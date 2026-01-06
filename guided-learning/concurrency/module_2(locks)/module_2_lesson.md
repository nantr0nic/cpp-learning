# Module 2 - Mutexes / Locking
## ----- DEFINITIONS -----
- "Shared State" => Memory (variables, objects) that is accessed by more than 
                    one thread.
- "Race Condition" => A bug where the output of your program depends on the
                      uncontrollable timing of threads (i.e. who gets to the
                      CPU first).
- "Data Race" => A specific type of race condition. It occurs when:
    1. Two or more threads access the same memory location concurrently.
    2. At least one of them is *writing* (modifying).
    3. No synchronization (locking) is used.
        Result: Undefined Behaviour. 
- "Critical Section" => The specific lines of code that access the shared 
                        resource.
- "Atomic" => An operation that is indivisible. It happens all at once or not
              at all.

## ----- Example -----
Hardware Reality: You might think ```counter++``` is one instruction. 
                  To the CPU, it is usually three:
                  
    LOAD: Read the value from memory into a CPU register.
    ADD: Add 1 to the register.
    STORE: Write the new value back to memory.
    
The Scenario: Imagine counter is 0.
    Thread A loads 0.
    Context Switch happens! Thread A pauses.
    Thread B loads 0.
    Thread B adds 1 and stores 1. (Counter is now 1).
    Context Switch back to A.
    Thread A (still thinking it holds 0) adds 1 and stores 1.
    
Result: Two threads incremented, but the counter is only 1. We lost a count.

## The solution: mutexes!
```std::mutex``` -- the primitive synchronization object.
```std::lock_guard``` (or ```std::scoped_lock```) -- An RAII wrapper that **locks**
the mutex when created and **automatically unlocks** it when destroyed (end of scope).
__Always use these wrappers; never call ```.lock()``` and ```.unlock()``` manually
if you can avoid it.__

### Minimal Example
```cpp
#include <mutex>

int shared_counter = 0;
std::mutex my_mutex; // The guardian of the counter

void increment() {
    // 1. Acquire the lock (wait if someone else has it)
    std::lock_guard<std::mutex> guard(my_mutex);
    
    // 2. Critical Section (Safe zone)
    shared_counter++;
    
    // 3. Lock is automatically released when 'guard' is destroyed here
}
```