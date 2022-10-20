#include "just_matrix.h"

#include <string>
#include <iomanip>

using namespace std;

static size_t ID = 0;

namespace just_namespace
{
	just_matrix::just_matrix(const ind& row_number, const ind& col_number,
		const init_matrix_callback& init) : row_number(row_number), col_number(col_number), id(++ID)
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

	just_matrix::just_matrix(const just_matrix& source)
		: row_number(source.row_number), col_number(source.col_number), id(++ID)
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

	just_matrix::~just_matrix()
	{
		std::cout << "Destructor"
			<< " "
			<< "[" << this << "]"
			<< " "
			<< "matrix"
			<< std::endl;

		delete[] buffer;
	}

	void just_matrix::for_each(function<void(double&)> callback) const
	{
		for (ind i = 0; i < row_number * col_number; ++i)
			callback(buffer[i]);
	}

	void just_matrix::for_each(function<void(double&, const ind&, const ind&)> callback) const
	{
		for (ind i = 0; i < row_number * col_number; ++i)
			callback(buffer[i], i / col_number, i % col_number);
	}

	bool just_matrix::is_suitable_for_addiction(const just_matrix& other) const
	{
		return row_number == other.row_number && col_number == other.col_number;
	}

	bool just_matrix::is_suitable_for_multiplication(const just_matrix& other) const
	{
		return col_number == other.row_number;
	}

	double& just_matrix::operator()(const ind& i, const ind& j) const
	{
		if (!(0 <= i && i < row_number) || !(0 <= j && j < col_number))
		{
			throw "index out of range";
		}

		return buffer[i * col_number + j];
	}

	just_matrix just_matrix::operator=(const just_matrix& other) const
	{
		return just_matrix(other);
	}

	void just_matrix::operator+=(const just_matrix& other)
	{
		if (!is_suitable_for_addiction(other))
		{
			throw "addiction is impossible";
		}

		for_each([&](auto& v, auto i, auto j) { v += other(i, j); });
	}

	void just_matrix::operator-=(const just_matrix& other)
	{
		if (!is_suitable_for_addiction(other))
		{
			throw "addiction is impossible";
		}

		for_each([&](auto& v, auto i, auto j) { v -= other(i, j); });
	}

	just_matrix just_matrix::operator+(const just_matrix& other) const
	{
		if (!is_suitable_for_addiction(other))
		{
			throw "addiction is impossible";
		}

		return just_matrix(row_number, col_number, [&](auto i, auto j) { return (*this)(i, j) + other(i, j); });
	}

	just_matrix just_matrix::operator-(const just_matrix& other) const
	{
		if (!is_suitable_for_addiction(other))
		{
			throw "addiction is impossible";
		}

		return just_matrix(row_number, col_number, [&](auto i, auto j) { return (*this)(i, j) - other(i, j); });
	}

	void just_matrix::operator*=(const just_matrix& other)
	{
		if (!is_suitable_for_multiplication(other))
		{
			throw "multiplication is impossible";
		}

		just_matrix m = (*this) * other;

		row_number = m.row_number;
		col_number = m.col_number;
		delete[] exchange(buffer, exchange(m.buffer, nullptr));
	}

	just_matrix just_matrix::operator*(const just_matrix& other) const
	{
		if (!is_suitable_for_multiplication(other))
		{
			throw "multiplication is impossible";
		}

		return just_matrix(row_number, other.col_number, [&](auto i, auto j) {
			double sum = 0.0;
			for (unsigned k = 0; k < row_number; ++k)
			{
				sum += (*this)(i, k) * other(k, j);
			}
			return sum;
			});
	}

	void just_matrix::operator*=(const double& a)
	{
		for_each([&](auto& v) { v *= a; });
	}

	just_matrix just_matrix::operator*(const double& a) const
	{
		return just_matrix(row_number, col_number, [&](auto i, auto j) { return (*this)(i, j) * a; });
	}

	ostream& operator<<(ostream& output, const just_matrix& matrix)
	{
		matrix.for_each([&](auto v, auto i, auto j)
			{
				output << setw(3) << matrix(i, j);
				if (j + 1 == matrix.col_number)
					output << endl;
			});
		return output;
	}

}
