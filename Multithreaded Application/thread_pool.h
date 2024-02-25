#pragma once

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <filesystem>
#include <functional>
#include <stdexcept>

class ThreadPool {
public:
    ThreadPool(size_t);
    ~ThreadPool();
    void push(std::filesystem::path);
private:
    std::vector< std::thread > workers;
    std::queue< std::filesystem::path > files;

    // synchronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};
