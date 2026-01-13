# Module 5 (Atomic Variables)

## Definitions
```
These are not exhaustive definitions. They are specifically in relation to atomics.
```
- ```std::atomic<T>``` is a template class that provides atomic operations for a 
given type ```T```. It ensures that operations on the atomic variable are 
performed atomically, preventing data races and other concurrency issues.
- **Lock-Free**: Operations on atomics generally do not use mutexes. __They
never block.__ 
- **Thread-Safe**: You can call ```my_atomic++``` from 100 threads at once, and
it will never lose a count.

## The Big Picture
CPUs have special hardware instructions (like ```LOCK XCHG``` or ```CAS```) that 
can modify a single piece of memory safely across cores without pausing the 
thread or asking the OS for help.

- **Mutex**: "Hey OS, put everyone to sleep while I use the bathroom." This is 
__slow__ but __safe__ (especially for complex tasks).
- **Atomic**: "I'm going to squeeze past you in the hallway really fast." This is
__fast__ and safe but "safe" for simple updates.

## Small example
```cpp
#include <atomic>

std::atomic<int> counter{0}; // Safe global

void worker() {
    for(int i=0; i<1000; ++i) {
        counter++; // No mutex needed! This is thread-safe.
    }
}
```

## Limitation
```std::atomic``` is safe for simple things (like counter) but it can become unsafe.
Example:
```cpp
std::atomic<int> tickets_remaining{ 1 };

void book_ticket() {
    if (tickets_remaining > 0) {             // Step 1: Check
        std::this_thread::sleep_for(1ms);    // (Simulate tiny processing delay)
        tickets_remaining--;                 // Step 2: Decrement
        std::println("Ticket booked! ✅");
    } else {
        std::println("Sold out! ❌");
    }
}
```
If multiple threads are running book_ticket(), a data race condition can occur because
while the variable itself is atomic, the **logic** combining the check and the 
write is **not**. This is a classic bug known as **TOCTOU** (Time of Check to
Time of Use). What can happen is two tickets are sold when only one remains.

Here is the problematic timeline:
1. Thread A checks ```if (tickets_remaining > 0)```. The value is 1. Passes.
2. Thread A gets paused by the OS (context switch).
3. Thread B checks ```if ... ```. Thread A hasn't changed it yet, so it is
still 1. Passes.
4. Thread A wakes up. It executes ```tickets_remaining--```. Value goes from 1
to 0. Prints "Ticket booked!"
5. Thread B wakes up. It executes the decrement. Value goes from 0 to -1. Prints 
"Ticket booked!"