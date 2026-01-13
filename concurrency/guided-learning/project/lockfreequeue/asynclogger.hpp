#include "lock_free_queue.hpp"

#include <string>
#include <condition_variable>
#include <thread>
#include <fstream>
#include <atomic>

class AsyncLogger {
public:
    explicit AsyncLogger(const std::string& filename);

    ~AsyncLogger();

    void Log(const std::string& message);

private:
    void process_logs();

    std::ofstream log_file_stream;
    LockFreeQueue log_queue;
    std::atomic_flag spin_lock = ATOMIC_FLAG_INIT;
    std::mutex signal_mut;
    std::condition_variable c_v;
    std::atomic<bool> stop_flag{ false };
    std::jthread log_worker;
};