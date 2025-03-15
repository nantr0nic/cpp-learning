//Critter Caretaker
//Simulates caring for a virtual pet

#include <iostream>

using namespace std;

class Critter
{
    public:
        Critter(int hunger = 0, int boredom = 0);
        void Talk();
        void Eat(int food = 4);
        void Play(int boredom = 4);
        void Check();

    private:
        int m_Hunger;
        int m_Boredom;

        int GetMood() const { return (m_Hunger + m_Boredom); }
        int GetHunger() const { return (m_Hunger); }
        int GetBoredom() const { return (m_Boredom); }
        void PassTime(int time = 1);
};

Critter::Critter(int hunger, int boredom):
    m_Hunger(hunger),
    m_Boredom(boredom)
    { }

void Critter::PassTime(int time) {
    m_Hunger += time;
    m_Boredom += time;
}

void Critter::Talk() {
    cout << "I'm a critter and I feel ";

    int mood = GetMood();
    if (mood > 15) {
        cout << "mad.\n";
        if (m_Boredom > m_Hunger) {
            cout << "I wanna play...\n";
        }
        else if (m_Boredom < m_Hunger) {
            cout << "My stomach is growling...\n";
        }
        else {
            cout << "I want to play but I'm too hungry...\n";
        }
    }
    else if (mood > 10) {
        cout << "frustrated.\n";
    }
    else if (mood > 5) {
        cout << "okay.\n";
    }
    else {
        cout << "happy!\n";
    }
    PassTime();
}

void Critter::Eat(int food) {
    cout << "Brruppp.\n";

    m_Hunger -= food;
    if (m_Hunger < 0) {
        m_Hunger = 0;
    }

    PassTime();
}

void Critter::Play(int fun) {
    cout << "Wheee!\n";

    m_Boredom -= fun;
    if (m_Boredom < 0) {
        m_Boredom = 0;
    }

    PassTime();
}

void Critter::Check() {
    PassTime();

    cout << "Hunger: " << GetHunger() << " / Boredom: " << GetBoredom() << "\n";
}

int main()
{
    Critter crit;
    crit.Talk();

    int choice;
    do {
        cout << "\nCritter Caretaker\n\n";
        cout << "0 - Quit\n";
        cout << "1 - Listen to your critter\n";
        cout << "2 - Feed your critter\n";
        cout << "3 - Play with your critter\n";
        cout << "9 - Check critter levels.\n\n";

        cout << "Choice >> ";
        cin >> choice;

        switch (choice) {
            case 0:
                cout << "Goodbye!\n";
                break;
            case 1:
                crit.Talk();
                break;
            case 2:
                crit.Eat();
                break;
            case 3:
                crit.Play();
                break;
            case 9:
                crit.Check();
                break;
            default:
                cout << "\nSorry, but " << choice << " isn't a valid choice.\n";
        }
    } while (choice != 0);

    return 0;
}