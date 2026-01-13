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

    void Log(const std::string& message);

private:
    void process_logs();

    std::ofstream log_file_stream;
    std::queue<std::string> log_queue;
    std::mutex mut;
    std::condition_variable c_v;
    bool stop_flag{ false };
    std::jthread log_worker;
};
