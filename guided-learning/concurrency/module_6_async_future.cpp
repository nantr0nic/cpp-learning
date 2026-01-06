#include <future>
#include <print>
#include <chrono>
#include <thread>

int square(int x) {
    std::println("Computing...");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return x * x;
}

int main() {
    std::future<int> result_handle = std::async(std::launch::async, square, 10);
    std::println("Main thread doing other work...");

    std::println("Result: {}", result_handle.get());
    // std::println("Result: {}", result_handle.get()); // <== this will crash because future is one-time!

    // using shared_future
    std::shared_future<int> shared_result = std::async(std::launch::async, square, 5);
    std::println("Main thread doing other work again...");
    std::println("Shared result: {}", shared_result.get());
    std::println("Shared result: {}", shared_result.get());


    // moving into regular int for two prints
    std::future<int> result_handle_B = std::async(std::launch::async, square, 10);
    std::println("Main thread doing other work again again...");
    int result_int = result_handle_B.get();

    std::println("Second result: {}", result_int);
    std::println("Second result: {}", result_int);

    return 0;
}
