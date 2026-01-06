#include <string>
#include <iostream>

// First iteration of Link
class Link {
public:
    std::string value;

    Link(const std::string& v, Link* p = nullptr, Link* s = nullptr)
        : value{ v }, prev{ p }, succ{ s }
        { }
    
//private:
    Link* prev;
    Link* succ;
};

// insert function
Link* insert_incomplete(Link* p, Link* n)      // insert n before p (incomplete)
// incomplete because doesn't handle cases with nullptrs
{
    // forward links
    n->succ = p;        // p comes after n
    p->prev->succ = n;  // n comes after what used to be p's predecessor
    // back links
    n->prev = p->prev;  // p's predecessor becomes n's predecessor
    p->prev = n;        // n becomes p's predecessor
    return n;
}

Link* insert(Link* p, Link* n)      // insert n before p; return n
{
    if (n == nullptr)
        return p;
    if (p == nullptr)
        return n;
    n->succ = p;        // p comes after n
    if (p->prev)
        p->prev->succ = n;
    n->prev = p->prev; // p's predecessor becomes n's predecessor
    p->prev = n;        // n becomes p's predecessor
    return n;
}

Link* add(Link* p, Link* n)         // insert n after p; return n
{
    if (n == nullptr)
        return p;
    if (p == nullptr)
        return n;
    n->prev = p;            // p comes before n
    n->succ = p->succ;      // push p's successor to be n's successor (including nullptr)
    if (p->succ)
        p->succ->prev = n;  // p's successor's predecessor becomes n
    p->succ = n;            // p's successor becomes n
    return n;
}

Link* erase(Link* p)    // remove *p from list; return p's successor
{
    if (p == nullptr)
        return nullptr;
    if (p->succ)
        p->succ->prev = p->prev;
    if (p->prev)
        p->prev->succ = p->succ;
    return p->succ;
}

Link* find(Link* p, const std::string& s)    // find s in list; return nullptr for "not found"
{
    while (p)
    {
        if (p->value == s)
            return p;
        p = p->succ;
    }
    return nullptr;
}

Link* advance(Link* p, int n)   // move n positions in list; return nullptr for "not found"
// positive n moves forward, negative backward
{
    if (p == nullptr)
        return nullptr;
    while (0 < n)
    {
        --n;
        if (p->succ)
            p = p->succ;
        return nullptr;
    }
    while (n < 0)
    {
        ++n;
        if (p->prev)
            p = p->prev;
        return nullptr;
    }
    return p;
}

void print_all(Link* p)
{
    std::cout << "{ ";
    while (p)
    {
        std::cout << p->value;
        if ((p = p->succ))
            std::cout << ", ";
    }
    std::cout << " }";
}

int main()
{
    // // First Link build...
    // Link* norse_gods = new Link{"Thor", nullptr, nullptr};
    // // right hand is evaluated before the assignment operation so norse_gods (below) V
    // //      still points to the Link above ^
    // norse_gods = new Link{"Odin", nullptr, norse_gods};
    // // NOW norse_gods points to the Link with "Odin"
    // // vvv this goes: Odin's succ which is Thor and the prev of that Thor, assign it Odin
    // norse_gods->succ->prev = norse_gods;
    // norse_gods = new Link{"Freja", nullptr, norse_gods};
    // norse_gods->succ->prev = norse_gods;

    // // Second Link build now using insert()
    // Link* norse_gods = new Link{"Thor"};
    // norse_gods = insert(norse_gods, new Link{"Odin"});
    // norse_gods = insert(norse_gods, new Link{"Freja"});

    // ----- 15.7.2 ----- //
    Link* norse_gods = new Link{"Thor"};
    norse_gods = insert(norse_gods, new Link{"Odin"});
    norse_gods = insert(norse_gods, new Link{"Zeus"});
    norse_gods = insert(norse_gods, new Link{"Freja"});

    Link* greek_gods = new Link{"Hera"};
    greek_gods = insert(greek_gods, new Link{"Athena"});
    greek_gods = insert(greek_gods, new Link{"Mars"});
    greek_gods = insert(greek_gods, new Link{"Poseidon"});

    Link* p = find(greek_gods, "Mars");
    if (p)
        p->value = "Ares";

    Link* q = find(norse_gods, "Zeus");
    if (q)
    {
        if (q == norse_gods)
            norse_gods = q->succ;
        erase(q);
        greek_gods = insert(greek_gods, q);
    }

    print_all(norse_gods);
    std::cout << '\n';

    print_all(greek_gods);
    std::cout << '\n';

    return 0;
}