// Module 6 Quiz -- async and future

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