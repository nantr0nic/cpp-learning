/*===========================================================================*
*                                                                            *
*                           "Try This" on page 812                           *
*                                                                            *
*We left two potentially serious errors in this little program. One can cause*
*  a crash, and the other will give wrong answers if high() is used in many  *
*   other programs where it might have been useful. The general techniques   *
*       that we describe below will make them obvious and show how to        *
*  systematically avoid them. For now, just find them and suggest remedies.  *
 *===========================================================================*/

import std;

double* high(double* first, double* last)
// return a pointer to the element in the [first:last) that has the highest value
{
    double h = -1;  //! <--- this is bad and limits the application of this function[!]
    double* high = nullptr;     //! don't use uninitialized raw pointers (crash?)

    for (double* p = first; p < last; ++p) //! don't use != (though might be okay here)
    {                                       //! it might skip 'last' and infinitely loop
        if (h < *p)
        {
            high = p;           
            h = *p;
        }
    }
    //! delete p?
    return high;
}
//! A more general problem with this code is it is only useful for doubles whereas 
//! a templatized version would be useful for any type that supports '<'


/*================================================================================*
*                             "Try This" on page 820                              *
*                                                                                 *
*Write a function void copy(int* f1, int* e1, int* f2) that copies the elements of*
* an array of ints defined by [f1:e1) into another [f2:f2+(e1−f1)). Use only the  *
*             iterator operations mentioned above (not subscripting).             *
 *================================================================================*/

void copy(int* f1, int* e1, int* f2)
{
    for (int* p = f1; p < e1; ++p)
    {
        *f2 = *p;
        ++f2;
    }
}

int main()
{
    int* int_array = new int[5]{ 1, 2, 3, 4, 5 };
    int* empty_array = new int[5]{ 0, 0, 0, 0, 0 };
    
    copy(int_array, (int_array + 5), empty_array);

    for (int i = 0; i < 5; ++i)
    {
        std::cout << int_array[i] << ' ';
        std::cout << empty_array[i] << ' ';
    }

    delete[] int_array;
    delete[] empty_array;

    return 0;
}