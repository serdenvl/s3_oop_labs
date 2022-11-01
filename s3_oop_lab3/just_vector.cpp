#include "just_vector.h"

using namespace std;

namespace just_namespace
{
	just_vector::just_vector(const unsigned int& length, const init_vector_callback& init)
		: just_matrix(length, 1, [&](auto i, auto) {return init(i); })
	{
		cout_structor_info(
			"Constructor just_vector base",
			(stringstream() << "(" << length << ")").str(),
			id_string(id, this)
		);
	}

	just_vector::just_vector() : just_matrix()
	{
		cout_structor_info(
			"Constructor just_vector default",
			"()",
			id_string(id, this)
		);
	}

	just_vector::~just_vector()
	{
		cout_structor_info(
			"Destructor just_vector",
			(stringstream() << "#" << id).str(),
			id_string(id, this)
		);
	}

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
