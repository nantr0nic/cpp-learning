/*
Step 1: The broken program. Create a data race.
Step 2: The fix.
*/

// This is Step 2.

#include <thread>
#include <print>
#include <mutex>

int counter { 0 };
std::mutex counter_mutex;

void worker(int inc_amt) {
    std::println("Starting worker. Inc amount: {}, Thread ID: {}",
        inc_amt, std::this_thread::get_id());
    for (int i = 0; i < inc_amt; ++i) {
        // lock_guard is still fine, especially for single locks
        // but guides/tutorials say to stick with scoped_lock if 17+
        std::lock_guard<std::mutex> lock(counter_mutex);
        counter++;
    }
    std::println("Worker finished (ID: {})", std::this_thread::get_id());
}

int main() {
    int increment_amt { 10000 };

    std::println("Initial counter value: {}", counter);

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

    std::println("Final counter value: {}", counter);

    return 0;
}
