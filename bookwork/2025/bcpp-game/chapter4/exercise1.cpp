/*
Write a program using vectors and iterators that allows a user to maintain
a list of his or her favorite games. The program should allow the user to
list all game titles, add a game title, and remove a game title.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    vector<string> games;

    vector<string>::const_iterator iter;

    int running = 1;
    char menu_option;
    string title;

    while (running) {
        cout << "\nFavorite Game List!\n";
        cout << "Would you like to (l)ist all titles, (a)dd a title, (r)emove a title, or (q)uit?\n >> ";
        cin >> menu_option;
        switch (menu_option) {
            case 'l':
                if (games.empty()) {
                    cout << "List is empty!\n";
                }
                for (unsigned int i = 0; i < games.size(); ++i) {
                    cout << i + 1 << ") " << games[i] << endl;
                }
                break;
            case 'a':
                cout << "What game would you like to add?\n >> ";
                cin >> title;
                iter = find(games.begin(), games.end(), title);
                if (iter != games.end()) {
                    cout << "Title already in list!\n";
                }
                else {
                    games.push_back(title);
                }
                break;
            case 'r':
                if (games.empty()) {
                    cout << "The list is empty! Nothing to remove.\n";
                    break;
                }
                cout << "Which title would you like to remove?\n >> ";
                cin >> title;
                iter = find(games.begin(), games.end(), title);
                if (iter == games.end()) {
                    cout << "Title is NOT on the list!\n";
                }
                else {
                    games.erase(iter);
                }
                break;
            case 'q':
                cout << "Thank you! Bye!\n";
                running = 0;
                break;
            default:
                cout << "Not a valid option.\n";
                break;
        }
    }

    return 0;
}
    

