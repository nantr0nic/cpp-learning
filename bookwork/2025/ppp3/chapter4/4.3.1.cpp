// Testing wrong syntax to see compiler messages

#include <iostream>

int area(int length, int width) { return length*width; }

/*
int s1 = area(7,2;
int s2 = area(7,2);
Int s3 = area(7,2);
int s4 = area('7,2);
*/

int x5 = area(10.7,9.3);

int main()
{
    std::cout << x5;
}