#include <iostream>

using namespace std;

int get_int();                  // read an int from cin
int get_int(int low, int high); // read an int in [low:high] from cin
int get_int(int low, int high, const string& greeting, const string& sorry);

void skip_to_int()
{
    if (cin.fail())
    {
        cin.clear();
        for (char ch; cin>>ch; )
        {
            if (isdigit(ch) || ch=='-')
            {
                cin.unget();
                return;
            }
        }
    }
    throw std::runtime_error("no input");
}

int get_int()
{
    int n = 0;
    while (true)
    {
        if (cin >> n)
        {
            return n;
        }
        cout << "Sorry, that was not a number; please try again!\n";
        skip_to_int();
    }
}

int get_int(int low, int high)
{
    cout << "Please enter an integer in the range "
        << low << " to " << high << " (inclusive):\n";
    while (true)
    {
        int n = get_int();
        if (low <= n && n <= high)
        {
            return n;
        }
        cout << "Sorry " << n << " is not in the ["
            << low << ":" << high << "] range; please try again!\n";
    }
}

int get_int(int low, int high, const string& greeting, const string& sorry)
{
    cout << greeting << ": ["<< low << ":" << high << "]\n";

    while (true)
    {
        int n = get_int();
        if (low <= n && n <= high)
        {
            return n;
        }
        cout << sorry << ": ["<< low << ":" << high << "]\n";
    }
}

int main()
{
    int n = get_int(1,10);
    cout << "n: " << n << "\n";

    int m = get_int(2,300);
    cout << "m: " << m << "\n";

    int strength = get_int(1, 10, "Enter strength", "Not in range, try again");
    cout << "Strength: " << strength << "\n";

    int altitude = get_int(0, 50000, "Please enter altitude in feet", "Not in range, please try again");
    cout << "Altitude: " << altitude << "f above sea level\n";

    return 0;
}