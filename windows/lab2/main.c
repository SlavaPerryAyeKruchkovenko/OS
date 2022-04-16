#include <windows.h>
#include <stdio.h>

int Arr[] =
        {28, 64, 88, '\0','\0','\0','\0',
         1, 2, 3, 4, 5, '\0','\0','\0','\0',
         6, 7, 10 ,8,'\0','\0',
         4, 3, 2, '\0',0,};

int main() {
    int i, n;
    DWORD nBytes;
    int *lpData, *lpArr;
    HANDLE hMap;
    HANDLE hFile = CreateFile(TEXT("lab2.dat"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            printf("File not exist. Creating...\n");
            hFile = CreateFile(TEXT("lab2.dat"),
                               GENERIC_READ | GENERIC_WRITE,
                               0,
                               NULL,
                               OPEN_ALWAYS,
                               FILE_ATTRIBUTE_NORMAL,
                               NULL);
            WriteFile(hFile, Arr, sizeof(Arr), &nBytes, NULL);
            CloseHandle(hFile);
            hFile = CreateFile(TEXT("lab2.dat"),
                                      GENERIC_READ, 0,
                                      NULL,
                                      OPEN_EXISTING,
                                      FILE_ATTRIBUTE_NORMAL,
                                      NULL);
        } else {
            printf("Error!\n");
            return 0;
        }
    WriteFile(hFile, Arr, sizeof(Arr), &nBytes, NULL);
    hMap = CreateFileMapping(hFile,
                             NULL,
                             PAGE_READONLY,
                             0,
                             0,
                             NULL);
    if (hMap != 0) {
        lpData = (int *) MapViewOfFile(hMap,
                                       FILE_MAP_READ,
                                       0,
                                       0,
                                       '\0');
        i=0;
        do{
            i++;
        }while(lpData[i]);

        do {
            system("cls");
            printf("Number of arrays - %d\n", i);
            printf("Enter array number(1-%d): ", i);
            scanf_s("%d", &n);
            if (n >= 1 && n <= i) {
                lpArr = (int *) ((char *) lpData + lpData[n - 1]);

                for (i = 0; lpArr[i]; i++) {
                    char value = lpArr[i];
                    printf("%d ", value);
                }

                printf("\n");
                break;
            }
            printf("incorrect value");
        } while (1);

    }
    return 0;
}