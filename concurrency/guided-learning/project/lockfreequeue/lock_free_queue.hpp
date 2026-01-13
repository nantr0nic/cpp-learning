#include <atomic>
#include <vector>
#include <string>
#include <optional>

class LockFreeQueue {
public:
    explicit LockFreeQueue(size_t capacity);
    
    bool push(std::string item);
    std::optional<std::string> pop();
    bool empty() { return (head.load() == tail.load()); }
    
private:
    size_t capacity;
    std::vector<std::string> buffer;
    
    std::atomic<size_t> head{ 0 };
    std::atomic<size_t> tail{ 0 };
};