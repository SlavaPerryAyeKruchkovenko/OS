#include <stdio.h>
#include <fileapi.h>
#include <windows.h>


const int n = 10000;
double function(double x){
    return 3/x;
}
DWORD WINAPI FuncThread1(LPVOID param){
    int count = 0;
    for (int i = 1; i < n; i+=2) {
        *((double*)param) += function(i);
    }
    return 0;
}
DWORD WINAPI FuncThread2(LPVOID param){
    int count = 0;
    for (int i = 2; i < n; i+=2) {
        *((double*)param) += function(i);
    }
    return 0;
}
int main() {
    double res = 0;
    HANDLE hTreads[2];
    hTreads[0] = CreateThread(NULL,
                              0,
                              FuncThread1,
                              &res,
                              0,
                              NULL);
    hTreads[1] = CreateThread(NULL,
                              0,
                              FuncThread2,
                              &res,
                              0,
                              NULL);
    WaitForMultipleObjects(2,hTreads,TRUE,INFINITE);
    printf_s("%f",res);
    return 0;
}
