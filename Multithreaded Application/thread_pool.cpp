#include "thread_pool.h"
#include "file_processor.h"
namespace fp = file_processor;
ThreadPool::ThreadPool(size_t threads) : stop(false)
{
    for (size_t i = 0; i < threads; ++i)
        workers.emplace_back(
            [this]
            {
                std::filesystem::path file;

                std::unique_lock<std::mutex> lock(this->queue_mutex);
                while(!this->stop || (this->stop && !this->files.empty()))
                {
                	this->condition.wait(lock,
                            [this] { return this->stop || !this->files.empty(); });
                	
                    if(!files.empty())
                    {
                        file = std::move(this->files.front());
                		this->files.pop();
	                    
	                    lock.unlock();
	                    fp::process(file);
	                    lock.lock();
                    }
                }
            }
            );
}

void ThreadPool::push(std::filesystem::path file)
{
    std::lock_guard<std::mutex> lock(queue_mutex);
    files.push(file);
    condition.notify_one();
}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread& worker : workers)
        worker.join();
}
