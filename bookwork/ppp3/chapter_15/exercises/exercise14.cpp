/*
***** Chapter 15 Exercises 14 *****

Implement the previous version of Link as a singly-linked list

*/

#include <string>
#include <iostream>

using std::string;

// Link class
class Link 
{
public:
    Link(const string& n, const string& m, const string& v, 
        const string& w, Link* s = nullptr);
    
    ~Link() {};

    Link* insert(Link* head, Link* n);                          // insert n before this object
    Link* add(Link* n);                             // insert n after this object
    Link* erase(Link* h);                                  // remove this object from list

    Link* find(Link* h, const string& s);               // find s in list
    // const Link* find(const string& s) const;   // find s in const list (see _oper.const_)

    // Link* advance(int n); //const;                  // move n positions in list
    Link* next() const { return succ; }

    // Exercise 12
    struct God_struct 
    {
        string name;
        string mythology;
        string vehicle;
        string weapon;
    };

    God_struct God;

private:
    Link* succ;
};

// Free functions declarations
void print_all(Link* p);
void delete_list(Link* p);

int main()
{
    Link* greek_gods = new Link{"Zeus", "Greek", "A Cloud", "lightning"};
    // This is not the most elegant solution. I would create a separate List class
    // but for the purposes of this exercise I'm staying within the text material.
    Link* greek_gods_head = greek_gods;
    greek_gods = greek_gods->add(new Link{"Athena", "Greek", "Chariot", "Spear"});
    greek_gods = greek_gods->insert(greek_gods_head,new Link{"Apollo", "Greek", 
        "Golden Chariot drawn by swans", "Bow"});
    greek_gods = greek_gods->add(new Link{"Helios", "Greek", "Fiery chariot", "The sun"});

    Link* p2 = greek_gods->find(greek_gods_head, "Athena");
    p2->erase(greek_gods_head);

    print_all(greek_gods_head);

    delete_list(greek_gods_head);

    Link* norse_gods = new Link{"Odin", "Norse", "Eight-legged horse Sleipnir", "Gungnir"};
    Link* norse_gods_head = norse_gods;
    norse_gods = norse_gods->add(new Link{"Thor", "Norse", 
        "Chariot pulled by two goats", "Mjolnir"});
    norse_gods = norse_gods->add(new Link{"Heimdall", "Norse", 
        "Rainbow bridge Bifrost", "Hofund"});
    norse_gods = norse_gods->add(new Link{"Tyr", "Norse", "", "Sword and shield"});

    Link* egyptian_gods = new Link{"Ra", "Egyptian", "Solar barque", "Sun Disk and Spear"};
    Link* egyptian_gods_head = egyptian_gods;
    egyptian_gods = egyptian_gods->add(new Link{"Horus", "Egyptian", "", "Harpoon"});
    egyptian_gods = egyptian_gods->add(new Link{"Anubis", "Egyptian", 
        "Runs as a jackal", "Scepter"});
    egyptian_gods = egyptian_gods->add(new Link{"Sekhmet", "Egyptian", 
        "Sometimes rides with Ra", "Flame"});

    print_all(norse_gods_head);
    print_all(egyptian_gods_head);

    delete_list(norse_gods_head);
    delete_list(egyptian_gods_head);

    return 0;
}

// ----- Free functions definitions ----- //

void print_all(Link* p)         // must pass head of list
{
    std::cout << "{\n";
    while (p)
    {
        std::cout << p->God.name << ", " << p->God.mythology << ", " 
        << p->God.vehicle << ", " << p->God.weapon;
        if ((p = p->next()))
            std::cout << '\n';
    }
    std::cout << "\n}";
}

void delete_list(Link* p)       // must pass head of list
{
    // Delete elements
    while (p)
    {
        Link* next = p->next();
        std::cout << "\nDeleting " << p->God.name << " at " << p << '\n';
        delete p;
        p = next;
    }
}

// ----- Link Definitions ----- //

Link::Link(const string& n, const string& m, const string& v, 
        const string& w, Link* s)
    : God{n, m, v, w}
    , succ{ s }
    {
    }

Link* Link::add(Link* n)            // add n after this object; return n
{
    if (n == nullptr)               // nothing to add
        return this;
    n->succ = succ;                 // this' successor becomes n's successor (including nullptr)
    succ = n;                       // this object's successor becomes n
    return n;
}

Link* Link::insert(Link* h, Link* n)        // insert n before this object in list h
{
    if (n == nullptr)
        return this;
    Link* prev = h;

    // Find the node before 'this' starting from the head
    // i.e. find the node where 'this' is the successor
    while (prev->succ != nullptr && prev->succ != this)
    {
        prev = prev->succ;
    }
    // set n's successor as this
    // set this' successor as n
    if (prev->succ == this)
    {
         n->succ = this;
         prev->succ = n;
    }
    // return the object being inserted before
    return this;
}

Link* Link::erase(Link* h)                 // remove this from h, return successor
{
    if (h == nullptr)
        return nullptr;

    // If erasing head of list
    if (this == h)
    {
        Link* new_head = this->succ;
        delete this;
        return new_head;
    }

    Link* prev = h;
    // Find the node before 'this' starting from the head
    // i.e. find the node where 'this' is the successor
    while (prev->succ != nullptr && prev->succ != this)
    {
        prev = prev->succ;
    }
    // if found, set prev->succ to this->succ
    if (prev->succ == this)
    {
        prev->succ = this->succ;
        delete this;
    }
    return h;
}

Link* Link::find(Link* h, const string& s)      // find s in h, return nullptr if not found
{
    Link* current = h;
    while (current)                         // while current != nullptr
    {
        if (current->God.name == s)            // if found
            return current;                 // return it
        current = current->succ;            // if not, move on to successor (until nullptr)
    }
    return nullptr;
}

/*
Link* Link::advance(int n)          // move n positions in list; return nullptr for "not found"
{                                   // positive n moves forward, negative backward
    Link* p = this;
    if (p == nullptr)
        return nullptr;
    while (0 < n)
    {
        --n;
        if (p->succ)
            p = p->succ;
        else
            return nullptr;
    }
    while (n < 0)
    {
        ++n;
        if (p->prev)
            p = p->prev;
        else
            return nullptr;
    }
    return p;
}
    */