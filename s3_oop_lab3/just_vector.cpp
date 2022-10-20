#include "just_vector.h"

using namespace std;

namespace just_namespace
{

	void just_vector::for_each(std::function<void(double&, const unsigned int&)> callback)
	{
		for (unsigned int i = 0; i < row * col; ++i)
			callback(buffer[i], i);
	}

	double& just_vector::operator[](const unsigned int& i) const
	{
		return buffer[i];
	}

}
