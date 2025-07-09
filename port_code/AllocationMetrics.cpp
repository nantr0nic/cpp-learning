#include <iostream>

struct AllocationMetrics
{
    uint32_t TotalAllocated = 0;
    uint32_t TotalFreed = 0;

    uint32_t CurrentUsage() { return TotalAllocated - TotalFreed; }
};

static AllocationMetrics s_allocation_metrics;

void* operator new(size_t size)
{
    s_allocation_metrics.TotalAllocated += size;
    // std::cout << "(Allocated " << size << " bytes)\n";
    return malloc(size);
}

void operator delete(void* memory, size_t size)
{
    s_allocation_metrics.TotalFreed += size;
    // std::cout << "(DEallocated " << size << " bytes)\n";
    free(memory);
}

static void PrintMemoryUsage()
{
    std::cout << "Memory Usage: " << s_allocation_metrics.CurrentUsage() << " bytes\n";
}

