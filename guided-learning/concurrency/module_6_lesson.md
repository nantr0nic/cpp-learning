# Module 6: ```std::async``` and ```std::future```
**Futures** are for getting a return value from a background task. Or, if we
want a thread to "return a value" we __could__ do it using thread, mutex, and 
condition_variable -- but it's safer and **easier** to use ```std::async``` and 
```std::future```. thread and jthread **ignore return values** -- they only play
with void return types. 

There was a way to ["get a return value"](#pre-futures-example) before std::future.


## Definitions
- ```std::async```: A high-level function that runs a task (potentially on a new
thread) and gives you a std::future representing the result. This is the "Launcher".
- ```std::future<T>```: A handle to a result that will exist in the future. 
It's like a claim check. You hold it now, and eventually, you turn it in to get 
the result. This is the "Handle". **It is a One-Time Use Object!** It becomes
**invalid** after it returns. If need to access multiple times, then use 
```std::shared_future```.
- ```.get()```: The method you call on the future to retrieve the value. 
Crucially, if the value isn't ready, ```.get()``` will block (wait) until it is.

## Examples
**Without Futures**
```cpp
int result;
std::mutex mut;
void worker() {
    int temp = calculate();
    lock_guard lock(mut);
    result = temp;
}
// Main has to wait/join/lock to read 'result'.
```

**With Futures**
```cpp
std::future<int> result_future = std::async(calculate);
// Do other work...
int result = result_future.get(); // Blocks if not ready. Done.
```

#### pre-futures-example
This is the "pre-futures" way to have gotten a value back from a worker thread:
```cpp
void square_workaround(int x, int& result) { // Reference to result
    result = x * x; 
}

int main() {
    int my_result = 0;
    std::jthread t(square_workaround, 10, std::ref(my_result));
    // The thread fills 'my_result' while we wait or do other work.
} // t joins here, my_result is now 100
```
You pass an argument by reference and ask the thread to fill it. This creates an
"empty" variable just to hold answers. It forces you to mix inputs and outputs
in the argument list.

---

## Syntax and such
1. ```std::async``` (The Launcher) -- This is a function that **starts the task**.
```cpp
// Syntax:
// std::async(LaunchPolicy, Function, Arguments...);

auto handle = std::async(std::launch::async, my_function, 10, "hello");
```
- **Launch Policy**: This is the most critical part.
- - ```std::launch::async```: **Forces a new thread.** This guarantees parallelism.
- - ```std::launch::deferred```: **Lazy evaluation.** It does not create a thread. It runs the function synchronously on the main thread only when you ask for the result later.

    (If you omit the policy, the compiler decides. Always be explicit if you want a background thread!)

- **Function & Args**: Passed exactly like ```std::jthread```.

2. ```std::future<T>``` (The Handle) -- This is the object returned by ```std::async```.
It represents a value of type ```T``` that will exist eventually.
```cpp
// Syntax:
// std::future<ReturnType> variable_name;

std::future<int> result_handle = std::async(...);
```