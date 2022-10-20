#include "some_matrix.h"

#include <sstream>
#include <iomanip>

#include "stuffs.h"

using namespace std;

static unsigned int ID = 0;

namespace some_namespace
{
	some_matrix::some_matrix(unsigned int row, unsigned int col, init_callback init)
		: row(row), col(col), id(++ID)
	{
		cout_structor_info(
			"Constructor some_matrix base",
			(stringstream() << "(" << row << "," << col << ")").str(),
			id_string(id, this)
		);

		if (row == 0 || col == 0)
		{
			buffer = nullptr;
			return;
		}

		buffer = new double[row * col];
		for (unsigned int i = 0; i < row * col; ++i)
		{
			buffer[i] = init(i / col, i % col);
		}
	}

	some_matrix::some_matrix(unsigned int size, init_callback init) : some_matrix(size, size, init)
	{
		cout_structor_info(
			"Constructor some_matrix square",
			(stringstream() << "(" << size << ")").str(),
			id_string(id, this)
		);
	}

	some_matrix::some_matrix() : some_matrix(0, 0, _default_callback)
	{
		cout_structor_info(
			"Constructor some_matrix default",
			"()",
			id_string(id, this)
		);
	}

	some_matrix::some_matrix(const some_matrix& source) : row(source.row), col(source.col), id(++ID)
	{
		cout_structor_info(
			"Constructor some_matrix copy",
			(stringstream() << "(" << "#" << source.id << ")").str(),
			id_string(id, this)
		);

		buffer = new double[row * col];
		for (unsigned int i = 0; i < row * col; ++i)
			buffer[i] = source.buffer[i];
	}

