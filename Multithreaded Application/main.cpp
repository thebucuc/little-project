#include <iostream>
#include <filesystem>
#include <queue>
#include "arg_parse.h"
#include "file_processor.h"
#include "thread_pool.h"

namespace fs = std::filesystem;
namespace ap = arg_parse;
namespace fp = file_processor;

template<typename DirItr>
DirItr getDirectoryIterator(fs::path& file)
{
	if (ap::recursive())
		return fs::recursive_directory_iterator(file);
	return fs::directory_iterator(file);
}

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
			<< "[-o(-fo)/--output(--force-output)] <text output path> [-r/--recursive]\n";
			
	}
	ThreadPool pool(ap::n_threads());
	for(const auto &file : ap::input_files())
	{
		if(fs::is_directory(file))
		{
			fp::process_directory(file, pool);
		}
	}

	return 0;
}
