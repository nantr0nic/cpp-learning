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
        vector<double> age;
};

Name_pairs::Name_pairs(vector<string> names)
    : name{names}
    { }

void Name_pairs::read_names()
{
    size_t index {};
    cout << "Here are some names we're going to work with:\n";
    for (const auto& individual : name)
    {
        cout << index << ". " << individual << "\n";
        ++index;
    }
}

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

void Name_pairs::print() const 
{
    cout << "Here are the names and ages you've entered.\n";
    for (size_t i = 0; i < name.size(); ++i)
    {
        cout << i << ". " << name[i] << " is " << age[i] << " years old.\n";
    }
};

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
        for (size_t j = 0; i < name_presort.size(); ++j)
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

std::ostream& operator<<(std::ostream& os, const Name_pairs& list)
{
    vector<string> names = list.get_name();
    vector<double> ages = list.get_age();
    cout << "Here are the names and ages you've entered.\n";
    for (size_t i = 0; i < names.size(); ++i)
    {
        cout << i << ". " << names[i] << " is " << ages[i] << " years old.\n";
    }
    return os;
}

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
    vector<string> list1_names = list1.get_name();
    vector<string> list2_names = list2.get_name();
    vector<double> list1_ages = list1.get_age();
    vector<double> list2_ages = list2.get_age();
    if (list1_names.size() != list2_names.size() || list1_ages != list2_ages)
    {
        return true;
    }
    for (size_t i = 0; i < list1_names.size(); ++i)
    {
        if (list1_names[i] != list2_names[i] || list1_ages[i] != list2_ages[i])
        {
            return true;
        }
    }
    return false;
}

int main()
{
    Name_pairs list1;
    Name_pairs list2 {vector<string> {"Jeff", "Jered", "Chapin"}};
    Name_pairs list3 {vector<string> {"Jeff", "Jered", "Chapin"}};

    cout << "Welcome to the Name_pairs program.\n";
    try {
        list1.read_names();
        list1.read_ages();
        list1.print();
        list1.sort();
        cout << "Let's re-print after sorting!\n";
        list1.print();
        cout << "\n\nLet's try our new global << operator!\n\n";
        cout << list1;
        list2.read_names();
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