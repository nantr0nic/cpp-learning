// Module 6 Quiz -- async and future
#include <future>
#include <print>
#include <stdexcept>
#include <vector>
#include <exception>
#include <iostream>

void risky_task() {
    throw std::runtime_error("Error!");
}

int main(){
    // Question #1
    {
        const int sq_num{ 422 };
        std::future<int> square_result = std::async(std::launch::async, [](){ return sq_num * sq_num; });
        std::println("Square of {} is {}", sq_num, square_result.get());
    }

    // Question #2
    {
        const std::vector<int> large_vec(1000000, 1);
        std::future<int> first_half = std::async(std::launch::async, [&large_vec](){
            int result{ 0 };
            for (size_t i = 0; i < large_vec.size() / 2; ++i) {
                result += large_vec[i];
            }
            return result;
        });
        // vvv this was a mistake b/c it could just be done on the main thread (2 total threads instead of 3)
        // std::future<int> second_half = std::async(std::launch::async, [&large_vec](){
        //     int result{ 0 };
        //     for (size_t i = large_vec.size() / 2; i < large_vec.size(); ++i) {
        //         result += large_vec[i];
        //     }
        //     return result;
        // });
        int second_half{ 0 };
        for (size_t i = large_vec.size() / 2; i < large_vec.size(); ++i) {
            second_half += large_vec[i];
        }
        const int vec_total = first_half.get() + second_half;
        std::println("The sum of all elements in large_vec is: {}", vec_total);
    }

    // Question 3
    {
        std::future<void> risky_future = std::async(std::launch::async, risky_task);
        try {
            risky_future.get();
        } catch (const std::exception& e)
        {
            std::println(std::cerr, "Exception thrown: {}", e.what());
        }
    }

    return 0;
}

/*
#1: Use std::async to launch a background task that calculates the square of
a number (e.g., 422) and returns it. In main, call .get() to retrieve and print
the result.

#2 (Parallel Sum): Create a large std::vector<int> (e.g., 1 million 1s).
Launch one std::async task to sum the first half of the vector. Have the main
thread sum the second half. Add the two results together.

#3 (The Crash Reporter): Write a function risky_task() that purposely throws
a std::runtime_error. Launch it using std::async. In main, wrap the .get() call
in a try/catch block to demonstrate that the exception is successfully
"teleported" from the background thread to the main thread.
*/
