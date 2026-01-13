// This is from module 2. It will use atomic instead of mutex.

#include <thread>
#include <print>
#include <atomic>

std::atomic<int> counter { 0 };

void worker(int inc_amt) {
    std::println("Starting worker. Inc amount: {}, Thread ID: {}",
        inc_amt, std::this_thread::get_id());
    for (int i = 0; i < inc_amt; ++i) {
        counter++;
    }
    std::println("Worker finished (ID: {})", std::this_thread::get_id());
}

int main() {
    int increment_amt { 10000 };

    std::println("Initial counter value: {}", counter.load());

    std::jthread thread_1(worker, increment_amt);
    std::jthread thread_2(worker, increment_amt);
    std::jthread thread_3(worker, increment_amt);
    std::jthread thread_4(worker, increment_amt);
    std::jthread thread_5(worker, increment_amt);

    thread_1.join();
    thread_2.join();
    thread_3.join();
    thread_4.join();
    thread_5.join();

    std::println("Final counter value: {}", counter.load());

    return 0;
}
