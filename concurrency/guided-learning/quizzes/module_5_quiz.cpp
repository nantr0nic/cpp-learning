#include <chrono>
#include <thread>
#include <atomic>
#include <print>
#include <vector>
#include <random>

std::atomic<int> g_sum{ 0 };
static std::atomic<int> max_val{ 0 };

int main() {
    // // Question 1
    // using namespace std::chrono;
    // auto count_start_time = high_resolution_clock::now();
    // {
    //     std::vector<std::jthread> workers;
    //     const int thread_count{ 10 };
    //     for (int i = 0; i < thread_count; ++i) {
    //         workers.emplace_back([]() {
    //             for (int j = 0; j < 100000; ++j) {
    //                 // std::scoped_lock lock(mut); // slower but "concurrent"
    //                 g_sum++;
    //                 if (j == 99999) {
    //                     std::println("Thread {} Finished", std::this_thread::get_id());
    //                 }
    //             }
    //         });
    //     }
    // }
    // auto count_done_time = high_resolution_clock::now();
    // auto count_time = duration_cast<milliseconds>(count_done_time - count_start_time).count();
    // std::println("Sum result: {} (expecting 1,000,000)", g_sum.load());
    // std::println("Time: {}ms\n\n", count_time);

    // // Question 2
    // {
    //     std::atomic<bool> running{ true };

    //     std::jthread worker1([&running]() {
    //         while (running) {
    //             std::println("Working...");
    //             std::this_thread::sleep_for(std::chrono::seconds(2));
    //             running = false;
    //         }
    //         std::println("Worker 1 finished and running is flipped!");
    //     });

    //     std::jthread worker2([&running]() {
    //         while (running) {
    //             std::this_thread::sleep_for(std::chrono::milliseconds(250));
    //             std::println("Other thread working...");
    //         }
    //         std::println("Other thread finished!");
    //     });

    //     std::jthread worker3([&running]() {
    //        std::this_thread::sleep_for(std::chrono::seconds(4));
    //        if (!running) {
    //            std::println("Not running! Atomic worked.");
    //        }
    //     });
    // }

    // Question 3
    {
        std::vector<std::jthread> workers;
        const int num_workers{ 10 };
        for (int i = 0; i < num_workers; ++i) {
            workers.emplace_back([i]() {
                // Need to setup thread-local random gen
                // static initializes once per thread
                // thread_local means each thread gets is own copy
                static thread_local std::random_device rd;
                static thread_local std::mt19937 gen(rd());
                std::uniform_int_distribution<> dist(1, 1000000);

                for (int j = 0; j < 10; ++j) {
                    const int new_val = dist(gen);
                    int current_max = max_val.load();
                    if (new_val > current_max) {
                        while (!max_val.compare_exchange_weak(current_max, new_val)) {
                            if (new_val <= current_max) {
                                break;
                            }
                        }
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                    std::println("(Thread #{}:{}) New_val: {} / Current_max: {}", i, j, new_val, current_max);
                }
            });
        }
    }
    std::println("Final max_val: {}", max_val.load());

    std::println("Finished!");
    return 0;
}
