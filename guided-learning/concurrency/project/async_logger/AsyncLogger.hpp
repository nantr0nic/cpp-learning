#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <fstream>

class AsyncLogger {
public:
    explicit AsyncLogger(const std::string& filename);

    ~AsyncLogger();

    // The Main Interface: Adds a log to the queue (Non-blocking!)
    void Log(const std::string& message); // producer

private:
    void process_logs(); // consumer

    std::ofstream log_file_stream;
    std::queue<std::string> log_queue;
    std::mutex mut;
    std::condition_variable c_v;
    bool stop_flag{ false };
    std::jthread log_worker;
};