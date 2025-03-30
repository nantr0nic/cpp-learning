#include <iostream>
#include <random>
#include <vector>

using namespace std;

ostream& operator<<(ostream& os, const vector<int>& vec)
{
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        os << vec[i];
        if (i < vec.size() - 1) os << ", ";
    }
    os << "]";
    return os;
}

int main()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> contacts_dist(5, 20);
    vector<int> contacts(contacts_dist(gen));

    int choice = 0;
    cout << "You're a virus. Choose one transmission method:\n";
    cout << "[1] - Sneezing. (High transmission / Low mortality)\n";
    cout << "[2] - Coughing. (Medium transmission / Medium mortality)\n";
    cout << "[3] - Bodily fluids. (Low transmission / High mortality)\n";
    cin >> choice;

    switch (choice)
    {
        case 1:
        {
            cout << "You chose Sneezing!\n";
            cout << "You've come into contact with " << contacts.size() << " other people.\n";
            int infected_total = 0;
            for (long unsigned int i = 0; i < contacts.size(); ++i)
            {
                uniform_int_distribution<> infection_dist(1,10);
                int infection_chance = infection_dist(gen);
                if (infection_chance <= 5)
                {
                    ++infected_total;
                    cout << "Contact #" << (i + 1) << " got infected!\n";
                }
                else
                {
                    cout << "Contact #" << (i + 1) << " did NOT get infected.\n";
                }
            }
            cout << "Out of " << contacts.size() << " you infected a total of " << infected_total << " people!\n";
            break;
        }

        case 2:
        {
            cout << "You chose Coughing!\n";
            cout << "You've come into contact with " << contacts.size() << " other people.\n";
            int infected_total = 0;
            for (long unsigned int i = 0; i < contacts.size(); ++i)
            {
                uniform_int_distribution<> infection_dist(1,10);
                int infection_chance = infection_dist(gen);
                if (infection_chance <= 3)
                {
                    ++infected_total;
                    cout << "Contact #" << (i + 1) << " got infected!\n";
                }
                else
                {
                    cout << "Contact #" << (i + 1) << " did NOT get infected.\n";
                }
            }
            cout << "Out of " << contacts.size() << " you infected a total of " << infected_total << " people!\n";
            break;
        }

        case 3:
        {
            cout << "You chose Bodily Fluids!\n";
            cout << "You've come into contact with " << contacts.size() << " other people.\n";
            int infected_total = 0;
            for (long unsigned int i = 0; i < contacts.size(); ++i)
            {
                uniform_int_distribution<> infection_dist(1,10);
                int infection_chance = infection_dist(gen);
                if (infection_chance <= 1)
                {
                    ++infected_total;
                    cout << "Contact #" << (i + 1) << " got infected!\n";
                }
                else
                {
                    cout << "Contact #" << (i + 1) << " did NOT get infected.\n";
                }
            }
            cout << "Out of " << contacts.size() << " you infected a total of " << infected_total << " people!\n";
            break;
        }
        default:
            cout << "That's not a valid option.\n";
            break;
    }
    return 0;
}