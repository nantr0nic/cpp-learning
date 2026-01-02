#include <thread>
#include <mutex>
#include <vector>
#include <print>
#include <functional>

std::mutex g_mtx;

void thread_func(const int i) {
    using namespace std::chrono_literals;
    {
        std::lock_guard<std::mutex> lock(g_mtx);
        std::println("running thread #{}: {}", i, std::this_thread::get_id());
    }

    std::this_thread::yield();
    std::this_thread::sleep_for(2s);

    {
        std::lock_guard<std::mutex> lock(g_mtx);
        std::println("done in thread #{}: {}", i, std::this_thread::get_id());
    }
}

template <typename T>
struct container {
    std::mutex mtx;
    std::vector<T> data;
};

template <typename T>
void move_between(container<T>& c1, container<T>& c2, const T value) {
    // std::lock(c1.mtx, c2.mtx);
    // const std::lock_guard<std::mutex> l1(c1.mtx, std::adopt_lock);
    // const std::lock_guard<std::mutex> l2(c2.mtx, std::adopt_lock);
    const std::scoped_lock lock(c1.mtx, c2.mtx);
    
    c1.data.erase(
        std::remove(c1.data.begin(), c1.data.end(), value), c1.data.end()
    );
    c2.data.push_back(value);
}

int main() {
    std::vector<std::thread> threads;

    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(thread_func, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::println("-----------------");

    container<int> c1;
    c1.data.push_back(1);
    c1.data.push_back(2);
    c1.data.push_back(3);

    container<int> c2;
    c2.data.push_back(4);
    c2.data.push_back(5);
    c2.data.push_back(6);

    std::println("c1: {}\nc2: {}", c1.data, c2.data);

    std::thread t1(move_between<int>, std::ref(c1), std::ref(c2), 3);
    std::thread t2(move_between<int>, std::ref(c2), std::ref(c1), 6);

    t1.join();
    t2.join();

    std::println("c1: {}\nc2: {}", c1.data, c2.data);
}
