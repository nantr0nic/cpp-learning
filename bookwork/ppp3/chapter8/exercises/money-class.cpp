#include <iostream>

class Money
{
    public:
        double roundValue(const double val);  // rounds to hundredths
        double addMoney(const double& val1, const double& val2);
        double subMoney(const double& val1, const double& val2);
        long int Cents(const double& val) { return val * 100; }  // represents an amount as cents
};

// Rounds a currency amount to the nearest hundredths
double Money::roundValue(const double val)
{
    return static_cast<int>(val * 100 + 0.5) / 100.00;
}

// Adds two amounts of money then returns rounded sum
double Money::addMoney(const double& val1, const double& val2)
{
    double new_value = val1 + val2;
    return roundValue(new_value);
}

double Money::subMoney(const double& val1, const double& val2)
{
    double new_value = val1 - val2;
    return roundValue(new_value);
}

int main()
{
    Money money;
    std::cout << "Rounding: $" << money.roundValue(123.4567) << "\n";
    std::cout << "Adding $10.13 and $87.31: $" << money.addMoney(10.13, 87.31) << "\n";
    std::cout << "Subtracting $10.13 from $87.31: $" << money.subMoney(87.31, 10.13) << "\n";
    std::cout << "Subtracting $87.31 from $10.13: $" << money.subMoney(10.13, 87.31) << "\n";
    std::cout << "$515.23 in cents is: " << money.Cents(515.23) << "\n";
    std::cout << "$123.456 in cents is: " << money.Cents(123.456) << "\n";

    return 0;
}