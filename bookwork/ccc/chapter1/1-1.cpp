#include <cstdio>

int absolute_value(int x) {
    int result = x;
    if (x < 0) {
        result = x * -1;
    } 
    return result;
}

int main() {
    int my_num = -9;
    printf("The absolute value of %d is %d.", my_num, absolute_value(my_num));
}
