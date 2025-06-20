#include <iostream>
#include <vector>
#include <stdexcept>

using std::string, std::cout, std::cin, std::istream, std::ostream;

struct Person
{
private:
    string first_name {};
    string second_name {};
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
    Person(const string& fn, const string& sn, int a) : first_name { fn }, second_name { sn}, age { a } 
    { 
        validate_name(fn);
        validate_name(sn);
        validate_age(a);
    }

    string get_name() const { return first_name + " " + second_name; }
    int get_age() const { return age; }

    void set_name(const string& n, int fs) 
    { 
        validate_name(n);
        if (fs == 1)
        {
            first_name = n;
        }
        if (fs == 2)
        {
            second_name = n;
        }
    }
    void set_age(int a) 
    {
        validate_age(a); 
        age = a; 
    }

};

istream& operator>>(istream& is, Person& p)
{
    while (is.good())
    {
        try
        {
            string first_name;
            string second_name;
            int input_age;

            cout << "First name? >> ";
            if (is >> first_name)
            {
                cout << "Last name? >> ";
                if (is >> second_name)
                {
                cout << "Age? >> ";
                    if (is >> input_age)
                    {
                        p.set_name(first_name, 1);
                        p.set_name(second_name, 2);
                        p.set_age(input_age);
                        break;
                    }
                }
            }
        } 
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    
    return is;
}

ostream& operator<<(ostream& os, const Person& p)
{
    os << "Name: " << p.get_name() << "\n" << "Age: " << p.get_age() << "\n";
    return os;
}

struct People
{
private:
    std::vector<Person> people {};

public:
    void add_person(const Person& p) { people.push_back(p); }
    void list_people()
    {
        for (const Person& p : people)
        {
            cout << p;
        }
    }
};

int main()
{
    // Drills 13-21
    // #14
    // Person ex14;
    // ex14.name = "Goofy";
    // ex14.age = 63;
    // cout << "Name: " << ex14.name << "\n" << "Age: " << ex14.age << "\n";

    // #15
    // Person ex15;
    // cin >> ex15;
    // cout << ex15;

    // Person ex19 {"@ndy", 34};
    // Person ex19 {"Andy", 151};

    People roster;
    cout << "Let's add people to our roster: (Name 'XXX' to stop)\n";

    Person temp;
    while (cin >> temp)
    {
        roster.add_person(temp);
    }

    cout << "\nWe have...\n";
    roster.list_people();

    return 0;
}