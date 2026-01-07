#include <thread>
#include <print>
#include <chrono>
#include <vector>

// Question 2
void greeter(const std::string& name, int times) {
    for (int i = 0; i < times; ++i) {
        std::println("Hello {}!", name);
    }
}

int main() {
    {
        // Question 1
        std::vector<std::jthread> workers;
        for (int i = 0; i < 3; ++i) {
            workers.emplace_back([]() {
                std::println("Hello from thread {}", std::this_thread::get_id());
                std::this_thread::sleep_for(std::chrono::seconds(1));
            });
        }
    }
    {
        // Question 2
        std::jthread greet_thread(greeter, "Andy", 5);
    }
    {
        // Question 3
        std::vector<std::jthread> workers;
        const int worker_count{ 10 };
        for (int i = 0; i < worker_count; ++i) {
            workers.emplace_back([i]() {
                std::println("Index: {}", i);
            });
        }
    }

    std::println("Finished!");
    return 0;
}
