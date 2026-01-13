#include <iostream>
#include <thread>
#include <print>
#include <vector>
#include <chrono>
#include <functional>
#include <mutex>
#include <cmath>

void exercise1() {
    std::jthread ex1([](){ std::println("Hello from thread"); });
}

void exercise2() {
    std::vector<std::jthread> workers;
    for (int i = 0; i < 3; ++i) {
        workers.emplace_back([](){
            std::println("Thread ID: {}", std::this_thread::get_id());
        });
    }
}

void exercise3(int repetitions, const std::string& message) {
    std::jthread ex3([repetitions, &message]() {
        for (int i = 0; i < repetitions; ++i) {
            std::println("{}", message);
        }
    });
}

void exercise3_1(int x, int y) {
    std::println("x * y = {}", (x * y));
}

int exercise5() {
    const int array_size{ 5 };
    const int int_array[array_size]{ 2, 4, 6, 8, 10 };
    int array_sum{ 0 };
    std::jthread ex5([int_array, &array_sum]() {
        for (int i : int_array) {
            array_sum += i;
        }
    });
    ex5.join();
    return array_sum;
}

unsigned long long factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

void exercise6() {
    std::jthread ex6_1([](){
        std::println("5! is: {}", factorial(5));
    });
    std::jthread ex6_2([](){
        std::println("9! is: {}", factorial(9));
    });
    std::jthread ex6_3([](){
        std::println("11! is: {}", factorial(11));
    });
}

std::string shared_string{ "This is a shared string" };
std::mutex mut; // we'll use this mutex for several exercises

void exercise7() {
    std::jthread worker_1([](){
        mut.lock();
        std::println("{}", shared_string);
        mut.unlock();
    });
    std::jthread worker_2([](){
        mut.lock();
        shared_string = "This shared string has been modified!";
        mut.unlock();
        std::println("{}", shared_string);
    });
}

int counter{ 0 };

void exercise8() {
    int iterations{ 10000 };
    std::function<void()> increment_counter = [iterations](){
        for (int i = 0; i < iterations; ++i) {
            ++counter;
        }
    };
    {
        std::jthread worker_1(increment_counter);
        std::jthread worker_2(increment_counter);
        std::jthread worker_3(increment_counter);
        // These threads will auto join at the end of the scope, but just to verify
        // that counter doesn't reach 30000 because of a data race, being thorough and
        // manually joining them
        worker_1.join();
        worker_2.join();
        worker_3.join();
    }
    std::println("Counter: {} (should be 30000 but data race will prevent it!)", counter);
}

void exercise9() {
    counter = 0; // reset it back to 0
    int iterations{ 10000 };
    std::function<void()> increment_counter_locked = [iterations](){
        for (int i = 0; i < iterations; ++i) {
            std::lock_guard<std::mutex> lock(mut);
            ++counter;
        }
    };
    {
        std::jthread worker_1(increment_counter_locked);
        std::jthread worker_2(increment_counter_locked);
        std::jthread worker_3(increment_counter_locked);
    }
    std::println("Using lock_guard, counter should hit 30000 this time: {}", counter);
}

void exercise10() {
    std::vector<int> even_numbers;
    std::jthread([&even_numbers](){
        std::unique_lock lock(mut);
        for (int i = 0; i < 42; ++i) {
            if (i % 2 == 0) {
                even_numbers.push_back(i);
            }
        }
        lock.unlock();
        std::println("Taking a short break from finding even numbers up to 42, releasing the lock!");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        lock.lock();
        std::println("Okay, relocked it. Let's print what we found:\n{}", even_numbers);
    });
}

void exercise11(){
    // We did this in exercise9
    exercise9();
}

void exercise12(){
    std::jthread([](){
        for (int i = 0; i <= 100; ++i) {
            if (i % 2 == 0) {
                std::print("{} ", i);
                if (i == 100) {
                    std::println("\n");
                }
            }
        }
    });
    std::jthread([](){
        for (int i = 0; i <= 100; ++i) {
            if (i % 2 == 1) {
                std::print("{} ", i);
                if (i == 99) {
                    std::println("\n");
                }
            }
        }
    });
}

void exercise13() {
    std::function<void(const std::string&)> lamb = [](const std::string& message){
        std::jthread lambda_worker([&message](){ std::println("Is this right? -> {}", message); });
    };
    lamb("I think so!");
    std::jthread experiment(lamb, "omg it does!");
}

