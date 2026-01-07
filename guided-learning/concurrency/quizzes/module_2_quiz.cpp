#include <thread>
#include <mutex>
#include <print>
#include <vector>

int g_sum{ 0 };

int main() {
    {
        // Question 1
        std::mutex mut;
        std::vector<std::jthread> workers;
        const int thread_count{ 10 };
        for (int i = 0; i < thread_count; ++i) {
            workers.emplace_back([&mut]() {
                std::scoped_lock lock(mut);
                for (int j = 0; j < 100000; ++j) {
                    g_sum++;
                }
            });
        }
    }
    std::println("Sum result: {} (expecting 1,000,000)", g_sum);

    std::println("Finished!");
    return 0;
}
