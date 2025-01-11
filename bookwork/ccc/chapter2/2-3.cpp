#include <cstdio>

float a = 0.1F;
double b = 0.2;
long double c = 0.3L;
double plancks_constant = 6.62607004e-34;
double an = 6.0221409e23;
float hp = 9.75;

int main() {
    printf("VVVV Planck's Constant VVVV\n");
    printf("f: %f\n", plancks_constant); // duh....
    printf("lf: %lf\n", plancks_constant); // number is smaller than given precision...
    printf(".34lf: %.34lf\n", plancks_constant); // here we'll see a 7 eventually lol
    printf("e: %e\n", plancks_constant);
    printf("g: %g\n", plancks_constant);
    printf("Avogadro's Number: %le, %f, %lg\n", an, an, an);
    printf("Hogwarts' Platform: %e, %f, %g\n", hp, hp, hp);
}