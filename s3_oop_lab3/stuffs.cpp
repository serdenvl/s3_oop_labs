#include "stuffs.h"

#include <sstream>
#include <iomanip>
#include <iostream>

std::string id_string(size_t id, const void* pointer)
{
	return (std::stringstream() << "[" << "#" << id << " | " << pointer << "]").str();
}

void cout_structor_info(const std::string name, const std::string params, const std::string id)
{
	constexpr auto example_name = "Constructor some_matrix default";
	constexpr auto example_params = "(100,100)";
	constexpr auto example_id = "[#0 | 1234567891234567]";

	auto max_len = 2 + strlen(example_name) + strlen(example_params) + strlen(example_id);

	std::stringstream buffer;
	buffer << name
		<< std::setw(strlen(example_name) - name.length() + 1) << std::left << " "
		<< params
		<< std::setw(strlen(example_params) - params.length() + 1) << std::left << " "
		<< id;

	std::string message = buffer.str();

	if (message.length() > max_len)
		throw std::logic_error("too long");

	std::cout << std::setw(terminal_width - 1 - max_len) << std::left << "" << message << std::endl;
}
