import std;

template<typename T>
class Counted_ptr
{
private:
    T* object_ptr{ nullptr };
    int* ptr_count{ nullptr };

public:
    Counted_ptr() = delete;
    explicit Counted_ptr(const T& object) 
        : object_ptr{ new T{ object } }
        , ptr_count{ new int{ 1 } }
    { 
        std::println("[!!!] New Counted_ptr constructed.");
    }
    
    // copy constructors, for this simple version of shared_ptr, is where
    // the magic happens
    Counted_ptr(const Counted_ptr<T>& cptr)
        : object_ptr{ cptr.object_ptr }
        , ptr_count{ cptr.ptr_count }
    {
        std::println("[!] Copy constructor called.");
        if (ptr_count)
        {
            ++(*ptr_count);
            std::println("[!!!] Pointer count increased! Currently: {}", *ptr_count);
        }
    }
    Counted_ptr& operator=(const Counted_ptr<T>& cptr) {
        std::println("[!] Copy assignment called.");
        if (this == &cptr)
        {
            return *this;
        }

        if (ptr_count && --(*ptr_count) == 0)
        {
            std::println("[!!] delete being called by copied-from object. (last owner)");
            delete object_ptr;
            delete ptr_count;
        }
        else if (ptr_count)
        {
            std::println("[!!] releasing current object, - {} owners remain", *ptr_count);
        }

        object_ptr = cptr.object_ptr;
        ptr_count = cptr.ptr_count;
        if (ptr_count)
        {
            ++(*ptr_count);
            std::println("[!!!] Pointer count increased! Currently: {}", *ptr_count);
        }
        return *this;
    }

    // Destructor must keep track of count to only delete heap object if last
    ~Counted_ptr() {
        if (ptr_count && --(*ptr_count) == 0)
        {
            std::println("[!!!] Last Counted_ptr! Deleting object.");
            delete object_ptr;
            delete ptr_count;
        }
        else if (ptr_count)
        {
            std::println("[!!!] Pointer count decreased! Currently: {}", *ptr_count);
        }
    }

public:
    T& operator*() const {
        if (!object_ptr)
        {
            throw std::runtime_error{"Dereferencing nullptr!"};
        }
        return *object_ptr;
    }

    T* operator->() const {
        return object_ptr;
    }

    int count() const {
        return ptr_count ? *ptr_count : 0;
    }

};