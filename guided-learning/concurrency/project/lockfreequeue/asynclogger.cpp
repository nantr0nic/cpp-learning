#include "asynclogger.hpp"

#include <atomic>
#include <chrono>
#include <stdexcept>
#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <fstream>

AsyncLogger::AsyncLogger(const std::string& filename)
    : log_queue(1024)
{
    log_file_stream.open(filename, std::ios::app);
    if (!log_file_stream.is_open()) {
        throw std::runtime_error("Failed to open " + filename);
    }

    log_worker = std::jthread(&AsyncLogger::process_logs, this);
}

AsyncLogger::~AsyncLogger() {
    {
        stop_flag = true;
    }
    c_v.notify_all();
}

void AsyncLogger::Log(const std::string& message) {
    bool success{ false };
    std::string entry = message + '\n';

    while (spin_lock.test_and_set(std::memory_order_acquire)) {
            std::this_thread::yield();
    }

    success = log_queue.push(std::move(entry));

    spin_lock.clear(std::memory_order_release);

    if (success) {
        c_v.notify_one();
    }
}

void AsyncLogger::process_logs() {
    int batch_count{ 0 };
    while (true) {
        std::optional<std::string> log_item = log_queue.pop();

        if (log_item.has_value()) {
            log_file_stream << *log_item;
            ++batch_count;

            if (batch_count >= 100) {
                log_file_stream.flush();
                batch_count = 0;
            }
        }

        else {
            if (batch_count > 0) {
                log_file_stream.flush();
                batch_count = 0;
            }

            if (stop_flag) {
                return;
            }

            std::unique_lock<std::mutex> lock(signal_mut);
            c_v.wait_for(lock, std::chrono::seconds(2), [this](){
                return !log_queue.empty() || stop_flag;
            });
        }
    }
}
