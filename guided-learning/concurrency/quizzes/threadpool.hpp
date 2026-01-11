#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <vector>
#include <queue>
#include <functional>

class ThreadPool
{
public:
    explicit ThreadPool(size_t num_threads) {
        for (size_t i = 0; i < num_threads; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(queue_mutex);
                        condition.wait(lock, [this] {
                            return stop_flag || !tasks.empty();
                        });
                        if (stop_flag && tasks.empty()) {
                            return;
                        }
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    ~ThreadPool() {
        stop_flag = true;
        condition.notify_all();
    }

    void enqueue(std::function<void()> task) {
        {
            std::scoped_lock lock(queue_mutex);
            tasks.push(std::move(task));
        }
        condition.notify_one();
    }

private:
    std::queue<std::function<void()>> tasks;
    std::atomic<bool> stop_flag { false };
    std::mutex queue_mutex;
    std::condition_variable condition;
    std::vector<std::jthread> workers;
};
