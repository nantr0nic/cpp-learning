# Discussion Questions
1. What are the advantages and disadvantages of passing a pointer?
2. What kinds of situations call for a constant pointer?
3. What kinds of situations call for a pointer to a constant?
4. What kinds of situations call for aconstant pointer to a constant?
5. What kinds of situations call for anon-constant pointer to a non-constant object?
   
---

### My Answers

1. Assuming this means 'passing a pointer' as an argument to a function... one advantage is that instead of making a copy of a value (thus doubling the amount of memory used) your code can use a pointer that *points to* the memory address of the already-existing value. This improves performance. A second advantage is that passing a pointer can allow you to access and change variables that are outside the scope of the function (depending on the kind of pointer you are using!). A major disavantage of passing pointers is they are less readable and can become more complicated than is required to fulfill a purpose. A constant reference is simpler/easier to read than a constant pointer to a constant.
2. You would use a constant pointer when you do not plan to change the memory address the pointer is storing and when you are pointing to a non-constant value. A suitable situation would be a pointer to a player's health points. This would be a non-constant value and you would not want the pointer to point to anything else.
   ```cpp
   int* const pHealth = &health;
   ```
3. You would use a pointer to a constant when you might want to change the memory address the pointer points to but you do NOT want the pointer to be able to change the value to which it points. It can point to a constant OR a non-constant value. A situation you might use a pointer to a constant is a pointer that stores the player with the highest score in a multiplayer game. You can make a function that changes the name that the pointer to a constant points to but you do NOT want the pointer to be able to change the player's name.
   ```cpp
   const string* pTopPlayer = &player[i];
   // i = the index of the player with the highest score
   ```
4. You would use a constant pointer to a constant when you do not want the pointer to change neither the memory address to which it points nor the value to which it points. I think this is the same as a constant reference -- which would be the preferable method in most cases excluding the return of a function. A situation where you could use a constant pointer to a constant is in a displaying the minimum elements in a heads up display. Say you have a HUD with a quick-inventory window where you want 6 spaces to be displayed even if they are empty, you could pass a constant pointer to a constant to a function that displays the slots. You want the function to display the slots without altering the number or contents of the slots.
   ```cpp
   #include <iostream>
   #include <string>
   #include <vector>
   //prototype declartion
   void displaySlots(const vector<string>* const pSlots, size_t size);
   // in main()...
   int main() {
        vector<string> slots = {"sword", "shield", "potion", "empty", "empty", "empty"};
        displaySlots(&slots, slots.size());
        return 0;
   }
   void displaySlots(const vector<string>* const pSlots, size_t size) {
        for (size_t i = 0; i < size; ++i) {
            cout << (*pSlots)[i] << " ";
        }
        cout << endl;
   }
   ```
5. An example of a non-constant pointer to a non-constant object would be a regular pointer pointing to a string object. Say you have a party system where you could have betwen 0 and 3 party members and you want a pointer to point to the 2nd party member's name. This pointer would be re-assigned depending on who is 2nd, and that player could also change their name -- thus the object would be non-constant.
   ```cpp
   vector<string> party_members = {"Player", "Eder", "Aloth"};
   string* pParty2 = &party_members[1];
   ```