	some_matrix::some_matrix(some_matrix&& source) : row(source.row), col(source.col), id(++ID)
	{
		cout_structor_info(
			"Constructor some_matrix move",
			(stringstream() << "(" << "#" << source.id << ")").str(),
			id_string(id, this)
		);

		buffer = exchange(source.buffer, nullptr);
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

	unsigned int some_matrix::get_id() const
	{
		return id;
	}

	unsigned int some_matrix::get_row() const
	{
		return row;
	}

	unsigned int some_matrix::get_col() const
	{
		return col;
	}

	void some_matrix::for_each(function<void(double&)> callback) const
	{
		for (unsigned int i = 0; i < row * col; ++i)
			callback(buffer[i]);
	}

	void some_matrix::for_each(function<void(double&, unsigned int, unsigned int)> callback) const
	{
		for (unsigned int i = 0; i < row * col; ++i)
		{
			callback(buffer[i], i / col, i % col);
		}
	}

	bool some_matrix::check_mul(const some_matrix& other) const
	{
		return this->col == other.row;
	}

	bool some_matrix::check_sum(const some_matrix& other) const
	{
		return (this->row == other.row) && (this->col == other.col);
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
		if (!(0 <= indexs[0] && indexs[0] < row) || !(0 <= indexs[1] && indexs[1] < col))
		{
			ostringstream message;
			message << "accessing an element"
				<< " "
				<< "by index " << "(" << indexs[0] << "," << indexs[1] << ")"
				<< " "
				<< "of the matrix #" << id << " " << "(size:" << row << "x" << col << ")";
			throw out_of_range(message.str());
		}

		return buffer[indexs[0] * col + indexs[1]];
	}


	some_matrix& some_matrix::operator=(const some_matrix& other)
	{
		delete[] buffer;

		row = other.row;
		col = other.col;
		buffer = new double[row * col];

		for_each([&](auto& v, auto i, auto j) {v = other[inds{ i, j }]; });

		return *this;
	}

	some_matrix& some_matrix::operator=(const some_matrix&& other)
	{
		delete[] buffer;

		row = other.row;
		col = other.col;
		buffer = new double[row * col];

		for_each([&](auto& v, auto i, auto j) {v = other[inds{ i, j }]; });

		return *this;
	}

	some_matrix& some_matrix::operator+=(const some_matrix& other)
	{
		if (!check_sum(other))
		{
			ostringstream message;
			message << "attempt"
				<< " "
				<< "matrix #" << id << "(size:" << row << "x" << col << ")"
				<< " "
				<< "+="
				<< "matrix #" << other.id << "(size:" << other.row << "x" << other.col << ")";

			throw logic_error(message.str());
		}

		for_each([&](auto& v, auto i, auto j) { v += other[inds{ i, j }]; });
		return *this;
	}

	some_matrix& some_matrix::operator-=(const some_matrix& other)
	{
		if (!check_sum(other))
		{
			ostringstream message;
			message << "attempt"
				<< " "
				<< "matrix #" << id << "(size:" << row << "x" << col << ")"
				<< " "
				<< "-="
				<< "matrix #" << other.id << "(size:" << other.row << "x" << other.col << ")";

			throw logic_error(message.str());
		}

		for_each([&](auto& v, auto i, auto j) { v -= other[inds{ i, j }]; });
		return *this;
	}

	some_matrix& some_matrix::operator*=(const some_matrix& other)
	{
		/*some_matrix buf = *this * other;
		this->buffer = exchange(buf.buffer, nullptr);
		this->cols = buf.cols;
		this->rows = buf.rows;*/

		double* buf = exchange(buffer, new double[row * other.col]{});
		unsigned int old_cols = exchange(col, other.col);

		for_each([&](auto& v, auto i, auto j) {
			for (unsigned k = 0; k < row; ++k)
			{
				v += buf[i * old_cols + k] * other[inds{ k, j }];
			}
			});

		delete[] buf;
		return *this;
	}

	some_matrix& some_matrix::operator*=(const double& scalar)
	{
		for_each([&](auto& v) { v *= scalar; });
		return *this;
	}

	ostream& some_namespace::operator<<(ostream& out, const some_matrix& matrix)
	{
		matrix.for_each([&](auto v, auto i, auto j)
			{
				out << setw(3) << matrix[inds{ i, j }] << " ";
				if (j + 1 == matrix.col)
					out << endl;
			});
		return out;
	}

	some_matrix operator+(const some_matrix& A, const some_matrix& B)
	{
		if (!A.check_sum(B))
		{
			ostringstream message;
			message << "attempt"
				<< " "
				<< "matrix #" << A.get_id() << "(size:" << A.get_row() << "x" << A.get_col() << ")"
				<< " "
				<< "+"
				<< " "
				<< "matrix #" << B.get_id() << "(size:" << B.get_row() << "x" << B.get_col() << ")";

			throw logic_error(message.str());
		}

		//return some_matrix(A.get_row(), A.get_col(), [&](auto i, auto j) { return A[inds{ i, j }] + B[inds{ i, j }]; });
		some_matrix C = A;
		C += B;
		return C;
	}

	some_matrix operator-(const some_matrix& A, const some_matrix& B)
	{
		if (!A.check_sum(B))
		{
			ostringstream message;
			message << "attempt"
				<< " "
				<< "matrix #" << A.get_id() << "(size:" << A.get_row() << "x" << A.get_col() << ")"
				<< " "
				<< "-"
				<< " "
				<< "matrix #" << B.get_id() << "(size:" << B.get_row() << "x" << B.get_col() << ")";

			throw logic_error(message.str());
		}

		//return some_matrix(A.get_row(), A.get_col(), [&](auto i, auto j) { return A[inds{ i, j }] - B[inds{ i, j }]; });
		some_matrix C = A;
		C -= B;
		return C;
	}

	some_matrix operator*(const some_matrix& A, const some_matrix& B)
	{
		if (!A.check_mul(B))
		{
			ostringstream message;
			message << "attempt"
				<< " "
				<< "matrix #" << A.get_id() << "(size:" << A.get_row() << "x" << A.get_col() << ")"
				<< " "
				<< "*"
				<< " "
				<< "matrix #" << B.get_id() << "(size:" << B.get_row() << "x" << B.get_col() << ")";

			throw logic_error(message.str());
		}

		/*double sum;
		return some_matrix(A.get_row(), B.get_col(), [&](auto i, auto j) {
			sum = 0.0;
			for (unsigned k = 0; k < A.get_row(); ++k)
			{
				sum += A[inds{ i, k }] * B[inds{ k,j }];
			}
			return sum;
			});*/

		some_matrix C = A;
		C *= B;
		return C;
	}

	some_matrix operator*(const some_matrix& A, double num)
	{
		//return some_matrix(A.get_row(), A.get_col(), [&](auto i, auto j) { return A[inds{ i, j }] * num; });
		some_matrix res = A;
		res *= num;
		return res;
	}

}