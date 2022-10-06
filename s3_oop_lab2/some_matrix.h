#pragma once

#include <iostream>
#include <istream>
#include <functional>

using inds = size_t[2];

using init_callback = std::function<double(size_t, size_t)>;
const init_callback _default_callback = [](size_t i, size_t j) { return 0.0; };

namespace some_namespace {

	class some_matrix
	{
	private:
		size_t id;
		double* buffer;
		size_t row_number, col_number;

	public:
		
		some_matrix(size_t row_number, size_t col_number, init_callback init = _default_callback);

		some_matrix(size_t size, init_callback init = _default_callback);

		some_matrix();

		some_matrix(const some_matrix& source);

		~some_matrix();

		size_t get_row_number() const;
		size_t get_col_number() const;

		void for_each(std::function<void(double&)> callback) const;
		void for_each(std::function<void(double&, size_t, size_t)> callback) const;

		bool is_suitable_for_multiplication(const some_matrix& other) const;
		bool is_suitable_for_addiction(const some_matrix& other) const;

		double max() const;
		double min() const;

		double& operator[](const inds&& indexs) const;

		friend std::ostream& operator<<(std::ostream& output, const some_matrix& matrix);

		some_matrix& operator=(const some_matrix& other);
		void operator+=(const some_matrix& other);
		void operator-=(const some_matrix& other);
		void operator*=(const some_matrix& other);
		void operator*=(double& other);
	};

	some_matrix operator+(const some_matrix& A, const some_matrix& B);
	some_matrix operator-(const some_matrix& A, const some_matrix& B);
	some_matrix operator*(const some_matrix& A, const some_matrix& B);
	some_matrix operator*(const some_matrix& A, double a);

}