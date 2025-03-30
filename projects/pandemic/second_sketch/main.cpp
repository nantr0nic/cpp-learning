#include <iostream>
#include <random>
#include <vector>
#include <numeric>

using std::cin, std::cout, std::vector;

// Overloading << for vector
std::ostream& operator<<(std::ostream& os, const vector<int>& vec)
{
    os << "[";
    if (!vec.empty())
    {
        os << vec[0];
        for (size_t i = 1; i < vec.size(); ++i)
        {
            os << ", " << vec[i];
        }
    }
    os << "]";
    return os;
}

class Population
{
    public:
        Population();
        void popContacted();
        const vector<int>& getContacted() { return m_contacts; }

        void popInfected(const vector<int>& m_contacts, int inf_chance);
        const vector<int>& getInfected() { return m_infected; }
        void resetInfected() { m_infected.clear(); m_infected.shrink_to_fit(); }
        

    private:
        vector<int> m_contacts;
        vector<int> m_infected;
        std::random_device rd;
        std::mt19937 gen;
};

Population::Population() : gen(rd()) { };

// Function to determine how many contacts are made
// Allow future functionality for location (NA, SA, Eur, Asia, etc.)
void Population::popContacted()
{
    std::uniform_int_distribution<> contacts_dist(5, 25);
    int contacts_size = contacts_dist(gen);
    m_contacts.resize(contacts_size);
    std::iota(m_contacts.begin(), m_contacts.end(), 1);
};

// Function to determine how many of the contacts are infected
// inf_chance is the transmission chance of an infection/symptom
void Population::popInfected(const vector<int>& m_contacts, int inf_chance)
{
    m_infected.reserve(m_contacts.size());  // Reserve the memory upfront
    std::uniform_int_distribution<> inf_dist(1,10);
    
    for (int num : m_contacts)
    {
        int inf_roll = inf_dist(gen);
        if (inf_roll <= inf_chance)
        {
            cout << "Contact #" << num << " got infected!\n";
            m_infected.push_back(num);
        }
        else
        {
            cout << "Contact #" << num << " did NOT get infected!\n";
        }
    }
};

int main()
{
    Population pop;
    pop.popContacted();
    cout << "The number of people contacted: " << pop.getContacted().size() << "\n";
    cout << pop.getContacted() << "\n\n";
    pop.popInfected(pop.getContacted(), 7);
    cout << "The number of people infected: " << pop.getInfected().size() << "\n\n";
    pop.resetInfected();

    pop.popContacted();
    cout << "The number of people contacted: " << pop.getContacted().size() << "\n";
    cout << pop.getContacted() << "\n\n";
    pop.popInfected(pop.getContacted(), 5);
    cout << "The number of people infected: " << pop.getInfected().size() << "\n\n";
    pop.resetInfected();

    pop.popContacted();
    cout << "The number of people contacted: " << pop.getContacted().size() << "\n";
    cout << pop.getContacted() << "\n\n";
    pop.popInfected(pop.getContacted(), 3);
    cout << "The number of people infected: " << pop.getInfected().size() << "\n\n";
    pop.resetInfected();

    return 0;
}