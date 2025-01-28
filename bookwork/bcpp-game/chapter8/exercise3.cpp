/*
3. What design problem does the following program have?
*/

#include <iostream>
using namespace std;

class Critter
{
    public:
        int GetHunger() const {return m_Hunger;}
    private:
        int m_Hunger;
};

int main()
{
    Critter crit;
    cout << crit.GetHunger() << endl;
return 0;
}

/*
The problem with this program is that m_Hunger is not initialized nor at any point given
a value. One could either initialize it with a value or make a constructor for the class
where a default value is declared.
*/