/*
1. Use std::condition_variable for thread signaling.
2. Implement producer-consumer using a queue and condition variable.
3. Use std::async and std::future to get result from a thread.
4. Run multiple asynchronous tasks and wait for results.
*/

#include <cstdio>
#include <string>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <print>
#include <chrono>
#include <queue>
#include <functional>
#include <future>
#include <atomic>

// Global stuff for the exercises
std::mutex mut;
std::condition_variable c_v;
bool ready{ false };
std::atomic<bool> stop_flag{ false };
std::queue<std::function<void()>> task_queue;
std::queue<std::string> string_data;

void exercise1() {
    std::jthread worker1([](){
        std::unique_lock<std::mutex> lock(mut);
        std::println("(Ex 1) Worker 1 - Waiting on CV");
        c_v.wait(lock, [](){ return ready; });
        std::println("(Ex 1) Worker 1 - Woken up!");
        // reset "ready" for other exercises
        ready = false;
    });
    std::jthread worker2([](){
        std::println("(Ex 1) Worker 2 - Spawned!");
        {
            std::scoped_lock lock(mut);
            std::print("(Ex 1) Worker 2 - Lock acquired. Simulating work");
            for (int i = 0; i <= 4; ++i) {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                std::print(".");
                std::fflush(stdout);
                if (i == 4) {
                    std::print("\n");
                }
            }
            ready = true;
        }
        std::println("(Ex 1) Worker 2 - Released lock! Notifying!");
        c_v.notify_one();
    });
}

void exercise2_pro(int task) {
    std::println("(Ex 2) Producer called!");
    std::println("(Ex 2) Producer working on task #{}...", task);
    std::string string_result = "(Ex 2) Producer string data from task {"
                                + std::to_string(task) + "}";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::scoped_lock lock(mut);
        string_data.push(std::move(string_result));
    }
    std::println("(Ex 2) Producer done. Notifying!");
    c_v.notify_one();
}

void exercise2_con() {
    std::println("(Ex 2) Consumer thread started!");
    while (true) {
        std::unique_lock<std::mutex> lock(mut);
        std::println("(Ex 2) Consumer waiting...");
        c_v.wait(lock, [](){ return !string_data.empty() || stop_flag; });
        if (stop_flag && string_data.empty()) {
            std::println("(Ex 2) Consumer thread stopping...");
            break;
        }
        std::println("(Ex 2) Consumer notified!!!");
        if (!string_data.empty()) {
            std::string consumed_string = string_data.front();
            std::println("(Ex 2) Consumer consumes data: {}", consumed_string);
            string_data.pop();
        }
    }
}

void exercise2() {
    for (int i = 0; i < 3; ++i) {
        task_queue.emplace([i]() { exercise2_pro(i); });
    }

    std::jthread pro_thread([]() {
        while (true) {
            std::function<void()> task;
            if (task_queue.empty()) {
                stop_flag = true;
                c_v.notify_one();
                break;
            }
            task = std::move(task_queue.front());
            task_queue.pop();
            task();
        }
    });

    std::jthread con_thread([](){
        exercise2_con();
    });
}

void exercise3() {
    auto square = [](int x){ return x * x; };
    std::future<int> result = std::async(std::launch::async, square, 1024);
    std::println("(Ex 3) The square of 1024 is: {}", result.get());
}

void exercise4() {
    auto square = [](int x){ return x * x; };
    std::vector<std::future<int>> results;
    for (int i = 0; i < 8; ++i) {
        results.push_back(std::async(std::launch::async, square, i));
    }
    for (size_t i = 0; i < results.size(); ++i) {
        std::println("(Ex 4) The square of {} is {}", i, results[i].get());
    }
}

int main() {
    std::println("----- Exercise 1 -----");
    exercise1();
    std::println("\n----- Exercise 2 -----");
    exercise2();
    std::println("\n----- Exercise 3 -----");
    exercise3();
    std::println("\n----- Exercise 4 -----");
    exercise4();


    return 0;
}
