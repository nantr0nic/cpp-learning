// Designers Network
// Demonstrates logical operators

#include <iostream>
#include <string>
using namespace std;

int main()
{
    string username;
    string password;
    bool success;

    cout << "\tGame Designer's Network\n";
    do
    {
        cout << "\nUsername >> ";
        cin >> username;

        cout << "Password >> ";
        cin >> password;

        if (username == "Andy" && password == "boobies")
        {
            cout << "\nHey, bruh.";
            success = true;
        }

        else if (username == "nantronic" && password == "1337")
        {
            cout << "\nWassup?";
            success = true;
        }

        else if (username == "guest" || password == "guest")
        {
            cout << "\nHello, guest!";
            success = true;
        }

        else
        {
            cout << "\nYour login failed.";
            success = false;
        } 
    } while (!success);

        return 0;
    }
    