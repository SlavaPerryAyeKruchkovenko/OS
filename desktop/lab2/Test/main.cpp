#include <iostream>

#ifdef __cplusplus

extern "C" {

#endif

double Mul(double num1, double num2);

double Sum(double num1, double num2);

double Sub(double num1, double num2);

void Mul1(double x1,double y1,double x2,double y2);
void Sub1(double x1,double y1,double x2,double y2);
void Sum1(double x1,double y1,double x2,double y2);

#ifdef __cplusplus

}
#endif
using namespace std;

int main() {
    std::cout << Sum(2,2) << std::endl;
    Sum1(2,2,6,5);
    return 0;
}
