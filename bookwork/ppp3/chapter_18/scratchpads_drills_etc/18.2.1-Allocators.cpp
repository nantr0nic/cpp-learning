import std;

template<typename T>
class allocator 
{
public:
    // ...
    // allocate space for n objects of type T
    T* allocate(int n) {             
        if (n <= 0)
        {
            return nullptr;
        }
        std::size_t bytes{ (sizeof(T) * static_cast<std::size_t>(n)) };
        return static_cast<T*>(std::malloc(bytes));
    }
    // deallocate n objects of type T starting at p
    void deallocate(T* p, int n) {   
        if (p != nullptr)
        {
            std::free(p);
        }
    }
};

