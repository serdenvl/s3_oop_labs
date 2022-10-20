#pragma once

#include <iostream>
#include <sstream>
#include <functional>

#include "just_matrix.h"
#include "stuffs.h"

namespace just_namespace
{

	using init_vector_callback = std::function<double(const unsigned int&)>;
	const init_vector_callback _default_vector_callback = [](auto) { return 0.0; };

	class just_vector : public just_matrix
	{
	public:
		just_vector(const unsigned int& length, const init_vector_callback& init = _default_vector_callback);

		just_vector();

		void for_each(std::function<void(double&, const unsigned int&)> callback);

		double& operator[](const unsigned int& i) const;
	};

}