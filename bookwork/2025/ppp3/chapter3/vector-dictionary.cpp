#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cout, std::cin, std::vector, std::string, std::sort;

int main()
{
    vector<string> words;
    vector<string> disliked = {"love", "hate", "mirror"};

    for(string temp; cin>>temp;)
        words.push_back(temp);
    cout << "\nNumber of words: " << words.size() << "\n";

    sort(words.begin(), words.end());
    for (unsigned long int i = 0; i < words.size(); ++i)
    {
        if (i == 0 || words[i-1] != words[i])       // this works because the words are already sorted
        {                                           // so repeated words are grouped in the vector
            for (unsigned long int j = 0; j < disliked.size(); ++j)
            {
                if (words[i] == disliked[j])
                    words[i] = "BLEEP";
            }
            cout << words[i] << "\n";
        }
    }
    return 0;
}