#include <thread>
#include <chrono>
#include <print>
#include <iostream>
#include <functional>

inline void print_time() {
    auto now = std::chrono::system_clock::now();
    // auto stime = std::chrono::system_clock::to_time_t(now);
    // auto ltime = std::localtime(&stime);
    // std::cout << std::put_time(ltime, "%c") << std::endl;
    
    std::println("print_time: {:%c}", now);
}

// using C++23's println which IS "thread-safe"
void func1() {
    std::println("thread (1) func without params");
}

void func2(const int i, const double d, const std::string s) {
    std::println("func2!\ni: {}\nd: {}\ns: {}", i, d, s);
}

// cout is NOT "thread-safe" so fun to see what happens
void func1_cout() {
    std::cout << "thread (1) func without params" << 'n';
}

void func2_cout(int const i, double const d, std::string const s) {
    std::cout << "func2!\ni: " << i << "\nd: " << d << "\ns: " << s << '\n';
}

void func3(int& i) {
    i *= 2;
    std::println("{}", i);
}

void func4() {
    using namespace std::chrono;
    
    print_time();
    std::this_thread::sleep_for(2s);
    print_time();
}

void func5() {
    using namespace std::chrono;
    print_time();
    std::this_thread::sleep_until(
        std::chrono::system_clock::now() + 2s
    );
    print_time();
}

void func6(std::chrono::seconds timeout) {
    auto now = std::chrono::system_clock::now();
    auto then = now + timeout;
    do {
        std::this_thread::yield();
    } while (std::chrono::system_clock::now() < then);
    print_time();
}

int main() {
    std::thread t1(func1);
    std::thread t2([]() {
        std::println("thread (2) func without params");
        //std::cout << "thread (2) func without params" << '\n';
    });
    std::thread t3(func2, 42, 42.0, "42");
    
    //t1.join();
    t2.join();
    t3.join();
    
    std::println("-------------");
    
    int n = 42;
    
    std::thread t4(func3, std::ref(n));
    std::thread t5(func4);
    std::thread t6(func5);
    
    //std::this_thread::sleep_for(std::chrono::seconds(10));
    
    t4.join();
    t5.join();
    t6.join();
    
    std::println("-------------");
    
    std::thread t7(func6, std::chrono::seconds(2));
    
    t7.join();
    print_time();
    
    std::println("-------------");
    
    std::thread t8(func6, std::chrono::seconds(2));
    
    print_time();
    t8.join();
    
    std::println("-------------");
    
    t1.join();
    
    std::println("Done");
    return 0;
}