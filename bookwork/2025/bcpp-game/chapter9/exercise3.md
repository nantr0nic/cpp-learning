# Exercise 3
##### "What's wrong with the following code?"
```cpp
#include <iostream>
using namespace std;
int main()
{
    int* pScore = new int;
    *pScore = 500;
    pScore = new int(1000);
    delete pScore;
    pScore = 0;
}
```
---
### Answer:
The initial memory allocated to pScore is not deleted before the second memory reservation is made thus resulting in an inaccessible block of memory (i.e. this code creates a memory leak). The fixed code would look something like this:
```cpp
#include <iostream>
using namespace std;
int main()
{
    int* pScore = new int;
    *pScore = 500;
    delete pScore;
    pScore = new int(1000);
    delete pScore;
    pScore = 0;     // handles the dangling pointer
}
```