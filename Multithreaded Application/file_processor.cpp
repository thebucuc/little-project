#include "file_processor.h"
#include <filesystem>
#include <fstream>
#include <iostream>
namespace ap = arg_parse;
namespace fs = std::filesystem;
void file_processor::process(const std::filesystem::path& file)
{
	std::fstream filep;
	filep.open(file,std::fstream::in);
	
}

void file_processor::process_directory(const std::filesystem::path& file, ThreadPool& pool)
{
	if (ap::recursive())
	{
		for (auto& itr : fs::recursive_directory_iterator(file))
		{
			/*
			 *TODO: way to decide whether or not the file is a text file
			 *regardless of extension
			 */
			if (itr.path().extension() == ".cpp")
			{
				std::cout<< itr.path().filename()<< "\n";
			}
		}
	}
	else
	{
		for (auto& itr : fs::directory_iterator(file))
		{
			/*
			 *TODO: way to decide whether or not the file is a text file
			 *regardless of extension
			 */
			if (itr.path().extension() == ".cpp")
			{
				pool.push(itr.path());
			}
		}
	}
}
