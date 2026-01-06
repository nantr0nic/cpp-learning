// This is tested and works under folder bookwork/ppp3/chapter_18/scratchpads_drills_etc/18-Vector_T.cpp

template<Element T, typename A>
void Vector<T, A>::push_front(const T& val)
{
    /* I think the only way this is possible, since heap allocated and contiguous, 
    * is to copy it and add val as the first element. */
    T* p = alloc.allocate(sz + 1); // make new space + 1 for new element
    std::uninitialized_move(elem, elem + sz, p + 1);         // copy old to new space but at 2nd spot
    *p = val;   // make first value = val
    // clean up old memory
    std::destroy(elem, elem + sz);
    alloc.deallocate(elem, static_cast<std::size_t>(space));

    elem = p;   // transfer ownership
    ++sz;
}