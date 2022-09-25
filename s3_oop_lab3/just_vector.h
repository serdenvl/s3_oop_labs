#pragma once

#include "just_matrix.h"

#include <iostream>
#include <istream>
#include <functional>

using init_vector_callback = std::function<double(const ind&)>;
const init_vector_callback _default_vector_callback = [](auto) { return 0.0; };

class just_vector : public just_matrix
{
public:
	just_vector(const ind& length = 1, const init_vector_callback& init = _default_vector_callback)
		: just_matrix(length, 1, [&](auto i, auto) {return init(i); })
	{
		std::cout << "Constructor" << " "
			<< "[" << this << "]" << " "
			<< "vector(" << length << ")" << " "
			<< "init: " << ((&init == &_default_vector_callback) ? "default" : "some") << std::endl;
	}

	void for_each(std::function<void(double&, const ind&)> callback);

	double& operator()(const ind& i) const;
};

