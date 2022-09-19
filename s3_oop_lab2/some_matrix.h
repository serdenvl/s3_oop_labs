#pragma once

#include <iostream>
#include <istream>
#include <functional>

typedef std::function<double(unsigned int, unsigned int)> init_callback;
#define _default_callback [](unsigned int i, unsigned int j) { return 0.0; }

class some_matrix
{
protected:
	double *buffer;
	unsigned int row_number, col_number;

public:

	some_matrix(unsigned int row_number, unsigned int col_number, init_callback init = _default_callback) : row_number(row_number), col_number(col_number)
	{
		std::cout << "Constructor A "
			<< "matrix(" << row_number << ":" << col_number << ")"
			<< "[" << this << "]" << std::endl;

		buffer = new double[row_number * col_number];
		for (unsigned int i = 0; i < row_number * col_number; ++i)
			buffer[i] = init(i/col_number, i%col_number);
	}

	some_matrix(unsigned int size, init_callback init = _default_callback) : some_matrix(size, size, init)
	{
		std::cout << "Constructor B "
			<< "matrix(" << row_number << ":" << col_number << ")"
			<< "[" << this << "]" << std::endl;
	}

	some_matrix() : some_matrix(1, 1, _default_callback)
	{
		std::cout << "Constructor C "
			<< "matrix(" << row_number << ":" << col_number << ")"
			<< "[" << this << "]" << std::endl;
	}

	some_matrix(const some_matrix& m) : row_number(m.row_number), col_number(m.col_number)
	{
		std::cout << "Constructor D "
			<< "matrix(" << row_number << ":" << col_number << ")"
			<< "[" << this << "]" << std::endl;

		buffer = new double[row_number * col_number];
		for (unsigned int i = 0; i < row_number * col_number; ++i)
			buffer[i] = m.buffer[i];
	}

	~some_matrix()
	{
		std::cout << "Destructor "
			<< "matrix(" << row_number << ":" << col_number << ")"
			<< "[" << this << "]" << std::endl;

		delete [] buffer;
	}

	unsigned int get_row_number() const;
	unsigned int get_col_number() const;

	void for_each(std::function<void(double&)> callback) const;
	void for_each(std::function<void(double&, unsigned int, unsigned int)> callback) const;

	bool is_suitable_for_multiplication(const some_matrix& other) const;
	bool is_suitable_for_addiction(const some_matrix& other) const;

	double max() const;
	double min() const;

	double& operator()(unsigned int i, unsigned int j) const;

	friend std::ostream& operator<<(std::ostream& output, const some_matrix& matrix);

	some_matrix operator=(const some_matrix& other) const;
	void operator+=(const some_matrix& other);
	void operator-=(const some_matrix& other);
	void operator*=(const some_matrix& other);
	void operator*=(double& other);
};

some_matrix operator+(const some_matrix& A, const some_matrix& B);
some_matrix operator-(const some_matrix& A, const some_matrix& B);
some_matrix operator*(const some_matrix& A, const some_matrix& B);
some_matrix operator*(const some_matrix& A, double a);
