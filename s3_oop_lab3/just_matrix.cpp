#include "just_matrix.h"

#include <string>
#include <sstream>
#include <iomanip>

#include "stuffs.h"

using namespace std;

static unsigned int ID = 0;

namespace just_namespace
{
	just_matrix::just_matrix(const unsigned int& row, const unsigned int& col,
		const init_matrix_callback& init) : row(row), col(col), id(++ID)
	{
		cout_structor_info(
			"Constructor just_matrix base",
			(stringstream() << "(" << row << ":" << col << ")").str(),
			id_string(id, this)
		);

		if (row == 0 || col == 0)
		{
			buffer = nullptr;
			return;
		}

		buffer = new double[row * col];
		for_each([&](auto& v, auto i, auto j) { v = init(i, j); });
	}

	just_matrix::just_matrix() : just_matrix(0, 0) {}

	just_matrix::just_matrix(const just_matrix& source) : id(++ID)
	{
		cout_structor_info(
			"Constructor just_matrix copy",
			(stringstream() << "(" << "#" << source.id << ")").str(),
			id_string(id, this)
		);

		*this = source;
	}

	just_matrix::just_matrix(just_matrix&& source)
		 : row(source.row), col(source.col), id(++ID)
	{
		cout_structor_info(
			"Constructor just_matrix move",
			(stringstream() << "(" << "#" << source.id << ")").str(),
			id_string(id, this)
		);
		
		*this = source;
	}

	just_matrix::~just_matrix()
	{
		cout_structor_info(
			"Destructor just_matrix",
			"",
			id_string(id, this)
		);

		delete[] buffer;
	}

	unsigned int just_matrix::get_id() const
	{
		return id;
	}

	unsigned int just_matrix::get_row() const
	{
		return row;
	}

	unsigned int just_matrix::get_col() const
	{
		return col;
	}

	void just_matrix::for_each(function<void(double&)> callback) const
	{
		for (unsigned int i = 0; i < row * col; ++i)
			callback(buffer[i]);
	}

	void just_matrix::for_each(function<void(double&, const unsigned int&, const unsigned int&)> callback) const
	{
		for (unsigned int i = 0; i < row * col; ++i)
			callback(buffer[i], i / col, i % col);
	}

	bool just_matrix::check_sum(const just_matrix& other) const
	{
		return row == other.row && col == other.col;
	}

	bool just_matrix::check_mul(const just_matrix& other) const
	{
		return col == other.row;
	}

	double& just_matrix::operator[](const inds& indexs) const
	{
		if (!(0 <= indexs[0] && indexs[0] < row) || !(0 <= indexs[1] && indexs[1] < col))
		{
			throw "index out of range";
		}

		return buffer[indexs[0] * col + indexs[1]];
	}

	just_matrix& just_matrix::operator=(const just_matrix& other)
	{
		row = other.row;
		col = other.col;
		delete[] exchange(buffer, new double[row*col]);
		for_each([&](auto& v, auto i, auto j) {v = other[inds{ i, j }];
	});

		return *this;
	}

	just_matrix& just_matrix::operator=(just_matrix&& other)
	{
		row = exchange(other.row, 0);
		col = exchange(other.col, 0);
		delete[] exchange(buffer, exchange(other.buffer, nullptr));

		return *this;
	}

	just_matrix& just_matrix::operator+=(const just_matrix& other)
	{
		if (!check_sum(other))
		{
			throw "addiction is impossible";
		}

		for_each([&](auto& v, auto i, auto j) { v += other[inds{ i, j }]; });
		return *this;
	}

	just_matrix& just_matrix::operator-=(const just_matrix& other)
	{
		if (!check_sum(other))
		{
			throw "addiction is impossible";
		}

		for_each([&](auto& v, auto i, auto j) { v -= other[inds{ i, j }]; });
		return *this;
	}

	just_matrix just_matrix::operator+(const just_matrix& other) const
	{
		if (!check_sum(other))
		{
			throw "addiction is impossible";
		}

		return just_matrix(row, col, [&](auto i, auto j) { return (*this)[inds{ i, j }] + other[inds{ i, j }]; });
	}

	just_matrix just_matrix::operator-(const just_matrix& other) const
	{
		if (!check_sum(other))
		{
			throw "addiction is impossible";
		}

		return just_matrix(row, col, [&](auto i, auto j) { return (*this)[inds{ i, j }] - other[inds{ i, j }]; });
	}

	just_matrix& just_matrix::operator*=(const just_matrix& other)
	{
		if (!check_mul(other))
		{
			throw "multiplication is impossible";
		}

		just_matrix m = (*this) * other;

		row = m.row;
		col = m.col;
		delete[] exchange(buffer, exchange(m.buffer, nullptr));

		return *this;
	}

	just_matrix just_matrix::operator*(const just_matrix& other) const
	{
		if (!check_mul(other))
		{
			throw "multiplication is impossible";
		}

		return just_matrix(row, other.col, [&](auto i, auto j) {
			double sum = 0.0;
			for (unsigned k = 0; k < row; ++k)
			{
				sum += (*this)[inds{ i, k }] * other[inds{ k, j }];
			}
			return sum;
			});
	}

	just_matrix& just_matrix::operator*=(const double& num)
	{
		for_each([&](auto& v) { v *= num; });

		return *this;
	}

	just_matrix just_matrix::operator*(const double& num) const
	{
		return just_matrix(row, col, [&](auto i, auto j) { return (*this)[inds{ i, j }] * num; });
	}

	ostream& operator<<(ostream& output, const just_matrix& matrix)
	{
		matrix.for_each([&](auto v, auto i, auto j)
			{
				output << setw(3) << matrix[inds{ i, j }];
				if (j + 1 == matrix.col)
					output << endl;
			});
		return output;
	}

}
