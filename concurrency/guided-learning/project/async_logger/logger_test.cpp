#include "AsyncLogger.hpp"

#include <print>
#include <string>
#include <chrono>
#include <thread>

int main() {
    std::string file_name{ "log.txt" };
    AsyncLogger logger(file_name);
    {
        std::jthread log_flood_1([&logger](){
            for (int i = 0; i < 100; ++i) {
                logger.Log("(1) Log message #" + std::to_string(i));
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
            }
        });

        std::jthread log_flood_2([&logger](){
            for (int i = 0; i < 100; ++i) {
                logger.Log("(2) Log message #" + std::to_string(i));
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
            }
        });
    }

    std::println("Finished!");

    return 0;
}
