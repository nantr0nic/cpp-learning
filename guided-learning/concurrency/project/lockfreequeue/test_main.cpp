#include "asynclogger.hpp"
#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <fstream>
#include <cassert>
#include <filesystem>

void run_correctness_test() {
    const std::string filename = "test_log.txt";
    const int NUM_THREADS = 10;
    const int LOGS_PER_THREAD = 1000;
    const int EXPECTED_LINES = NUM_THREADS * LOGS_PER_THREAD;

    // cleanup previous run
    if (std::filesystem::exists(filename)) {
        std::filesystem::remove(filename);
    }

    std::cout << "Starting Correctness Test..." << std::endl;

    // Scope to ensure AsyncLogger destructor runs and flushes queue
    {
        AsyncLogger logger(filename);
        std::vector<std::jthread> threads;

        for (int i = 0; i < NUM_THREADS; ++i) {
            threads.emplace_back([&logger, i, LOGS_PER_THREAD]() {
                for (int j = 0; j < LOGS_PER_THREAD; ++j) {
                    logger.Log("Thread " + std::to_string(i) + " msg " + std::to_string(j));
                }
            });
        }
        // threads join automatically here
    }

    // Verify the file content
    std::ifstream file(filename);
    std::string line;
    int line_count = 0;
    while (std::getline(file, line)) {
        line_count++;
    }

    std::cout << "Expected lines: " << EXPECTED_LINES << std::endl;
    std::cout << "Actual lines:   " << line_count << std::endl;

    if (line_count == EXPECTED_LINES) {
        std::cout << "[PASS] Log count matches." << std::endl;
    } else {
        std::cerr << "[FAIL] Data loss detected!" << std::endl;
    }
}

int main() {
    run_correctness_test();
    return 0;
}
