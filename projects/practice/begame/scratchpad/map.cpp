// Testing ASCII map stuff

// Note: Rough idea. Need to use vectors cuz they're dynamic.
// Also, fun that the compiler returns errors but it still works lol

#include <iostream>
#include <vector>

using namespace std;

void displayMap(char* pMap, int& map_y, int& map_x);

const char WL = '|'; // wall
const char SP = '.'; // space
const char EN = 'X'; // enemy

int main() {
    int map_y = 6;
    int map_x = 15;
    bool running = true;
    char map[map_y][map_x] = {  {WL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, WL},
                                    {WL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, WL},
                                    {WL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, WL},
                                    {WL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, WL},
                                    {WL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, WL},
                                    {WL, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, SP, WL} };
    char (*pMap)[map_x] = map;
    while (running) {
        char key;
        cin >> key;
        switch (key) {
            case 'q':
                running = false;
                break;
            default:
                displayMap(pMap, map_y, map_x);
        }
    }
    return 0;
}


void displayMap(char (*pMap)[15], int& map_y, int& map_x) {
    for (int i = 0; i < map_y; ++i) {
        for (int j = 0; j < map_x; ++j) {
            cout << pMap[i][j];
        }
        cout << "\n";
    }
}


/*
|..................|
|.............@....|
|..................|
|....@.............|
|..................|
|.........O........|
*/