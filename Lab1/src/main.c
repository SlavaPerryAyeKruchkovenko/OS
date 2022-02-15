#define _CRT_SECURE_NO_WARNINGS
#define  MAX 64
#define  MIN 32
#include <stdio.h>
#include <windows.h>
#include <fileapi.h>
#include <string.h>
#include <winnt.h>


void clear(){
    system("cls");
}
HANDLE createFile(LPCSTR nameOfFile){
	return CreateFile(
		nameOfFile,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ,
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
void printAllNameOfResume(HANDLE file){
	SetFilePointer(file,0,0,FILE_END);
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
void writeField(char result[],char name[],char* text,char* text2,HANDLE file){
	memset(result,0,MAX);
	printf("%s", text);
	fscanf(stdin,"%s",name);
	snprintf(result, MAX, "%s%s", text2, name);		
	writeFile(file,result,MAX);
}
void registerBlank(HANDLE file){	
	SetFilePointer(file,0,0,FILE_END);
	char name[MIN];
	char result[MAX];
	writeField(result,name,"Write name of resume\n","\n",file);
	writeField(result,name,"write name\n","\nname:",file);
	writeField(result,name,"write sex\n","\nsex:",file);
	writeField(result,name,"write post\n","\npost:",file);
	writeField(result,name,"write experience\n","\nexperience:",file);
	writeField(result,name,"Write year of born\n","\nyear of born:",file);
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
			registerBlank(file);
		}
		else if(res == 2){
			printf("All resume\n");
			char result[64];
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
