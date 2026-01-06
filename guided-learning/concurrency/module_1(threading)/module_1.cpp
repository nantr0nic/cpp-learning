#include <thread>
#include <print>
#include <chrono>
#include <string>

// To save space I'm not going to save previous versions of the various tasks.
// Module 1 task_a() had no parameters, slept for 2 seconds.
// Module 1.5:
void task_a(const std::string& name, int duration_ms) {
    std::println("{} starting.", name);
    std::this_thread::sleep_for(std::chrono::milliseconds(duration_ms));
    std::println("{} finished!", name);
}

void task_b() {
    std::println("Task B starting");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::println("Task B finished");
}

int main() {
    // Module 1
    // std::jthread a_thread(task_a);
    // task_b();
    
    // Module 1.5
    std::jthread thread_A(task_a, "Worker 1", 500);
    std::jthread thread_B(task_a, "Worker 2", 1500);
    
    
    return 0;
}

// Answers to guided questions:

/*              "Module 1"
    Task B finishes first because task A is spawned on a background thread that
    is 'non-blocking'. Which means the program spawns a thread that begins to 
    execute the function task_a() but instead of being blocked or waiting for
    the completion of task_a() it continues to the next line of execution where
    task_b() is being called on the main thread.
*/

/*              "Module 1.5"
    Question: Since we are now running two background threads and the main 
    thread will immediately hit return 0, what keeps the program from exiting 
    before the workers are done?
    
    My answer: The destructor for jthread handles joining the threads back into
    main(). At the "return 0" line the main thread is actively blocked by the
    destructors for thread_A and thread_B because they have provided the instru-
    ction to join but the threads are still executing instructions (task_a()).
    Once one thread then the other complete their instructions, they are joined
    into main() and the main thread is UN-blocked only then executing "return 0"
    which ends the program.
*/