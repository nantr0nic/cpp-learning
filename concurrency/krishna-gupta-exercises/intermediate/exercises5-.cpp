// I got tired of fighting visual studio's editor so syntax is messy

/*
5. Simulate a dining philosophers problem.
6. Readers-Writers problem using std::shared_mutex.
7. Thread pool implementation (basic).
*/

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <print>
#include <functional>
#include <atomic>

struct ThreadPool {
public:
    explicit ThreadPool(int threads_no) { 
		process_pool();
    }

	~ThreadPool() { 
		stop_flag = true;
        c_v.notify_all();
	}

	void enqueue(std::function<void()> task) {
		{
			std::lock_guard<std::mutex> lock(mut);
			task_queue.emplace(std::move(task));
		}
		c_v.notify_one();
	};

	bool const empty() { return task_queue.empty(); };

private:
        void process_pool() {
          while (true) {
		  
		  }
	}

	std::queue<std::function<void()>> task_queue;
	std::mutex mut;
	std::condition_variable c_v;
	std::atomic<bool> stop_flag{ false };
	std::thread worker1;
    std::thread worker2;
};

/*
ThreadPool starts with an empty queue and a number of available workers/threads
 - empty queue is default initialized
 - initialize workers with empty lambda?

 process_pool must loop until stop_flag is true or object is destroyed

 what is protected by the locks? -- the queue and stop_flag (but its atomic so ok)

 lock on enqueue -> lock from thread taking front task from queue (then pop it after move)

*/