/* Write a program with a pointer to a pointer to a string object. Use the
pointer to the pointer to call the size() member function of the string
object.*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    string name = "Andy";
    cout << "[[string name = \"Andy\"]]\n";
    cout << "name: " << name << "\n";
    cout << "&name: " << &name << "\n";
    cout << "name.size(): " << name.size() << "\n";
    cout << "-=-=-=-=-=-=-=-=-=-=-\n";
    string* pName = &name;
    cout << "[[string* pName = &name;]]\n";
    cout << "pName: " << pName << "\n";
    cout << "&pName: " << &pName << "\n";
    cout << "*pName: " << *pName << "\n";
    cout << "pName->size(): " << pName->size() << "\n";
    cout << "(*pName).size(): " << (*pName).size() << "\n";
    cout << "-=-=-=-=-=-=-=-=-=-=-\n";
    string** pName2 = &pName;
    cout << "[[string** pName2 = &pName;]]\n";
    cout << "pName2: " << pName2 << "\n";
    cout << "&pName2: " << &pName2 << "\n";
    cout << "*pName2: " << *pName2 << "\n";
    cout << "**pName2: " << **pName2 << "\n";
    cout << "(*pName2)->size(): " << (*pName2)->size() << "\n";
    cout << "(**pName2).size(): " << (**pName2).size() << "\n";
    cout << "-=-=-=-=-=-=-=-=-=-=-\n";
    cout << "pName is a pointer and pName2 is a pointer to a pointer.\n";
    cout << "-=-=-=-=-=-=-=-=-=-=-\n";
    cout << "pName points to name.\n";
    cout << "pName returns the memory address of name.\n";
    cout << "&pName is the memory address of pName itself.\n";
    cout << "*pName is dereferenced and returns the string object of name.\n";
    cout << "-=-=-=-=-=-=-=-=-=-=-\n";
    cout << "pName2 points to pName (another pointer).\n";
    cout << "pName2 returns the memory address of pName\n";
    cout << "&pName2 is the memory address of pName2 itself.\n";
    cout << "*pName2 is dereferenced and returns pName itself which is the memory address of name.\n";
    cout << "**pName2 is dereferenced twice, so it points to what pName points to (Andy)." << "\n\n";
    cout << "Thus...\n";
    cout << name << " == " << *pName << " == " << **pName2 << "\n";
    cout << "name == *pName == **pName\n\n";
    cout << &name << " == " << pName << " == " << *pName2 << "\n";
    cout << "&name == pName == *pName\n\n";
    cout << &pName << " == " << pName2 << "\n";
    cout << "&pName == pName2\n";
    return 0;
}