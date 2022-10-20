#pragma once

#include <iostream>
#include <istream>
#include <functional>

namespace some_namespace {

	using inds = unsigned int[2];

	using init_callback = std::function<double(unsigned int, unsigned int)>;
	const init_callback _default_callback = [](unsigned int i, unsigned int j) { return 0.0; };

	class some_matrix
	{
	private:
		unsigned int id;
		double* buffer;
		unsigned int row, col;

	public:
		
		explicit some_matrix(unsigned int rows, unsigned int cols, init_callback init = _default_callback);

		explicit some_matrix(unsigned int size, init_callback init = _default_callback);

		explicit some_matrix();

		some_matrix(const some_matrix& source);

		some_matrix(some_matrix&& source);

		~some_matrix();

		unsigned int get_id() const;
		unsigned int get_row() const;
		unsigned int get_col() const;

		void for_each(std::function<void(double&)> callback) const;
		void for_each(std::function<void(double&, unsigned int, unsigned int)> callback) const;

		bool check_mul(const some_matrix& other) const;
		bool check_sum(const some_matrix& other) const;

		double max() const;
		double min() const;

		double& operator[](const inds& indexs) const;

		friend std::ostream& operator<<(std::ostream& output, const some_matrix& matrix);

		some_matrix& operator=(const some_matrix& other);
		some_matrix& operator=(some_matrix&& other);

		some_matrix& operator+=(const some_matrix& other);
		some_matrix& operator-=(const some_matrix& other);
		some_matrix& operator*=(const some_matrix& other);
		some_matrix& operator*=(const double& other);
	};

	some_matrix operator+(const some_matrix& A, const some_matrix& B);
	some_matrix operator-(const some_matrix& A, const some_matrix& B);
	some_matrix operator*(const some_matrix& A, const some_matrix& B);
	some_matrix operator*(const some_matrix& A, double num);

}