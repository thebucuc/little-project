#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <stdexcept>
#include <fstream>

namespace arg_parse
{
	void parse(int argc, char* argv[]);

	const std::vector<std::string>& input_files();
	const std::string& output_file();
	const std::string& query_string();

};