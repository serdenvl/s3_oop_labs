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
		unsigned int row_number, col_number;

	public:
		just_matrix(const unsigned int& row_number = 1, const unsigned int& col_number = 1,
			const init_matrix_callback& init = _default_matrix_callback);

		just_matrix(const just_matrix& source);

		virtual ~just_matrix();

		void for_each(std::function<void(double&)> callback) const;
		void for_each(std::function<void(double&, const unsigned int&, const unsigned int&)> callback) const;

		bool is_suitable_for_addiction(const just_matrix& other) const;
		bool is_suitable_for_multiplication(const just_matrix& other) const;

		double& operator()(const unsigned int& i, const unsigned int& j) const;

		friend std::ostream& operator<<(std::ostream& output, const just_matrix& matrix);

		just_matrix operator=(const just_matrix& other) const;

		void operator+=(const just_matrix& other);
		void operator-=(const just_matrix& other);
		just_matrix operator+(const just_matrix& other) const;
		just_matrix operator-(const just_matrix& other) const;

		void operator*=(const just_matrix& other);
		just_matrix operator*(const just_matrix& other) const;

		void operator*=(const double& a);
		just_matrix operator*(const double& a) const;
	};

}