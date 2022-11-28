#pragma once
#include <string>

const auto terminal_width = 120;

std::string id_string(size_t id, const void* pointer);

void cout_structor_info(const std::string& name, const std::string& params, const std::string& id);
