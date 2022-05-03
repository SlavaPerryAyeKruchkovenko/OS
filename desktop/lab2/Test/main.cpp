#include <iostream>
#include <fileapi.h>
#include <libloaderapi.h>


#ifdef __cplusplus

extern "C" {

#endif

double Mul(double num1, double num2);

double Sum(double num1, double num2);

double Sub(double num1, double num2);


#ifdef __cplusplus

}
#endif
using namespace std;
struct complex{
    int x;
    int y;
};
int main() {
    cout << "select 1 if normal num, select 2 if complex num" << endl;
    int num;
    cin >> num;
    if(num == 1){
        cout << Sum(2,2);
    }
    if(num == 2){
        complex (*SumComp)(complex c1,complex c2);
        HMODULE hModule;
        hModule=LoadLibrary(TEXT("libcomplex.dll"));
        SumComp= reinterpret_cast<complex (*)(complex, complex)>(GetProcAddress(hModule, "SumComp"));
        complex c1{1,2};
        complex c2{2,2};
        complex res = SumComp(c1,c2);
        cout << res.x << endl << res.y << endl;
    }
    return 0;
}
