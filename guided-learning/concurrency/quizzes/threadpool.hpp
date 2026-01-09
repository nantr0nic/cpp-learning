#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <vector>
#include <queue>
#include <functional>
#include <chrono>
#include <print>

class ThreadPool
{
public:
    explicit ThreadPool(size_t num_threads) {
        for (size_t i = 0; i < num_threads; ++i) {
// We use emplace_back rather than push_back because the latter expects you to
// create the object FIRST, then it copies (or moves) that object into the vector
// but std::jthread is NOT COPYABLE and constructing it inside push_back() creates
// a temporary, moves it to vector, destroys temporary -- unnecessary with emplace_back
// emplace_back constructs the object _directly inside the vector's memory_, it
// forwards the arguments (the lambda) straight to the std::jthread constructor
            workers.emplace_back([this] {
// use while (true) {} to keep thread alive
                while (true) {
                    std::function<void()> task;
                    {
                        // Lock first
                        std::unique_lock<std::mutex> lock(queue_mutex);
                        // Now wait
// on a ThreadPool being constructed, all the threads immediately go to sleep
// at the wait instruction here
// thread unlocks lock and sleeps if the predicate is TRUE
                        condition.wait(lock, [this] {
                            return stop_flag || !tasks.empty();
                        });
                        // Check exit condition
                        if (stop_flag && tasks.empty()) {
                            return;
                        }
                        // If exit condition isn't met, grab a task
                        task = std::move(tasks.front());
                        tasks.pop();
                    } // Lock releases here
                    // Execute the task
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
// This needs to be in the correct order. Make sure workers are destroyed first
// thus declared last
    // 1. DATA (Tasks, Flags)
    std::queue<std::function<void()>> tasks;
    std::atomic<bool> stop_flag { false };
    // 2. SYNCHRONIZATION (Must outlive workers)
    std::mutex queue_mutex;
    std::condition_variable condition;
    // 3. WORKERS (Must be destroyed FIRST, so declared LAST)
    std::vector<std::jthread> workers;
};
