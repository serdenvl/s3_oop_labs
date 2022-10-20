#pragma once

#include <iostream>
#include <istream>
#include <functional>

namespace just_namespace
{
	using init_matrix_callback = std::function<double(const unsigned int&, const unsigned int&)>;
	const init_matrix_callback _default_matrix_callback = [](auto, auto) { return 0.0; };

	class just_matrix
	{
	protected:
		unsigned int id;
		double* buffer;
		unsigned int row, col;

	public:
		explicit just_matrix(const unsigned int& row, const unsigned int& col,
			const init_matrix_callback& init = _default_matrix_callback);

		explicit just_matrix();

		just_matrix(const just_matrix& source);
		just_matrix(just_matrix&& source);

		virtual ~just_matrix();

		unsigned int get_id() const;
		unsigned int get_row() const;
		unsigned int get_col() const;

		void for_each(std::function<void(double&)> callback) const;
		void for_each(std::function<void(double&, const unsigned int&, const unsigned int&)> callback) const;

		bool check_sum(const just_matrix& other) const;
		bool check_mul(const just_matrix& other) const;

		double& operator()(const unsigned int& i, const unsigned int& j) const;

		friend std::ostream& operator<<(std::ostream& output, const just_matrix& matrix);

		just_matrix operator=(const just_matrix& other) const;

		void operator+=(const just_matrix& other);
		void operator-=(const just_matrix& other);
		just_matrix operator+(const just_matrix& other) const;
		just_matrix operator-(const just_matrix& other) const;

		void operator*=(const just_matrix& other);
		just_matrix operator*(const just_matrix& other) const;

		void operator*=(const double& num);
		just_matrix operator*(const double& num) const;
	};

}