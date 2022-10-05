#include "just_vector.h"

using namespace std;

namespace just_namespace
{

	void just_vector::for_each(std::function<void(double&, const ind&)> callback)
	{
		for (ind i = 0; i < row_number * col_number; ++i)
			callback(buffer[i], i);
	}

	double& just_vector::operator()(const ind& i) const
	{
		return buffer[i];
	}

}
