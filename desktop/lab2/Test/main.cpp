#include <iostream>

#ifdef __cplusplus

extern "C" {

#endif

double Mul(double num1, double num2);

double Sum(double num1, double num2);

double Sub(double num1, double num2);

struct complex MulComp(struct complex c1,struct complex c2);
struct complex SubComp(struct complex c1,struct complex c2);
struct complex SumComp(struct complex c1,struct complex c2);
struct complex;

#ifdef __cplusplus

}
#endif
using namespace std;

int main() {
    std::cout << Sum(2,2) << std::endl;
    struct complex c1;
    c1.x = 2;
    c1.y = 10;
    struct complex c2;
    c2.x = 26;
    c2.y = 10;
    SumComp(c1,c2);
    return 0;
}
