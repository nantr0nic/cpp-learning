#include "threadpool.cpp"

#include <fstream>
#include <vector>
#include <string>
#include <print>
#include <chrono>
#include <filesystem>

const size_t FILE_SIZE = 2ULL * 1024 * 1024 * 1024; // 2 GB
const size_t CHUNK_SIZE = 4 * 1024 * 1024; // 4 MB buffer (RAM friendly)
const int NUM_FILES = 8; // benchmark making eight 1GB files

void create_large_file(int id) {
    std::string filename = "test_file_" + std::to_string(id) + ".bin";
    std::ofstream ofs(filename, std::ios::binary);

    std::vector<char> buffer(CHUNK_SIZE, 0);

    for (size_t i = 0; i < FILE_SIZE / CHUNK_SIZE; ++i) {
        ofs.write(buffer.data(), buffer.size());
    }

    std::println("  --> File {} created.", id);
}

void cleanup_files() {
    for(int i = 0; i < NUM_FILES; ++i) {
        std::filesystem::remove("test_file_" + std::to_string(i) + ".bin");
    }
}

int main() {
    using namespace std::chrono;

    // Test 1 -- sequential (not pooled)
    std::println("----- Starting SEQUENTIAL test -----");
    auto seq_start_time = high_resolution_clock::now();

    for (int i = 0; i < NUM_FILES; ++i) {
        create_large_file(i);
    }

    auto seq_end_time = high_resolution_clock::now();
    cleanup_files();

    // Test 2 -- thread pool
    std::println("----- Starting THREAD POOL test -----");
    auto pool_start_time = high_resolution_clock::now();

    {
        ThreadPool pool(4);
        for (int i = 0; i < NUM_FILES; ++i) {
            pool.enqueue([i]() {
                create_large_file(i);
            });
        }
    }

    auto pool_end_time = high_resolution_clock::now();
    cleanup_files();

    // Results
    auto seq_time = duration_cast<milliseconds>(seq_end_time - seq_start_time).count();
    auto pool_time = duration_cast<milliseconds>(pool_end_time - pool_start_time).count();

    std::println("\n ------- RESULTS ------");
    std::println("Sequential time: {} ms", seq_time);
    std::println("Thread pool time: {} ms", pool_time);

    return 0;
}
