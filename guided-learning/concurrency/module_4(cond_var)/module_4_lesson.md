# Module 4 (Signaling and Condition Variable)

## Definitions
- **Signaling**: Signaling is a mechanism used by threads to communicate the 
occurrence of an event or a change in state to other threads.
- - Threads often sleep (block) to save CPU resources while they wait for data.
- - **Signaling** is the act of one thread (the __Producer__) poking the sleeping
thread (the __Consumer__) to say, "Hey! The data you were waiting for is ready now."
- - **Polling (No signal)** is checking every 10 seconds to see package has arrived (if producer is done)
- - **Signaling** is driver (the producer) rings the doorbell (signal) when package arrives.
- - Consumer = Waiter // Producer = Notifier

- **Condition Variable** ```std::condition_variable```: A synchronization primitive 
that allows threads to block (sleep) until another thread notifies them that a 
specific condition (like data_ready == true) is met.
- ```std::unique_lock```: A more flexible wrapper than ```std::lock_guard``` that 
allows for more complex locking scenarios.
- - **Why we need it here**: ```std::condition_variable``` needs to be able to unlock 
the mutex while you are sleeping (so the producer can grab it to set the data) 
and re-lock it when you wake up. ```lock_guard``` cannot unlock manually, 
but ```unique_lock``` can.

## The Big Picture
### The Problem: Waiting for Data
Imagine a "Producer" thread that downloads an image, and a "Consumer" thread that
processes it. The Consumer must wait until the download is finished.

**Approach A**
```cpp
while (!read) { /* check, check, check, check... */}
```
This burns 100% of the CPU core just asking "Are we there yet?" -- wastes resources.

**Approach B**
```cpp
while (!read) {
    std::this_read::sleep_for(100ms);
}
```
This saves CPU, but it introduces **latency**. If the data arrives 1ms after you
fall asleep, you waste 99ms doing nothing before you notice.

**Approach C: Condition Variable**
The Consumer goes to sleep immediately. The Producer sends a Signal (notification)
the exact moment the data is ready, waking the Consumer instantly. Zero CPU waste,
zero latency.

## Syntax
### The Waiter (**Consumer**)
```cpp
std::unique_lock<std::mutex> lock(mut); // <== use unique_lock for cv
// cv.wait(lock, predicate)
// logic: if predicate is false, unlock mut and sleep.
//        when notified, lock mut, check predicate again.
cv.wait(lock, []{ return ready; }); 
// Now we hold the lock and ready is true. Go!
```

### The Notifier (**Producer**)
```cpp
{
    std::lock_guard<std::mutex> lock(mut);
    ready = true;
} // Release lock logic
cv.notify_one(); // Wake up one waiting thread
```