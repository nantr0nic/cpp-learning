#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>


using std::cout, std::cin, std::string, std::ifstream, std::ofstream, std::vector;

int main()
{
    string iname;
    string word;
    string line;
    int lineNumber {};
    vector<string> matching_lines;
    vector<int> matching_line_no;
    int no_of_matches {};

    cout << "Word line finder!\nEnter the name of a file: ";
    cin >> iname;

    ifstream ist {iname};
    if (!ist)
    {
        throw std::runtime_error("Can't open file: " + iname);
    }

    cout << "\nEnter a word you'd like to find: ";
    cin >> word;

    while (getline(ist, line))
    {
        lineNumber++;

        if (line.find(word) != string::npos)
        {
            cout << "Found \"" << word << "\" on line " << lineNumber << "\n";
            matching_lines.push_back(line);
            matching_line_no.push_back(lineNumber);
            no_of_matches++;
        }
    }

    cout << "\nHere are our results!\nWe found " << no_of_matches
        << " on the following lines:\n";

    for (size_t i = 0; i < matching_lines.size(); ++i)
    {
        cout << "Line " << matching_line_no[i] << ": " << matching_lines[i] << "\n";
    }

    return 0;
}