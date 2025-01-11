#include <cstddef>
#include <cstdio>

int main() {
    unsigned long maximum = 0;
    unsigned long values[] = { 10, 50, 20, 40, 0 };
    for(size_t i=0; i < 5; i++) {
        if (values[i] > maximum) maximum = values[i];
    }
    printf("The maximum value is %lu\n\n", maximum);
    printf("xXxXxXxXxXx\n\n");
    for(unsigned long value : values) {
        if (value > maximum) maximum = value;
    }
    printf("The max.. %lu.\n\n", maximum);
    
    short array[] = { 104, 105, 32, 98, 105, 108, 108, 0 };
    size_t n_elements = sizeof(array) / sizeof(short);
    printf("Elements: %d", n_elements);
}

/*
for(init-statement; conditional; iteration-statement) {
    code
}

for(element-type element-name : array-name) {
    code
}
*/