#include "AsyncLogger.hpp"

#include <chrono>
#include <stdexcept>
#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <fstream>
#include <print>

AsyncLogger::AsyncLogger(const std::string& filename) {
    log_file_stream.open(filename, std::ios::app);
    if (!log_file_stream.is_open()) {
        throw std::runtime_error("Failed to open " + filename);
    }

    log_worker = std::jthread(&AsyncLogger::process_logs, this);
}

AsyncLogger::~AsyncLogger() {
    {
        std::scoped_lock lock(mut);
        stop_flag = true;
    }
    c_v.notify_all();
}

void AsyncLogger::Log(const std::string& message) {
    std::string entry = message + '\n';
    {
        std::scoped_lock lock(mut);
        log_queue.push(std::move(entry));
    }
    c_v.notify_one();
}

void AsyncLogger::process_logs() {
    while (true) {
        std::queue<std::string> local_queue;
        {
            std::unique_lock<std::mutex> lock(mut);
            c_v.wait_for(
                lock,
                std::chrono::seconds(2),
                [this](){ return !log_queue.empty() || stop_flag; }
            );

            if (stop_flag && log_queue.empty()) {
                return;
            }

            // In case we wake up from 2 second timeout
            if (!log_queue.empty()) {
                std::swap(log_queue, local_queue);
            }
        }

        while (!local_queue.empty()) {
            log_file_stream << local_queue.front();
            local_queue.pop();
        }

        log_file_stream.flush();
    }
}
