// Module 4 Quiz -- Signaling

/*
#1 (The Starter Gun): Spawn 5 threads. Have them all perform condition.wait()
immediately. In the main thread, sleep for 2 seconds, then call notify_all() to
wake them all up at once. They should print "Started!" and exit.

#2 (Ping-Pong): Create two threads. Thread A prints "Ping". Thread B prints
"Pong". Use a condition variable (and a boolean flag/state) to force them to
alternate strictly: Ping, Pong, Ping, Pong... for 10 iterations.

#3 (The Barrier): Create a function reached_checkpoint(). Spawn 5 threads.
Each thread does some work (sleeps random time) and calls the function.
Crucial Rule: No thread is allowed to return from that function until all 5
threads have entered it. (This effectively pauses the fast threads until the
slow ones catch up).
*/
