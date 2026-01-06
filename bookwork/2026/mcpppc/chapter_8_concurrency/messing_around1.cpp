#include <thread>
#include <mutex>
#include <functional>
#include <fstream>
#include <string>
#include <print>

void read_file(const std::string& file_name) {
    std::string line {};
    std::ifstream ifs {file_name};
    if (!ifs.is_open()) {
        std::println("Can't open {}", file_name);
        return;
    }
    while (std::getline(ifs, line)) {
        std::println("{}", line);
    }
}

template <typename T>
void read_to_vector(const std::string& file_name, std::vector<T>& vec) {
    std::string line {};
    std::ifstream ifs {file_name};
    if (!ifs.is_open()) {
        std::println("Can't open {}", file_name);
        return;
    }
    while (std::getline(ifs, line)) {
        vec.push_back(line);
    }
}

void write_line_to_file(const std::string& file_name, const std::string& line) {
    std::ofstream ofs {file_name, std::ios::app};
    if (!ofs.is_open()) {
        std::println("Can't open {}", file_name);
        return;
    }
    ofs << "\n" << line;
}

void reset_file_to_original(const std::string& file_name, const std::string& original_file_name) {
    std::ofstream ofs {file_name, std::ios::out};
    if (!ofs.is_open()) {
        std::println("Can't open {}", file_name);
        return;
    }
    std::ifstream ifs {original_file_name};
    if (!ifs.is_open()) {
        std::println("Can't open {}", original_file_name);
        return;
    }
    std::string line {};
    while (std::getline(ifs, line)) {
        ofs << line << "\n";
    }
}

int main() {
    std::string file_name {"some_data.txt"};
    std::string original_file_name {"some_data_original.txt"};
    reset_file_to_original(file_name, original_file_name);

    std::println("1. Reading file");
    read_file(file_name);

    std::println("2. Populating a vector with the lines from file.");
    std::vector<std::string> lines_from_file;
    read_to_vector<std::string>(file_name, lines_from_file);
    std::println("Vector: {}", lines_from_file);

    std::println("3. Writing a line to the file.");
    write_line_to_file(file_name, "This is a line added from a C++ program!");

    std::println("4. Reading the file again.");
    read_file(file_name);

    std::println("----------------------");
    std::println("Now the threading section");
    std::println("----------------------");

    std::println("5. Making 3 std::threads that each write a line to the file.");

    std::thread t1(write_line_to_file, file_name, "A line from thread #1");
    std::thread t2(write_line_to_file, file_name, "A line from thread #2");
    std::thread t3(write_line_to_file, file_name, "A line from thread #3");

    t1.join();
    t2.join();
    t3.join();

    std::println("6. Let's check the file:");
    read_file(file_name);

    std::vector<std::string> vec2 {};

    std::println("7. Let's make threads that read and write to the file at the same time.");
    std::jthread t4(read_file, file_name);
    std::jthread t5(write_line_to_file, file_name, "-=-=-= Thread 5 line =-=-=-");
    std::jthread t6(read_to_vector<std::string>, file_name, std::ref(vec2));


    std::println("8. Let's do that again but now with locks.");
    std::mutex mtx;
    {
        std::println("    8.1 Scope lock, thread 7, reading file:");
        std::jthread t7([&mtx, &file_name]() {
            std::scoped_lock<std::mutex> thread_lock(mtx);
            read_file(file_name);
        });
    }
    {
        std::println("    8.2 Scope lock, thread 8, writing lines:");
        std::vector<std::jthread> threads;
        std::string line = "A line from thread #";

        for (int i = 1; i <= 3; ++i) {
            threads.push_back(std::jthread([&mtx, &file_name, i, line]() {
                // Worker thread must lock the mutex
                std::scoped_lock<std::mutex> thread_lock(mtx);
                write_line_to_file(file_name, line + std::to_string(i));
                // Lock releases automatically when thread exits/finishes
            }));
        }
    }
    {
        std::println("    8.3 Lock guard, thread 9, reading file to vector:");
        std::jthread t9([&mtx, &file_name, &vec2]() {
            std::scoped_lock<std::mutex> thread_lock(mtx);
            read_to_vector<std::string>(file_name, std::ref(vec2));
            });
        // race condition:
            // std::println("\n    Vec2 now reads: {}", [&vec2]() {
            //     std::string result;
            //     for (const auto& line : vec2) {
            //         result += "\n" + line;
            //     }
            //     return result;
            // }());
    }
    std::println("\n    Vec2 now reads: {}", [&vec2]() {
        std::string result;
        for (const auto& line : vec2) {
            result += "\n" + line;
        }
        return result;
    }());

    return 0;
}
