/*
[2] Design and implement a Name_pairs class holding (name,age) pairs
where name is a string and age is a double. Represent that as a
vector<string> (called name) and a vector<double> (called age) member.
>> Provide an input operation read_names() that reads a series of names.
>> Provide a read_ages() operation that prompts the user for an age for each
name. 
>> Provide a print() operation that prints out the (name[i],age[i]) pairs
(one per line) in the order determined by the name vector. 
>> Provide a sort() operation that sorts the name vector in alphabetical order and
reorganizes the age vector to match. 
! Implement all “operations” as member functions. 
Test the class (of course: test early and often).

---

[3] Replace Name_pair::print() with a (global) operator << and define == and !=
for Name_pairs.
*/

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <exception>

using std::vector, std::string, std::cin, std::cout, std::cerr;

// The Name_pairs class
class Name_pairs
{
    public:
        Name_pairs() { };   // use default names
        Name_pairs(vector<string> names);   // set names
        void read_names();
        void read_ages();
        void print() const;
        void sort();
        vector<string> get_name() const { return name; }
        vector<double> get_age() const { return age; }

    private:
        vector<string> name {"Andy", "AP", "Heather", "Jill", "Luz"};
        vector<double> age {};
};

// Declarations
std::ostream& operator<<(std::ostream& os, const Name_pairs& list);
bool operator==(const Name_pairs& list1, const Name_pairs& list2);
bool operator!=(const Name_pairs& list1, const Name_pairs& list2);

// Class definitions
Name_pairs::Name_pairs(vector<string> names)
    : name{names}
    { }


// Prompt user for names
void Name_pairs::read_names()
{
    cout << "Enter names (terminate with 'end'):\n";
    string input;
    name.clear();  // Clear existing names
    
    while (cin >> input && input != "end")
    {
        name.push_back(input);
    }
}

// Prompt user for ages
void Name_pairs::read_ages()
{
    int ages_input {};
    cout << "Alright, let's enter the ages of the names in the list.\n";
    for (const auto& individual : name)
    {
        cout << "How old is " << individual << "?\n";
        cout << " >> ";
        cin >> ages_input;
        age.push_back(ages_input);
    }
    cout << "Ages have been registered!\n";
}

// print() is replaced by overloaded <<
void Name_pairs::print() const 
{
    cout << *this;
};

// Sorts list alphabetically and sorts ages accordingly
void Name_pairs::sort()
{
    vector<string> name_presort = name;
    vector<double> age_presorted = age;
    vector<double> age_sorted;
    cout << "Now going to sort the list of names alphabetically.\n";
    std::sort(name.begin(), name.end());
    // For each name in the sorted list
    for (size_t i = 0; i < name.size(); ++i)
    {
        // Find its position in the original list
        for (size_t j = 0; j < name_presort.size(); ++j)
        {
            if (name_presort[j] == name[i])
            {
                // Add the corresponding age to new list
                age_sorted.push_back(age_presorted[j]);
                break;      // Stop cuz we don't need to go through rest
                            // of the list if age is found.
            }
        }
    }
    // Copy sorted ages to age member
    age = age_sorted;
}

// Overloaded function definitions
std::ostream& operator<<(std::ostream& os, const Name_pairs& list)
{
    vector<string> names = list.get_name();
    vector<double> ages = list.get_age();
    if (names.empty())
    {
        cout << "That list is empty!\n";
    }
    else if (names.size() != 0 && ages.empty())
    {
        int index {};
        cout << "Here are the names (without ages) in the list:\n";
        for (const auto& individual : names)
        {
            cout << index << ". " << individual << "\n";
            ++index;
        }
    }
    else
    {
        cout << "Here are the names and ages you've entered.\n";
        for (size_t i = 0; i < names.size(); ++i)
        {
            cout << i << ". " << names[i] << " is " << ages[i] << " years old.\n";
        }
    }
    return os;
}

// Compare if two lists are equal (both names and ages)
bool operator==(const Name_pairs& list1, const Name_pairs& list2)
{
    vector<string> list1_names = list1.get_name();
    vector<string> list2_names = list2.get_name();
    vector<double> list1_ages = list1.get_age();
    vector<double> list2_ages = list2.get_age();
    if (list1_names.size() != list2_names.size() || list1_ages != list2_ages)
    {
        return false;
    }
    for (size_t i = 0; i < list1_names.size(); ++i)
    {
        if (list1_names[i] != list2_names[i] || list1_ages[i] != list2_ages[i])
        {
            return false;
        }
    }
    return true;
}

bool operator!=(const Name_pairs& list1, const Name_pairs& list2)
{
    /*
    if (list1 == list2)
    {
        return false;
    }
    return true;
    */
    // More simple but a little more opaque to me:
    return !(list1 == list2);
}

int main()
{
    Name_pairs list1;
    Name_pairs list2 {vector<string> {"Jeff", "Jered", "Chapin"}};
    Name_pairs list3;

    cout << "Welcome to the Name_pairs program.\n";
    try {
        list1.read_ages();
        list1.print();
        list1.sort();
        cout << "Let's re-print after sorting!\n";
        list1.print();
        cout << "\n\nLet's try our new global << operator!\n\n";
        cout << list1;
        cout << list2;
        list2.read_ages();
        cout << list2;
        list3.read_names();
        list3.read_ages();
        cout << list3;
        cout << "Let's test our == and != operators.\n";
        cout << "Are List 1 and List 2 are equal? -> " << (list1 == list2) << "\n";
        cout << "Are List 2 and List 3 equal? -> " << (list2 == list3) << "\n";
        cout << "Are List 1 and List 3 UNequal? -> " << (list1 != list3) << "\n";
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Runtime error: " << e.what() << "\n";
        return 1;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unexpected error: " << e.what() << "\n";
        return 2;
    }
    catch (...)
    {
        std::cerr << "Unknown exception.\n";
        return 2;
    }

    return 0;
}