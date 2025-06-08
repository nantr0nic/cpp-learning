// "third sketch"

#include <iostream>
#include <random>

class Pandemic
{
public:
    Pandemic() : rTool{} { }

    struct randTools
    {
    public:
        randTools()
        {
            std::random_device rd;
            gen = std::mt19937(rd());
        }

        std::mt19937& getGenerator() { return gen; }

        int r20();
        int rAny(const int& low, const int& high);

    private:
        std::mt19937 gen;
    };
    
    // Getters
    int infected() const { return m_infected; }
    int contacts() const { return m_contacts; }

    // Infection functions
    void makeContacts();
    void makeInfected(const int& chance);

    bool infectChance(const int& chance);

private:
    randTools rTool;

    int m_infected {};
    int m_contacts {};
    // int m_chance {};
};

int main()
{
    Pandemic game;

    game.makeContacts();
    game.makeInfected(15);

    std::cout << "A total of " << game.infected() << " people were infected.\n";
    
    return 0;
}

int Pandemic::randTools::r20()
{
    std::uniform_int_distribution<> dist(1, 20);
    return dist(gen);
}

int Pandemic::randTools::rAny(const int& low, const int& high)
{
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

bool Pandemic::infectChance(const int& chance)
{
    // Chance is an int representing chance of infection (e.g. 3%, 50%)
    int infected_roll = rTool.rAny(0, 100);
    // std::cout << "Person rolled a " << infected_roll << "\n";
    if (infected_roll <= chance)
    {
        // is infected
        return true;
    }
    else if (infected_roll > chance)
    {
        // is not infected
        return false;
    }
}

void Pandemic::makeContacts()
{
    m_contacts = rTool.r20();
    std::cout << "Contacts: " << contacts() << "\n";
}

void Pandemic::makeInfected(const int& chance)
{
    for (int i {}; i < m_contacts; ++i)
    {
        bool infected = infectChance(chance);
        if (infected)
        {
            std::cout << "Someone was infected!\n";
            ++m_infected;
        }
        else
        {
            std::cout << "Someone was contacted but NOT infected.\n";
        }
    }
}
