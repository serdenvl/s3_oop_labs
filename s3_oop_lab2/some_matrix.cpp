#include "some_matrix.h"

#include <sstream>
#include <iomanip>

#include "stuffs.h"

using namespace std;

static size_t ID = 0;

namespace some_namespace
{
	some_matrix::some_matrix(size_t row_number, size_t col_number, init_callback init)
		: row_number(row_number), col_number(col_number), id(++ID)
	{
		cout_structor_info(
			"Constructor some_matrix base",
			(stringstream() << "(" << row_number << "," << col_number << ")").str(),
			id_string(id, this)
		);

		buffer = new double[row_number * col_number];
		for (size_t i = 0; i < row_number * col_number; ++i)
		{
			if (i / col_number == 4)
			{
				i = i;
			}
			buffer[i] = init(i / col_number, i % col_number);
		}
	}

	some_matrix::some_matrix(size_t size, init_callback init) : some_matrix(size, size, init)
	{
		cout_structor_info(
			"Constructor some_matrix square",
			(stringstream() << "(" << size << ")").str(),
			id_string(id, this)
		);
	}

	some_matrix::some_matrix() : some_matrix(1, 1, _default_callback)
	{
		cout_structor_info(
			"Constructor some_matrix default",
			"()",
			id_string(id, this)
		);
	}

	some_matrix::some_matrix(const some_matrix& source) : row_number(source.row_number), col_number(source.col_number), id(++ID)
	{
		cout_structor_info(
			"Constructor some_matrix copy",
			(stringstream() << "(" << "#" << source.id << ")").str(),
			id_string(id, this)
		);

		buffer = new double[row_number * col_number];
		for (size_t i = 0; i < row_number * col_number; ++i)
			buffer[i] = source.buffer[i];
	}

	some_matrix::~some_matrix()
	{
		cout_structor_info(
			"Destructor some_matrix",
			"",
			id_string(id, this)
		);

		delete[] buffer;
	}

	size_t some_matrix::get_id() const
	{
		return id;
	}

	size_t some_matrix::get_row_number() const
	{
		return row_number;
	}

	size_t some_matrix::get_col_number() const
	{
		return col_number;
	}

	void some_matrix::for_each(function<void(double&)> callback) const
	{
		for (size_t i = 0; i < row_number * col_number; ++i)
			callback(buffer[i]);
	}

	void some_matrix::for_each(function<void(double&, size_t, size_t)> callback) const
	{
		for (size_t i = 0; i < row_number * col_number; ++i)
		{
			callback(buffer[i], i / col_number, i % col_number);
		}
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

	double& some_matrix::operator[](const inds& indexs) const
	{
		if (!(0 <= indexs[0] && indexs[0] < row_number) || !(0 <= indexs[1] && indexs[1] < col_number))
		{
			ostringstream message;
			message << "accessing an element"
				<< " "
				<< "by index " << "(" << indexs[0] << "," << indexs[1] << ")"
				<< " "
				<< "of the matrix #" << id << " " << "(size:" << row_number << "x" << col_number << ")";
			throw out_of_range(message.str());
		}

		return buffer[indexs[0] * col_number + indexs[1]];
	}


	some_matrix& some_matrix::operator=(const some_matrix& other)
	{
		delete[] buffer;

		buffer = new double[row_number * col_number];
		row_number = other.row_number;
		col_number = other.col_number;

		for_each([&](auto& v, auto i, auto j) {v = other[inds{i, j}]; });

		return *this;
	}

	void some_matrix::operator+=(const some_matrix& other)
	{
		if (!is_suitable_for_addiction(other))
		{
			ostringstream message;
			message << "attempt"
				<< " "
				<< "matrix #" << id << "(size:" << row_number << "x" << col_number << ")"
				<< " "
				<< "+="
				<< "matrix #" << other.id << "(size:" << other.row_number << "x" << other.col_number << ")";

			throw logic_error(message.str());
		}

		for_each([&](auto& v, auto i, auto j) { v += other[inds{i, j}]; });
	}

	void some_matrix::operator-=(const some_matrix& other)
	{
		if (!is_suitable_for_addiction(other))
		{
			ostringstream message;
			message << "attempt"
				<< " "
				<< "matrix #" << id << "(size:" << row_number << "x" << col_number << ")"
				<< " "
				<< "-="
				<< "matrix #" << other.id << "(size:" << other.row_number << "x" << other.col_number << ")";

			throw logic_error(message.str());
		}

		for_each([&](auto& v, auto i, auto j) { v -= other[inds{i, j}]; });
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
		for_each([&](auto& v) { v *= scalar; });
	}

	ostream& some_namespace::operator<<(ostream& out, const some_matrix& matrix)
	{
		matrix.for_each([&](auto v, auto i, auto j)
			{
				out << setw(3) << matrix[inds{i, j}] << " ";
				if (j + 1 == matrix.col_number)
					out << endl;
			});
		return out;
	}

	some_matrix operator+(const some_matrix& A, const some_matrix& B)
	{
		if (!A.is_suitable_for_addiction(B))
		{
			ostringstream message;
			message << "attempt"
				<< " "
				<< "matrix #" << A.get_id() << "(size:" << A.get_row_number() << "x" << A.get_col_number() << ")"
				<< " "
				<< "+"
				<< " "
				<< "matrix #" << B.get_id() << "(size:" << B.get_row_number() << "x" << B.get_col_number() << ")";

			throw logic_error(message.str());
		}

		return some_matrix(A.get_row_number(), A.get_col_number(), [&](auto i, auto j) { return A[inds{i, j}] + B[inds{i, j}]; });
	}

	some_matrix operator-(const some_matrix& A, const some_matrix& B)
	{
		if (!A.is_suitable_for_addiction(B))
		{
			ostringstream message;
			message << "attempt"
				<< " "
				<< "matrix #" << A.get_id() << "(size:" << A.get_row_number() << "x" << A.get_col_number() << ")"
				<< " "
				<< "-"
				<< " "
				<< "matrix #" << B.get_id() << "(size:" << B.get_row_number() << "x" << B.get_col_number() << ")";

			throw logic_error(message.str());
		}

		return some_matrix(A.get_row_number(), A.get_col_number(), [&](auto i, auto j) { return A[inds{i, j}] - B[inds{i, j}]; });
	}

	some_matrix operator*(const some_matrix& A, const some_matrix& B)
	{
		if (!A.is_suitable_for_multiplication(B))
		{
			ostringstream message;
			message << "attempt"
				<< " "
				<< "matrix #" << A.get_id() << "(size:" << A.get_row_number() << "x" << A.get_col_number() << ")"
				<< " "
				<< "*"
				<< " "
				<< "matrix #" << B.get_id() << "(size:" << B.get_row_number() << "x" << B.get_col_number() << ")";

			throw logic_error(message.str());
		}

		double sum;
		return some_matrix(A.get_row_number(), B.get_col_number(), [&](auto i, auto j) {
			sum = 0.0;
			for (unsigned k = 0; k < A.get_row_number(); ++k)
			{
				sum += A[inds{ i, k }] * B[inds{ k,j }];
			}
			return sum;
			});
	}

	some_matrix operator*(const some_matrix& A, double a)
	{
		return some_matrix(A.get_row_number(), A.get_col_number(), [&](auto i, auto j) { return A[inds{i, j}] * a; });
	}

}