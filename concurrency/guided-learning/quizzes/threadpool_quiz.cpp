// Quiz using the ThreadPool class we built
#include "threadpool.hpp"
#include <print>
#include <thread>
#include <vector>
#include <future>

int main() {
    ThreadPool pool(3);
    
    // Question 1
    {
        for (int i = 0; i < 10; ++i) {
            pool.enqueue([i] {
                std::println("Hello from Task #{} from Thread ({})", i, std::this_thread::get_id());
            });
        }
    }
    
    // Question 2
    {
        // This promise/future setup is necessary because the ThreadPool class isn't templatized
        // and enqueue only accepts std::function<void()>, it can't return an int
        std::vector<std::future<int>> future_vec;
        for (int i = 0; i < 10; ++i) {
            auto promise = std::make_shared<std::promise<int>>();
            future_vec.push_back(promise->get_future());
            pool.enqueue([i, promise]() {
                const int res = i * i;
                promise->set_value(res);
            });
        }
        for (auto& future : future_vec) {
            std::println("Element: {}", future.get());
        }
    }
    
    return 0;
}

/*
Easy: Instantiate your ThreadPool with 3 workers. Submit 10 tasks. Each task 
should simply print "Hello from Task [i]". Verify they all run.

Medium (The Result Collector): Create a std::vector<std::future<int>>. 
Submit 10 tasks to the pool. Each task should calculate i * i and return it. 
(Note: enqueue returns a future). Store these futures in the vector. 
Finally, loop through the vector and print the results to ensure they computed 
correctly.

Hint: Your current enqueue implementation might need to look like the complex 
template version to support return values. If you didn't implement the complex 
enqueue, you can achieve this by passing a std::promise into the task or writing
to a thread-safe std::vector.

Hard (The Recursive Nightmare): (If you are feeling brave). Submit a task that 
calculates Fibonacci(N).

    Logic: 
    If N < 2, return 1.

    Else: Submit two new tasks to the pool to calculate Fib(N-1) and Fib(N-2).

    Warning: If your pool has 4 threads and you submit tasks that wait on other 
    tasks... what happens if all 4 threads are waiting? (This is a theoretical 
    "Deadlock" question—you don't strictly have to code it if you can explain 
    why it would freeze).
*/