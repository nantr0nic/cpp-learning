#include <string>
#include <chrono>

// Returns the current date and time as a string
//      in the format "2025-04-23 18:50:00"
std::string getCurrentDateTime(const char* format = "%Y-%m-%d")
{
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), format, std::localtime(&time_t_now));
    
    return std::string(buffer);
}