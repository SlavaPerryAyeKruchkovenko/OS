#define _CRT_SECURE_NO_WARNINGS
#define  MAX 64
#define  MIN 32
#include <stdio.h>
#include <windows.h>
#include <fileapi.h>
#include <string.h>
#include <winnt.h>

typedef struct Profile {
    char name[MIN];
    char nameOfWork[MAX];
    int age;
} Profile;
HANDLE openFile(LPCSTR nameOfFile){
	HANDLE file = CreateFile(
		nameOfFile,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	return file;
}
DWORD writeFile(HANDLE file,char* data,int size){
	DWORD bytesWritten;
	WriteFile(
		file,
		data,
		size,
		&bytesWritten,
		NULL
	);
	return bytesWritten;
}
void lockFile(HANDLE file,int start,int size,int access){
	OVERLAPPED ol;
	ol.OffsetHigh=0;
	ol.Offset=start;
	ol.hEvent = NULL;
	LockFileEx(file,access,0,size,0,&ol);
}
void unlockFile(HANDLE file,int start,int size,int access){
	OVERLAPPED ol;
	ol.OffsetHigh=0;
	ol.Offset=start;
	ol.hEvent = NULL;
	UnlockFileEx(file,access, 0, size, &ol);
}
Profile readFile(HANDLE file,int size){
	Profile data;
	DWORD bytesWritten;
	ReadFile(file,
            (char*)&data,
            size,
            &bytesWritten,
    		NULL);
	return 	data;	
}
Profile readProfile(HANDLE file,int numOfResume){
	int startPoint = sizeof(Profile) * (numOfResume - 1);
	SetFilePointer(file, sizeof(Profile) * (numOfResume - 1), 0, FILE_BEGIN);
	lockFile(file,startPoint,sizeof(Profile),0);
	return readFile(file,sizeof(Profile));
}
Profile registerBlank(){	

	Profile anketa;
	int res = 0;
	printf("Print age\n");
	scanf_s("%d", &res);
	anketa.age = res;

	printf("Print name\n");
	fscanf(stdin,"%s",anketa.name);

	printf("Print name of work\n");
	fscanf(stdin,"%s",anketa.nameOfWork);
	return anketa;
}
void writeProfileInFile(HANDLE file,Profile profile){
	SetFilePointer(file,0,0,FILE_END);	
	writeFile(file,(char*)&profile,sizeof(profile));
}
void editProfile(HANDLE file,int numOfResume){
	int startPoint = sizeof(Profile) * (numOfResume - 1);	
	lockFile(file,startPoint,sizeof(Profile),LOCKFILE_EXCLUSIVE_LOCK);
	Profile profile = registerBlank();	
	SetFilePointer(file,startPoint,0,FILE_BEGIN);	
	writeFile(file,(char*)&profile,sizeof(profile));
	CloseHandle(file);
}
void writeProfile(Profile profile){
	printf("%d\n", profile.age);
	printf("%s\n", profile.name);
	printf("%s\n", profile.nameOfWork);
}
void writeProfiles(HANDLE file){
	Profile profile;
	DWORD readedBytes;
	int numOfResume = 1;
	do{
		ReadFile(file, (char*)&profile, sizeof(Profile), &readedBytes, NULL);
		if (readedBytes != 0)
		{
			printf_s("num of resume %d\n",numOfResume);
			writeProfile(profile);
			numOfResume++;
		}
	}
	while (readedBytes != 0);
}
void clear(){
    system("cls");
}
int main()
{
	char* path  = "D:\\slava.bin";	//write your path
	HANDLE file;
	printf("Hello\n");
	while(1){
		file = openFile(path);
		fflush(stdin);
		clear();
		writeProfiles(file);

		printf_s("What are you want 1-Create Resume 2-Read Resumes\n");
		int res = 0;
		scanf_s("%d", &res); 
		while(res < 0 || res > 2){
			printf_s("please input correct value\n");
			printf_s("What are you want 1-Create File 2-Write Files\n");
			scanf_s("%d", &res); 
		}
		clear();
		if(res == 1){
			Profile profile = registerBlank();
			writeProfileInFile(file, profile);
		}
		else if(res == 2){
			fflush(stdin);
			printf("inpurt num of resume\n");
			scanf_s("%d", &res); 

			Profile profile = readProfile(file,res);
			unlockFile(file,sizeof(Profile) * (res - 1),sizeof(Profile),FILE_SHARE_READ | FILE_SHARE_WRITE);
			writeProfile(profile);
			CloseHandle(file);

			printf("Do you wanna edit y/n\n");
			int letter = getch();
			if(letter == 'y'){	
				file = openFile(path);
				editProfile(file,res);
			}		
		}
		fflush(stdin);
		printf_s("Do you wanna exit? y/n\n");
		res = getch();	
		CloseHandle(file);
		if(res == 'y'){
			return 0;
		}
	}	
	return 0;
}
