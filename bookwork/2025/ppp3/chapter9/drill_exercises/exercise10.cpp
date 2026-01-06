/*
[10] Make a simple table including last name, first name, telephone number,
and email address for yourself and at least five of your friends. Use
strings to hold all values, even for the phone numbers. Experiment with
different field widths until you are satisfied that the table is well
presented.
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <format>
#include <vector>

using std::cout, std::string, std::format, std::vector, std::setw;

// I know I should make the data private and use getters but I'm just
// keeping it n00b to fulfill the exercise quickly
class Contacts
{
    public:
        Contacts(string f, string l, string p, string e);
        string fname {};
        string lname {};
        string phone {};
        string email {};
};

Contacts::Contacts(string f, string l, string p, string e)
    : fname{f}, lname{l}, phone{p}, email{e}
    { };

int main()
{
    Contacts andy {"Andy", "Khazanovsky", "831-201-7075", "andykhazanovsky@gmail.com"};
    Contacts jess {"Jess", "Smith", "215-555-9012", "jess.smith@email.com"};
    Contacts mike {"Mike", "Johnson", "614-555-5432", "mike.johnson@example.net"};
    Contacts sarah {"Sarah", "Williams", "415-555-0192", "sarah.williams@domain.org"};
    Contacts jason {"Jason", "Lee", "312-555-9876", "jason.lee@company.com"};
    vector<Contacts> contact_list {andy, jess, mike, sarah, jason};
    
    // using setw()
    cout << "------- setw() -------\n";
    cout << "First Name\tLast Name\tPhone\t\tEmail\n";
    for (const auto& entry : contact_list)
    {
        cout << setw(10) << entry.fname << setw(16) << entry.lname
            << setw(14) << entry.phone << setw(27) << entry.email << "\n";
    }

    // using format()
    cout << "\n------ format() --------\n";
    cout << format("{:13} {:13} {:13} {:27}\n", "First Name", "Last Name", "Phone", "Email");
    for (const auto& entry : contact_list)
    {
        cout << format("{:13} {:13} {:13} {:27}\n", entry.fname, entry.lname, entry.phone, entry.email);
    }

    return 0;
}