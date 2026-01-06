#include <cstdio>

enum class Operation {
    Add,
    Subtract,
    Multiply,
    Divide
};

struct Calculator {
    Operation op;

    Calculator(Operation operation) : op(operation) {}

    int calculate(int a, int b) {
        switch(op) {
            case Operation::Add: {
                int result = a + b;
                return result;
            } break;
            case Operation::Subtract: {
                int result = a - b;
                return result;
            } break;
            case Operation::Multiply: {
                int result = a * b;
                return result;
            } break;
            case Operation::Divide: {
                if(b != 0) {
                    int result = a / b;
                    return result;
                } else {
                    printf("Can't divide by 0.\n");
                    return 0;
                }
            } break;
            default: {
                printf("Unsupported operation.\n");
                return 0;
            }
        }
    }
};

int main() {
    Calculator addCalc(Operation::Add);
    Calculator subCalc(Operation::Subtract);
    Calculator mulCalc(Operation::Multiply);
    Calculator divCalc(Operation::Divide);

    printf("Addition of 6 and 3: %d\n", addCalc.calculate(6, 3));
    printf("Subtraction: %d\n", subCalc.calculate(6, 3));
    printf("Multiplication: %d\n", mulCalc.calculate(6, 3));
    printf("Division: %d\n", divCalc.calculate(6,3));
    printf("Divide by 0: %d\n", divCalc.calculate(6,0));
}
