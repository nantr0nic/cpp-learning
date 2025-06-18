#include <iostream>

using std::string, std::cout, std::cin, std::istream, std::ostream;

// Drills 13-21
struct Person
{
private:
    string name {};
    int age {};

    void validate_name(const string& n)
    {
        for (const char& c : n)
        {
            if (ispunct(c))
                throw std::runtime_error("Can't have punctuation in name!\n");
        }
    }

    void validate_age(const int a)
    {
        if (a <= 0 || a > 150)
            throw std::runtime_error("Invalid age!\n");
    }

public:
    Person() { }
    Person(const string& n, int a) : name { n }, age { a } 
    { 
        validate_name(n);
        validate_age(a);
    }

    string get_name() const { return name; }
    int get_age() const { return age; }

    void set_name(const string& n) 
    { 
        validate_name(n);
        name = n; 
    }
    void set_age(int a) 
    {
        validate_age(a); 
        age = a; 
    }


};

istream& operator>>(istream& is, Person& p)
{
    string input_name;
    int input_age;

    cout << "Name? >> ";
    is >> input_name;
    p.set_name(input_name);
    cout << "Age? >> ";
    is >> input_age;
    p.set_age(input_age);
    return is;
}

ostream& operator<<(ostream& os, const Person& p)
{
    os << "Name: " << p.get_name() << "\n" << "Age: " << p.get_age() << "\n";
    return os;
}

int main()
{
    // Drills 13-21
    // #14
    // Person ex14;
    // ex14.name = "Goofy";
    // ex14.age = 63;
    // cout << "Name: " << ex14.name << "\n" << "Age: " << ex14.age << "\n";

    // #15
    Person ex15;
    cin >> ex15;
    cout << ex15;

    // Person ex19 {"@ndy", 34};
    // Person ex19 {"Andy", 151};

    return 0;
}