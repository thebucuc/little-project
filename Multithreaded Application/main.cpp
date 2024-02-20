#include <iostream>
#include <filesystem>
#include <queue>
#include "arg_parse.h"

namespace fs = std::filesystem;
namespace ap = arg_parse;


int main(int argc, char* argv[])
{
	try
	{
		arg_parse::parse(argc, argv);
	}
	catch(const std::exception &ex)
	{
		std::cerr << ex.what() << "\n";
		std::cerr << "usage: app [-d/--directory] <dir-path> [-q/--query] <query-string> "
			<< "[-o(-fo)/--output(--force-output) <text output path>]\n";
			
	}
	std::queue<fs::path> file_queue;
	for(const auto &file : ap::input_files())
	{
		fs::path file_path(file);
		if(is_directory(file_path))
		{
			for(auto &itr: fs::recursive_directory_iterator(file_path))
			{
				/*
				 *TODO: way to decide whether or not the file is a text file
				 *regardless of extension
				 */
				if(itr.path().extension()==".txt")
				{
					file_queue.push(itr.path());
				}
			}
		}
	}


	return 0;
}
