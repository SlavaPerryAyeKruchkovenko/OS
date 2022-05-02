#include <iostream>

#ifdef __cplusplus

extern "C" {

#endif

double Mul(double num1, double num2);

double Sum(double num1, double num2);

double Sub(double num1, double num2);

#ifdef __cplusplus

}
#endif
int main() {
    std::cout << Sum(2,2) << std::endl;
    return 0;
}
