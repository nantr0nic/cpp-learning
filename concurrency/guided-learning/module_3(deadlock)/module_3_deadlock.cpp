// Module 3 (Deadlocks)

#include <chrono>
#include <thread>
#include <mutex>
#include <print>

std::mutex g_mut1;
std::mutex g_mut2;

void worker_A() {
    std::scoped_lock lock(g_mut1); // <== deadlocks here (B)
    std::println("Worker A has Mutex 1");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::scoped_lock lock2(g_mut2); // <== deadlocks here (A)
    std::println("Worker A now has BOTH Mutex locks!");
}

void worker_B() {
    std::scoped_lock lock(g_mut2); // <== deadlock here (A)
    std::println("Worker B has Mutex 2");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::scoped_lock lock2(g_mut1); // <== deadlocks here (B)
    std::println("Worker B now has BOTH Mutex locks!");
}

void worker_B_fixed() {
    std::scoped_lock lock(g_mut1); // <== use same ORDER of locks as worker_A
    std::println("Worker B has Mutex 1");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::scoped_lock lock2(g_mut2); // <== use same ORDER of locks as worker_A
    std::println("Worker B now has BOTH Mutex locks!");
}

int main() {
    std::jthread thread_one(worker_A);
    // std::jthread thread_two(worker_B);
    std::jthread thread_two(worker_B_fixed);

    thread_one.join();
    thread_two.join();

    // We shouldn't reach this with worker_B vvv
    std::println("Both threads joined.");
    // ^^^ But we should reach it with worker_B_fixed

    return 0;
}

/* "Why does changing the order force them to run one after the other?"

    My answer: Using the "unfixed" version of worker_B, it starts by locking
    g_mut2; then, when it tries to lock g_mut1, it cannot because of worker_A
    having already locked it. So it "sleeps" until g_mut1 is unlocked. Worker_A
    is also operating on the same two locks (in reverse order) so when it tries
    to acquire the lock for g_mut2 it cannot and also "sleeps", waiting for it
    to unlock. They are each waiting for the other and so enter a deadlock.
    
    Changing the order avoids the deadlock because worker_B, by starting with
    the same mutex as worker_A, sleeps at the beginning of its instructions
    waiting for the lock g_mut1 to be released. g_mut1 is only released at the
    end of the scoped_lock's lifetime which is the same as the scope of the
    worker_A function -- thus, worker_B sleeps until worker_A is completely
    done and they avoid entering a waiting state for each other.
*/