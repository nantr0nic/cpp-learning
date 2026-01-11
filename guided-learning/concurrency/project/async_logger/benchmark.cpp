#include "AsyncLogger.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <iomanip>

void benchmark(int num_threads, int logs_per_thread) {
    const std::string filename = "bench_log.txt";
    
    // Setup
    AsyncLogger logger(filename);
    std::vector<std::jthread> threads;
    threads.reserve(num_threads);

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&logger, logs_per_thread]() {
            std::string payload = "This is a benchmark log message to simulate some data payload.";
            for (int j = 0; j < logs_per_thread; ++j) {
                logger.Log(payload);
            }
        });
    }

    // Wait for all producers to finish pushing to the queue
    for (auto& t : threads) {
        if(t.joinable()) t.join();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    
    // Calculate stats
    std::chrono::duration<double> duration = end_time - start_time;
    double seconds = duration.count();
    long total_logs = num_threads * logs_per_thread;
    double logs_per_sec = total_logs / seconds;

    std::cout << "Threads: " << std::setw(2) << num_threads 
              << " | Total Logs: " << std::setw(8) << total_logs 
              << " | Time: " << std::fixed << std::setprecision(4) << seconds << "s"
              << " | Throughput: " << (int)logs_per_sec << " logs/sec" << std::endl;
}

int main() {
    std::cout << "=== AsyncLogger Benchmark ===" << std::endl;
    std::cout << "Note: Comment out std::println in AsyncLogger::Log for accurate results.\n" << std::endl;

    // Warmup
    benchmark(1, 1000); 

    // Scenarios
    benchmark(1, 100000);    // Single thread heavy load
    benchmark(4, 25000);     // 4 threads (common quad core load)
    benchmark(8, 12500);     // 8 threads (high contention)
    benchmark(16, 10000);    // 16 threads (oversaturation)

    return 0;
}