#pragma once
#include<filesystem>
#include "thread_pool.h"
#include "arg_parse.h"
namespace file_processor
{
	void process(const std::filesystem::path& file);
	void process_directory(const std::filesystem::path& file,ThreadPool& pool);
}