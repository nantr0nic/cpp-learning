//Heap
//Demonstrates dynamically allocating memory

#include <iostream>

using namespace std;

int* intOnHeap();       //returns an int on the heap
void leak1();           //creates a memory leak
void leak2();           //creates another memory leak

int main()
{
    int* pHeap = new int;
    *pHeap = 10;
    cout << "*pHeap: " << *pHeap << "\n\n";

    int* pHeap2 = intOnHeap();
    cout << "*pHeap2: " << *pHeap2 << "\n\n";

    cout << "Freeing memory pointed to by pHeap.\n\n";
    delete pHeap;

    cout << "Freeing memory pointed to by pHeap2.\n\n";
    delete pHeap2;

    //get rid of dangling pointers
    pHeap = 0;
    pHeap2 = 0;

    return 0;
}

int* intOnHeap() {
    int* pTemp = new int(20);
    return pTemp;
}

//drip1 is a local variable that goes out of existence after this function concludes
//so the memory heap cannot be 'deleted' thus the memory is 'lost' or 'leaked'
void leak1() {
    int* drip1 = new int(30);
}

//in this one, access to the memory reserved for the first new int(50) is lost and thus
//a 'leak'
void leak2() {
    int* drip2 = new int(50);
    drip2 = new int(100);
    delete drip2;
}
