#pragma once

#include <iostream>
#include <istream>
#include <functional>

using ind = size_t;

using init_matrix_callback = std::function<double(const ind&, const ind&)>;
const init_matrix_callback _default_matrix_callback = [](auto, auto) { return 0.0; };

namespace just_namespace
{

	class just_matrix
	{
	protected:
		double* buffer;
		ind row_number, col_number;

	public:
		just_matrix(const ind& row_number = 1, const ind& col_number = 1,
			const init_matrix_callback& init = _default_matrix_callback) : row_number(row_number), col_number(col_number)
		{
			std::cout << "Constructor"
				<< " "
				<< "[" << this << "]"
				<< " "
				<< "matrix(" << row_number << ":" << col_number << ")"
				<< " "
				<< "init: " << ((&init == &_default_matrix_callback) ? "default" : "some")
				<< std::endl;

			buffer = new double[row_number * col_number];
			for_each([&](auto& v, auto i, auto j) { v = init(i, j); });
		}

		just_matrix(const just_matrix& source) : row_number(source.row_number), col_number(source.col_number)
		{
			std::cout << "Constructor"
				<< " "
				<< "[" << this << "]"
				<< " "
				<< "matrix(" << &source << ")"
				<< std::endl;

			buffer = new double[row_number * col_number];
			for_each([&](auto& v, auto i, auto j) { v = source(i, j); });
		}

		virtual ~just_matrix()
		{
			std::cout << "Destructor"
				<< " "
				<< "[" << this << "]"
				<< " "
				<< "matrix"
				<< std::endl;

			delete[] buffer;
		}

		void for_each(std::function<void(double&)> callback) const;
		void for_each(std::function<void(double&, const ind&, const ind&)> callback) const;

		bool is_suitable_for_addiction(const just_matrix& other) const;
		bool is_suitable_for_multiplication(const just_matrix& other) const;

		double& operator()(const ind& i, const ind& j) const;

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