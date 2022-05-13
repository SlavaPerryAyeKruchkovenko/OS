#include <stdio.h>
#include <fileapi.h>
#include <windows.h>


const int n = 10000;
const int countThread = 2;
double res = 0;
double function(double x){
    return 3/x;
}
DWORD WINAPI FuncThread(LPVOID param){
    for (int i = 1; i <= n; i++) {
        if(i %  countThread == *((int*)param)){
            res += function(i);
        }
    }
    return 0;
}
int main() {
    int params[countThread];
    params[0] = 0;
    params[1] = 1;
    HANDLE hTreads[countThread];
    hTreads[0] = CreateThread(NULL,
                              0,
                              FuncThread,
                              &params[0],
                              0,
                              NULL);
    hTreads[1] = CreateThread(NULL,
                              0,
                              FuncThread,
                              &params[1],
                              0,
                              NULL);
    WaitForMultipleObjects(2,hTreads,TRUE,INFINITE);
    printf_s("%f",res);
    return 0;
}
