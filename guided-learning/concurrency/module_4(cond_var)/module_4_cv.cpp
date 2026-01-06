// Build a simple producer/consumer system

#include <thread>
#include <condition_variable>
#include <mutex>
#include <print>
#include <chrono>

bool ready { false };
std::mutex mut;
std::condition_variable c_v;

void producer() {
    std::println("Producer is working...");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
    std::scoped_lock lock(mut);
    ready = true;
    }
    c_v.notify_one();
    std::println("Producer sent signal!");
}

void consumer() {
    std::println("Consumer waiting...");
    std::unique_lock<std::mutex> lock(mut);
    // This lambda is necessary to prevent a "spurious wakeup"
    c_v.wait(lock, [](){ return ready; });
    // the lambda acts like: while (!ready) { cv.wait(lock); }
    std::println("Consumer got the signal!");
}

int main() {
    std::println("Simple producer/consumer example.\n");
    
    std::jthread con_thread(consumer);
    std::jthread pro_thread(producer);
    
    return 0;
}

/* "Why is it important that consumer uses unique_lock instead of lock_guard?" 

    My answer: I don't know but I'll guess based on an assumption. I assume that
    it being called "unique" ensures that only a single thread "owns" the lock's
    unlocked state at a time? My guess was somewhat correct: it is similar to
    unique_ptr in that it models exclusive ownership. lock_guard is simple and
    rigid: locks on creation, unlocks on destruction. Cannot be manually 
    unlocked in between. unique_lock is 'smart' and 'flexible' -- it OWNS the
    mutex but allows you (or the condition variable) to unlock() and lock() it
    essentially whenever you want.
*/