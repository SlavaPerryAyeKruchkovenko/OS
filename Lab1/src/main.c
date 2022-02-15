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
void printAllFiles(char *path){
	WIN32_FIND_DATA FindFileData;
    HANDLE hf;
    hf = FindFirstFile(path,&FindFileData);
    if(hf != INVALID_HANDLE_VALUE){
        do{
            printf("%s\n",FindFileData.cFileName);
        }
        while(FindNextFile(hf,&FindFileData) != 0);
        FindClose(hf);
    }    
}
/*FILE openFile(char *nameOfFile){

}*/
void registerBlank(HANDLE file){
	char name[16];
	char result[32];

	memset(result,0,32);
	printf("Введите имя\n");
	fscanf(stdin,"%s",name);
	snprintf(result, sizeof  result, "%s%s", "\n name:", name);	
	writeFile(file,result,32);

	memset(result,0,32);
	printf("Введите пол\n");
	fscanf(stdin,"%s",name);
	snprintf(result, sizeof  result, "%s%s", "\n sex:", name);		
	writeFile(file,result,32);
	
	memset(result,0,32);
	printf("Введите должность\n");
	fscanf(stdin,"%s",name);
	snprintf(result, sizeof  result, "%s%s", "\n post:", name);		
	writeFile(file,result,32);

	memset(result,0,32);
	printf("Введите Стаж\n");
	fscanf(stdin,"%s",name);
	snprintf(result, sizeof  result, "%s%s", "\n experience:", name);		
	writeFile(file,result,32);

	memset(result,0,32);
	printf("Введите Год рождения\n");
	fscanf(stdin,"%s",name);	
	snprintf(result, sizeof  result, "%s%s", "\n year of born:", name);		
	writeFile(file,result,32);
}
int main()
{
	char* path  = "D:\\repoditory\\OS\\Lab1\\resumes\\";
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
		printf("Write name of File\n");

		char name[30];

		fscanf(stdin,"%s",name);	
		char result[512];
		snprintf(result, sizeof  result, "%s%s", path, name);
		snprintf(result, sizeof  result, "%s%s", result, ".bin");
		HANDLE file = createFile(result);	
		registerBlank(file);
	}
	else if(res == 2){
		printf("All resume\n");
	}
	return 0;
}
