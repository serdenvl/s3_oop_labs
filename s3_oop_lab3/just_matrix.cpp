#include "just_matrix.h"
#include <string>
#include <iomanip>

namespace just_namespace
{

	void just_matrix::for_each(std::function<void(double&)> callback) const
	{
		for (ind i = 0; i < row_number * col_number; ++i)
			callback(buffer[i]);
	}

	void just_matrix::for_each(std::function<void(double&, const ind&, const ind&)> callback) const
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
			throw std::invalid_argument("index out of range");
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
			throw std::invalid_argument("addiction is impossible");
		}

		for_each([&](auto& v, auto i, auto j) { v += other(i, j); });
	}

	void just_matrix::operator-=(const just_matrix& other)
	{
		if (!is_suitable_for_addiction(other))
		{
			throw std::invalid_argument("addiction is impossible");
		}

		for_each([&](auto& v, auto i, auto j) { v -= other(i, j); });
	}

	just_matrix just_matrix::operator+(const just_matrix& other) const
	{
		if (!is_suitable_for_addiction(other))
		{
			throw std::invalid_argument("addiction is impossible");
		}

		return just_matrix(row_number, col_number, [&](auto i, auto j) { return (*this)(i, j) + other(i, j); });
	}

	just_matrix just_matrix::operator-(const just_matrix& other) const
	{
		if (!is_suitable_for_addiction(other))
		{
			throw std::invalid_argument("addiction is impossible");
		}

		return just_matrix(row_number, col_number, [&](auto i, auto j) { return (*this)(i, j) - other(i, j); });
	}

	void just_matrix::operator*=(const just_matrix& other)
	{
		if (!is_suitable_for_multiplication(other))
		{
			throw std::invalid_argument("multiplication is impossible");
		}

		just_matrix m = (*this) * other;

		row_number = m.row_number;
		col_number = m.col_number;
		delete[] std::exchange(buffer, std::exchange(m.buffer, nullptr));
	}

	just_matrix just_matrix::operator*(const just_matrix& other) const
	{
		if (!is_suitable_for_multiplication(other))
		{
			throw std::invalid_argument("multiplication is impossible");
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

	std::ostream& operator<<(std::ostream& output, const just_matrix& matrix)
	{
		matrix.for_each([&](auto v, auto i, auto j)
			{
				output << std::setw(3) << matrix(i, j);
				if (j + 1 == matrix.col_number)
					output << std::endl;
			});
		return output;
	}

}
