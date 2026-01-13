// Module 4 Quiz -- Signaling

#include <thread>
#include <condition_variable>
#include <vector>
#include <mutex>
#include <print>
#include <chrono>
#include <random>

std::mutex mut;
std::condition_variable con_v;
bool ready{ false };
int threads_ready{ 0 };
bool ping_next{ true };

void ping(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        std::unique_lock<std::mutex> lock(mut);
        con_v.wait(lock, [](){ return ping_next; });
        std::println("Ping!");
        ping_next = false;
        lock.unlock();
        con_v.notify_one();
    }
}

void pong(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        std::unique_lock<std::mutex> lock(mut);
        con_v.wait(lock, [](){ return !ping_next;});
        std::println("Pong!");
        ping_next = true;
        lock.unlock();
        con_v.notify_one();
    }
}

void reached_checkpoint(int thread_no, int interval) {
    std::unique_lock<std::mutex> lock(mut);
    std::println("(Thread #{}) Reached checkpoint! -- \"Worked\" for {} seconds.", thread_no, interval);
    threads_ready++;
    if (threads_ready == 5) {
        con_v.notify_all();
    }
    con_v.wait(lock, [](){ return threads_ready == 5; });
    std::println("(Thread #{}) Re-awoken!", thread_no);
};

int main() {
    // Question #1
    {
        const int num_threads{ 5 };
        std::vector<std::jthread> workers;
        workers.reserve(5);
        for (int i = 0; i < num_threads; ++i) {
            std::scoped_lock lock(mut);
            workers.emplace_back([](){
                std::println("Thread ({}) Spawned.", std::this_thread::get_id());
                std::unique_lock<std::mutex> worker_lock(mut);
                con_v.wait(worker_lock, [](){ return ready; });
                std::println("Thread ({}) Started!", std::this_thread::get_id());
            });
        }
        std::println("Main thread sleeping for 2 seconds...");
        std::this_thread::sleep_for(std::chrono::seconds(2));
        ready = true;
        con_v.notify_all();
    }

    // Question #2
    {
        const int iterations{ 10 };
        std::jthread ping_thread(ping, iterations);
        std::jthread pong_thread(pong, iterations);
    }

    // Question #3
    {
        const int n_threads{ 5 };
        std::vector<std::jthread> workers;
        workers.reserve(5);
        for (int i = 0; i < n_threads; ++i) {
            workers.emplace_back([i](){
                static thread_local std::random_device rd;
                static thread_local std::mt19937 gen(rd());
                static thread_local std::uniform_int_distribution<> dist(2,8);
                const int interval = dist(gen);
                std::this_thread::sleep_for(std::chrono::seconds(interval));
                reached_checkpoint(i, interval);
            });
        }
    }


    std::println("Finished!");
    return 0;
}
/*
#1 (The Starter Gun): Spawn 5 threads. Have them all perform condition.wait()
immediately. In the main thread, sleep for 2 seconds, then call notify_all() to
wake them all up at once. They should print "Started!" and exit.

#2 (Ping-Pong): Create two threads. Thread A prints "Ping". Thread B prints
"Pong". Use a condition variable (and a boolean flag/state) to force them to
alternate strictly: Ping, Pong, Ping, Pong... for 10 iterations.

#3 (The Barrier): Create a function reached_checkpoint(). Spawn 5 threads.
Each thread does some work (sleeps random time) and calls the function.
Crucial Rule: No thread is allowed to return from that function until all 5
threads have entered it. (This effectively pauses the fast threads until the
slow ones catch up).
*/
