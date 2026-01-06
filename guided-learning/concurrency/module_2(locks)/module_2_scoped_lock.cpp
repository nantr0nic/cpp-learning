// Trying scoped_lock with multiple locks

#include <thread>
#include <mutex>
#include <print>

std::mutex mut1;
std::mutex mut2;

int account_A { 10000 };
int account_B { 1000 };

void transfer_AtoB(int amount) {
    std::println("Transferring {}", amount);
    std::scoped_lock lock(mut1, mut2);
    account_A -= amount;
    account_B += amount;
}

int main() {
    std::println("A: {}\n B: {}\n", account_A, account_B);
    
    std::jthread worker(transfer_AtoB, 750);
    worker.join();
    
    std::println("A: {}\n B: {}\n", account_A, account_B);
    return 0;
}