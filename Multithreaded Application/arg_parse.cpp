#include "arg_parse.h"



std::vector<std::string> _input_files;
std::string _query_string;
std::string _output_file;
bool _directory_selected = false;
bool _query_provided = false;
bool _output_provided = false;
bool _force_output = false;

void arg_parse::parse(int argc,char *argv[])
{
	const std::vector<std::string> args(argv + 1, argv + argc);
	for(const auto &arg:args)
	{
	
		if(arg=="-d" || arg=="--directory")
		{
			if(_directory_selected)
			{
				throw std::runtime_error("app: cannot use -d or --directory twice");
			}
			_directory_selected = true;
			continue;
		}


		if(arg=="-q" || arg=="--query")
		{
			if(_query_provided)
			{
				throw std::runtime_error("app: cannot use -q or --query twice");
			}
			_query_provided = true;
			continue;
		}

		if(_query_provided && _query_string.empty())
		{
			_query_string = arg;
			continue;
		}

		if(arg=="-o"|| arg=="--output")
		{
			if(_output_provided)
			{
				throw std::runtime_error("app: cannot use -o/-fo or --output twice");
			}
			_output_provided = true;
			continue;
		}

		if(_output_provided && _output_file.empty())
		{
			if(!std::filesystem::exists(arg))
			{
				throw std::runtime_error("app: the provided output file does not exist");
			}
			_output_file = arg;
			continue;
		}
		if(arg=="-fo" || arg=="--force-output")
		{
			if(_force_output || _output_provided)
			{
				throw std::runtime_error("app: cannot use -o/-fo or --output twice");
			}
			_force_output = true;
			//_output_provided = true;
			continue;
		}
		if(_force_output && _output_file.empty())
		{
			if (!std::filesystem::exists(arg))
			{
				//initialise and destroy ofstream, thus creating the file
				std::ofstream{arg};
			}
			_output_file = arg;
			continue;
		}

		if(_directory_selected && !_query_provided && !_output_provided)
		{
			if (!std::filesystem::exists(arg)) {
				throw std::runtime_error(std::string("app: the provided directory does not exist: ")+arg);
			}
			_input_files.push_back(arg);
		}
	}
	if(!_query_provided || _query_string.empty())
	{
		throw std::runtime_error("app: provide the query");
	}
}


const std::vector<std::string>& arg_parse::input_files()
{
    return _input_files;
}

const std::string& arg_parse::output_file()
{
	return _output_file;
}

const std::string& arg_parse::query_string()
{
	return _query_string;
}

