#include <stdio.h>
#include <windows.h>
#include <fileapi.h>
#include <string.h>
#include <winnt.h>

#define PATH = L"/resumes/";
void clear(){
    system("cls");
}
HANDLE createFile(LPCSTR nameOfFile){
	return CreateFile(
		nameOfFile,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
}
DWORD writeFile(HANDLE file,char* text,int size){
	DWORD bytesWritten;
	WriteFile(
		file,
		text,
		size,
		&bytesWritten,
		NULL
	);
	return bytesWritten;
}
void printAllNameOfResume(char *path){
	
}
void openFile(char *nameOfFile){

}
void lockFile(HANDLE file,int start){
	OVERLAPPED ol;
	ol.OffsetHigh=0;
	ol.Offset=start;
	ol.hEvent = NULL;
	LockFileEx(file,0,0,192,0,&ol);
}
void registerBlank(char* nameOfRes, HANDLE file){	
	SetFilePointer(file,0,0,FILE_END);
	char name[16];
	char result[32];
	snprintf(result, sizeof  result, "%s%s", "\n:", nameOfRes);	
	writeFile(file,result,32);

	memset(result,0,32);
	printf("write name\n");
	fscanf(stdin,"%s",name);
	snprintf(result, sizeof  result, "%s%s", "\nname:", name);	
	writeFile(file,result,32);

	memset(result,0,32);
	printf("write sex\n");
	fscanf(stdin,"%s",name);
	snprintf(result, sizeof  result, "%s%s", "\nsex:", name);		
	writeFile(file,result,32);
	
	memset(result,0,32);
	printf("write post\n");
	fscanf(stdin,"%s",name);
	snprintf(result, sizeof  result, "%s%s", "\npost:", name);		
	writeFile(file,result,32);

	memset(result,0,32);
	printf("write experience\n");
	fscanf(stdin,"%s",name);
	snprintf(result, sizeof  result, "%s%s", "\nexperience:", name);		
	writeFile(file,result,32);

	memset(result,0,32);
	printf("Write year of born\n");
	fscanf(stdin,"%s",name);	
	snprintf(result, sizeof  result, "%s%s", "\nyear of born:", name);		
	writeFile(file,result,32);
}
int main()
{
	char* path  = "D:\\repoditory\\OS\\Lab1\\resumes\\slava.bin";	
	HANDLE file = createFile(path);
	printf("Hello\n");
	while(1){
		clear();
		printf("What are you want 1-Create Resume 2-Write Resume\n");
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
			printf("Write name of resume\n");

			char name[32];
			fscanf(stdin,"%s",name);	

			registerBlank(name,file);
		}
		else if(res == 2){
			printf("All resume\n");
			char result[512];
			snprintf(result, sizeof  result, "%s%s", path, "*.bin");
			printAllNameOfResume(result);
			FILE* input;
			char name[32];
			do{
				printf("Select resume\n");	
				fscanf(stdin,"%s",name);
				snprintf(name, sizeof  result, "%s%s", name, ".bin");
				snprintf(result, sizeof  result, "%s%s", path, name);
				input = fopen(result, "r");
				if(!input){
					printf("incorrect resume\n");	
				}
			}			
			while(!input);
			do{
				printf("What are you want 1-Edit 2- Open\n");
				scanf_s("%d", &res); 
				if(res < 0 || res > 3){
					printf("incorrect name\n");
				}
			}
			while(res < 1 || res > 3);
		}
	}	
	return 0;
}
