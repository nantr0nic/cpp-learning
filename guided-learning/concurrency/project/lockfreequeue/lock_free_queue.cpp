#include "lock_free_queue.hpp"

#include <vector>
#include <string>
#include <optional>

LockFreeQueue::LockFreeQueue(size_t cap) 
    : capacity(cap)
    , buffer(cap) 
{ /* empty */ }

bool LockFreeQueue::push(std::string item) {
    size_t current_head = head.load();
    size_t next_head = (current_head + 1) % capacity;
    
    if (next_head == tail.load()) {
        // ring is full
        return false;
    }
    
    buffer[current_head] = std::move(item);
    head.store(next_head);
    return true;
}

std::optional<std::string> LockFreeQueue::pop() {
    size_t current_tail = tail.load();
    size_t next_tail = (current_tail + 1) % capacity;
    
    if (current_tail == head.load()) {
        // ring is empty
        return std::nullopt;
    }
    
    std::string item = std::move(buffer[current_tail]);
    tail.store(next_tail);
    return item;
}