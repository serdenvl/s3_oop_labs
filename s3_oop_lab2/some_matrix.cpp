#include "some_matrix.h"
#include <string>
#include <iomanip>

using namespace std;

unsigned int some_matrix::get_row_number() const
{
	return row_number;
}

unsigned int some_matrix::get_col_number() const
{
	return col_number;
}

void some_matrix::for_each(function<void(double&)> callback) const
{
	for (unsigned int i = 0; i < row_number * col_number; ++i)
		callback(buffer[i]);
}

void some_matrix::for_each(function<void(double&, unsigned int, unsigned int)> callback) const
{
	for (unsigned int i = 0; i < row_number * col_number; ++i)
		callback(buffer[i], i / col_number, i % col_number);
}

bool some_matrix::is_suitable_for_multiplication(const some_matrix& other) const
{
	return this->col_number == other.row_number;
}

bool some_matrix::is_suitable_for_addiction(const some_matrix& other) const
{
	return (this->row_number == other.row_number) && (this->col_number == other.col_number);
}

double some_matrix::max() const
{
	double max = buffer[0];
	for_each([&](double v) {max = (max < v) ? v : max; });
	return max;
}

double some_matrix::min() const
{
	double min = buffer[0];
	for_each([&](double v) {min = (min > v) ? v : min; });
	return min;
}

double& some_matrix::operator()(unsigned int i, unsigned int j) const
{
	return buffer[i * col_number + j];
}


some_matrix some_matrix::operator=(const some_matrix& other) const
{
	return some_matrix(other);
}

void some_matrix::operator+=(const some_matrix& other)
{
	if (!is_suitable_for_addiction(other))
	{
		throw invalid_argument("addiction is impossible");
	}

	for_each([&](auto v, auto i, auto j) { v += other(i, j); });
}

void some_matrix::operator-=(const some_matrix& other)
{
	if (!is_suitable_for_addiction(other))
	{
		throw invalid_argument("addiction is impossible");
	}

	for_each([&](auto v, auto i, auto j) { v -= other(i, j); });
}

void some_matrix::operator*=(const some_matrix& other)
{
	some_matrix t = *this * other;
	this->buffer = exchange(t.buffer, nullptr);
	this->col_number = t.col_number;
	this->row_number = t.row_number;
}

void some_matrix::operator*=(double& scalar)
{
	for_each([&](auto v) { v *= scalar; });
}

std::ostream& operator<<(std::ostream& out, const some_matrix& matrix)
{
	matrix.for_each([&](auto v, auto i, auto j)
		{
			out << setw(3) << matrix(i, j);
			if (j + 1 == matrix.col_number)
				out << endl;
		});
	return out;
}

some_matrix operator+(const some_matrix& A, const some_matrix& B)
{
	if (!A.is_suitable_for_addiction(B))
	{
		throw invalid_argument("addiction is impossible");
	}

	return some_matrix(A.get_col_number(), A.get_row_number(), [&](auto i, auto j) { return A(i, j) + B(i, j); });
}

some_matrix operator-(const some_matrix& A, const some_matrix& B)
{
	if (!A.is_suitable_for_addiction(B))
	{
		throw invalid_argument("addiction is impossible");
	}

	return some_matrix(A.get_col_number(), A.get_row_number(), [&](auto i, auto j) { return A(i, j) - B(i, j); });
}

some_matrix operator*(const some_matrix& A, const some_matrix& B)
{
	if (!A.is_suitable_for_multiplication(B))
	{
		throw invalid_argument("multiplication is impossible");
	}

	double sum;
	return some_matrix (A.get_row_number(), B.get_col_number(), [&](auto i, auto j) {
		sum = 0.0;
		for (unsigned k = 0; k < A.get_row_number(); ++k)
		{
			sum += A(i, k) * B(k, j);
		}
		return sum;
	});
}

some_matrix operator*(const some_matrix& A, double a)
{
	return some_matrix(A.get_col_number(), A.get_row_number(), [&](auto i, auto j) { return A(i, j) * a; });
}