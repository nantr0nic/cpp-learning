#include <functional>
#include <thread>
#include <mutex>
#include <print>
#include <vector>
#include <chrono>


int g_sum{ 0 };
std::mutex g_mut;

struct Account {
    int balance{1000};
    std::mutex mut;
    // using uint8_t turns out to be less performative than a regular int
    // (at least on 64-bit systems) but just using uint8_t for fun here
    uint8_t id{ 0001 };

    explicit Account(uint8_t id_no) : id(id_no) {};
};

void transfer(Account& from, Account& to, int amount) {
    {
        std::scoped_lock lock(from.mut, to.mut);
        from.balance -= amount;
        to.balance += amount;
    }
    std::println("Transferred {} from Account #{} to Account #{}", amount, from.id, to.id);
    std::println("(Thread ID: {})", std::this_thread::get_id());
}

struct HeavyObject { };

HeavyObject get_resource(HeavyObject*& res) {
    if (res == nullptr) {
        std::scoped_lock lock(g_mut);

        if (res == nullptr) {
            res = new HeavyObject();
            std::println("-> Created new HeavyOjbect! (Thread {})", std::this_thread::get_id());
            return *res;
        }
    }

    std::println("Got HeavyObject!");
    return *res;
}

int main() {
    using namespace std::chrono;
    // Question 1
    auto count_start_time = high_resolution_clock::now();
    {
        std::mutex mut;
        std::vector<std::jthread> workers;
        const int thread_count{ 10 };
        for (int i = 0; i < thread_count; ++i) {
            workers.emplace_back([&mut]() {
                std::scoped_lock lock(mut); // faster but essentially sequential
                for (int j = 0; j < 100000; ++j) {
                    // std::scoped_lock lock(mut); // slower but "concurrent"
                    g_sum++;
                    if (j == 99999) {
                        std::println("Thread {} Finished", std::this_thread::get_id());
                    }
                }
            });
        }
    }
    auto count_done_time = high_resolution_clock::now();
    auto count_time = duration_cast<milliseconds>(count_done_time - count_start_time).count();
    std::println("Sum result: {} (expecting 1,000,000)", g_sum);
    std::println("Time: {}ms\n\n", count_time);

    // Question 2
    Account acc_A(0001);
    Account acc_B(0002);
    Account acc_C(0003);
    {
        std::jthread work1([&acc_A, &acc_B](){ transfer(acc_A, acc_B, 100); }); // A: 900, B: 1100
        std::jthread work2([&acc_A, &acc_C](){ transfer(acc_C, acc_A, 100); }); // A: 1000, C: 900
        std::jthread work3([&acc_A, &acc_B](){ transfer(acc_B, acc_A, 100); }); // A: 1100, B: 1000
        std::jthread work4([&acc_C, &acc_B](){ transfer(acc_B, acc_C, 100); }); // B: 900, C: 1000
    }
    std::println("--- Ending balances ----");
    std::println("A: {}, B: {}, C: {}", acc_A.balance, acc_B.balance, acc_C.balance);
    std::println("(Should be 1100, 900, 1000)\n\n");

    HeavyObject* ho_1{ nullptr };
    auto hoho = new HeavyObject();
    HeavyObject* ho_2{ hoho };
    {
        std::jthread worker1(get_resource, std::ref(ho_1));
        std::jthread worker2(get_resource, std::ref(ho_1));
        std::jthread worker3(get_resource, std::ref(ho_2));
    }
    std::println("Should be 1 \"created new\" and 2 \"Got HeavyObject\" messages");
    delete ho_1;
    delete ho_2;

    std::println("Finished!");
    return 0;
}
