#include <stdio.h>
#include <windows.h>

void clear(){
    system("cls");
}
void createFile(char *nameOfFile);
FILE openFile(char *nameOfFile);
int main()
{
	printf("Hello\n");
	printf("What are you want 1-Create File 2-Write Files\n");
	int res = 0;
	scanf_s("%d", &res); 
	while(res < 0 || res > 2){
		printf_s("please input correct value");
		printf_s("What are you want 1-Create File 2-Write Files\n");
		scanf_s("%d", &res); 
	}
	clear();
	if(res == 1){
		printf("New resume\n");

	}
	else if(res == 2){
		printf("All resume\n");
	}
	return (0);
}