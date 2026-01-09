// Quiz using the ThreadPool class we built
#include "threadpool.hpp"

int main() {
    
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