void exercise14() {
    std::println("---- single vs multi thread sum performance comparison ----");
    using namespace std::chrono;
    constexpr size_t count{ 2'500'000 };
    std::vector<unsigned long long> large_vec;
    large_vec.reserve(count);
    for (unsigned long long i = 0; i < count; ++i) {
        large_vec.push_back(i);
    }
    {
        std::println("Adding up the ULL int from 0 to 2,500,000");
        {   // SEQUENTIAL
            auto first = high_resolution_clock::now();
            unsigned long long result{ 0 };
            for (auto i : large_vec) {
                result += i;
            }
            auto second = high_resolution_clock::now();
            auto seq_time = duration_cast<milliseconds>(second - first).count();
            std::println("Sequential: {}ms / Result: {}", seq_time, result);
        }
        {   // ASYNC
            auto first = high_resolution_clock::now();
            unsigned long long result{ 0 };
            unsigned long long first_half{ 0 };
            std::jthread calc([&large_vec, &first_half](){
                for (size_t i = 0; i < large_vec.size() / 2; ++i) {
                    first_half += large_vec[i];
                }
            });
            for (size_t i = large_vec.size() / 2; i < large_vec.size(); ++i) {
                result += large_vec[i];
            }
            calc.join();
            result += first_half;
            auto second = high_resolution_clock::now();
            auto async_time = duration_cast<milliseconds>(second - first).count();
            std::println("Async: {}ms / result: {}", async_time, result);
        }
    }
    std::println("----------------");
    std::println("What about a much larger set of numbers? Let's do 100,000,000");
    {
        std::println("Adding up the ULL int from 0 to 100,000,000");
        constexpr size_t count{ 100'000'000 };
        std::vector<unsigned long long> large_vec;
        large_vec.reserve(count);
        for (unsigned long long i = 0; i < count; ++i) {
            large_vec.push_back(i);
        }
        using namespace std::chrono;
        {   // SEQUENTIAL
            auto first = high_resolution_clock::now();
            unsigned long long result{ 0 };
            for (auto i : large_vec) {
                result += i;
            }
            auto second = high_resolution_clock::now();
            auto seq_time = duration_cast<milliseconds>(second - first).count();
            std::println("Sequential: {}ms / Result: {}", seq_time, result);
        }
        {   // ASYNC
            auto first = high_resolution_clock::now();
            unsigned long long result{ 0 };
            unsigned long long first_half{ 0 };
            size_t split_index = large_vec.size() / 2;
            std::jthread calc([&large_vec, split_index, &first_half](){
                for (size_t i = 0; i < split_index; ++i) {
                    first_half += large_vec[i];
                }
            });
            for (size_t i = split_index; i < large_vec.size(); ++i) {
                result += large_vec[i];
            }
            calc.join();
            result += first_half;
            auto second = high_resolution_clock::now();
            auto async_time = duration_cast<milliseconds>(second - first).count();
            std::println("Async: {}ms / result: {}", async_time, result);
        }
    }
    std::println("----------------");
    std::println("What if we do a heavier function? \
                  Let's calculate the sum of square roots of 0 - 100,000,000");
    {
        auto first = high_resolution_clock::now();
        double result{ 0 };
        for (auto i : large_vec) {
            result += std::sqrt(i);
        }
        auto second = high_resolution_clock::now();
        auto seq_time = duration_cast<milliseconds>(second - first).count();
        std::println("Sequential: {}ms / Result: {}", seq_time, result);
    }
    {   // ASYNC
        auto first = high_resolution_clock::now();
        double result{ 0 };
        double first_half{ 0 };
        size_t split_index = large_vec.size() / 2;
        std::jthread calc([&large_vec, split_index, &first_half](){
            for (size_t i = 0; i < split_index; ++i) {
                first_half += std::sqrt(large_vec[i]);
            }
        });
        for (size_t i = split_index; i < large_vec.size(); ++i) {
            result += std::sqrt(large_vec[i]);
        }
        calc.join();
        result += first_half;
        auto second = high_resolution_clock::now();
        auto async_time = duration_cast<milliseconds>(second - first).count();
        std::println("Async: {}ms / result: {}", async_time, result);
    }
    std::println("----------------------");
}

int some_int{ 0 };
int* shared_int = &some_int;

void exercise15_increment(int* shared_value, int n) {
    {
        for (int i = 0; i < n; ++i) {
            std::scoped_lock lock(mut);
            *shared_value += 1;
        }
    }
}

void exercise15() {
    {
        std::vector<std::jthread> workers;
        const int threads{ 12 };
        for (int i = 0; i < threads; ++i) {
            workers.emplace_back([](){
                exercise15_increment(shared_int, 12);
            });
        }
    }
    std::println("*Shared_int and some_int should be 144: {} | {}", *shared_int, some_int);
    std::println("Sanity check: \n shared_int = {:p} \n some_int   = {:p}",
        static_cast<const void*>(shared_int),
        static_cast<const void*>(&some_int));
}

int main() {
    exercise1();
    exercise2();
    exercise3(3, "Ditto");
    std::jthread ex3(exercise3_1, 5, 5);
    ex3.join(); // <-- this is also part of exercise 4
    std::jthread ex4([](){
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            std::println("Exercise 4 background print!");
        }
    });
    ex4.detach();
    std::println("(exercise 5) The sum of an array containing 2, 4, 6, 8, 10 is {}", exercise5());
    exercise6();
    exercise7();
    exercise8();
    exercise9();
    exercise10();
    exercise11();
    std::println("--- Even and odd numbers ---");
    exercise12();
    exercise13();
    exercise14();
    exercise15();

    std::println("Main thread is waiting... Press Enter to quit.");
    std::cin.get();
    return 0;
}
