
#include "windows.h"
#include <stdio.h>
#include<TCHAR.H> 


int _tmain(int argc, _TCHAR* argv[])
{
	int i;
	HANDLE hFile, hMap;
	LPVOID lpFile;
	char** lpFuncs, * lpFuncName;
	PIMAGE_DOS_HEADER lpDOS;
	PIMAGE_NT_HEADERS32 lpNT;
	PIMAGE_SECTION_HEADER lpSections;
	PIMAGE_EXPORT_DIRECTORY lpExport;
	//Здесь в первом параметре передаем путь к dll
	hFile = CreateFile(TEXT("D:\\repoditory\\OS\\desktop\\lab3\\test\\liblibrary.dll.a"),
		GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	hMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	//lpFile - указатель на отображенную на память dll
	lpFile = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
	lpDOS = (PIMAGE_DOS_HEADER)lpFile;
	printf("DOS-> new header:%d\n", lpDOS->e_lfanew);
	//Поле e_lfanew содержит смещение заголовка NT
	lpNT = (PIMAGE_NT_HEADERS32)((DWORD)lpFile + lpDOS->e_lfanew);
	printf("NT sig: %s\n", (char*)&(lpNT->Signature));
	printf("NT sections: %d\n", lpNT->FileHeader.NumberOfSections);

	//С помощью макроса находим адрес массива, который описывает секции
	lpSections = IMAGE_FIRST_SECTION(lpNT);
	//Определяем, в какой из секций находятся данные экспорта
	//У нас есть только виртуальный адрес структуры, описывающей эти данные
	//поэтому ищем секцию, у которой виртуальный адрес и размер соответствуют этому адресу
	for (i = 0; i < lpNT->FileHeader.NumberOfSections; i++)
	{
		if (lpSections[i].VirtualAddress <= lpNT->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress \
			&& lpSections[i].VirtualAddress + lpSections[i].Misc.VirtualSize >= lpNT->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress)
			break;
	}
	printf("Section export: %s\n", lpSections[i].Name);
	//Вычисляем адрес данных экспорта как АДРЕС_НАЧАЛА_СЕКЦИИ + СМЕЩЕНИЕ
	//АДРЕС_НАЧАЛА_СЕКЦИИ=lpFile+PointerToRawData
	//СМЕЩЕНИЕ=разность виртуальных адресов нужной структуры и начала секции
	//PointerToRawData - смещение начала секции относит. начала файла
	lpExport = (PIMAGE_EXPORT_DIRECTORY)((DWORD)lpFile + lpSections[i].PointerToRawData + \
		(lpNT->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress - \
			lpSections[i].VirtualAddress));
	printf("Number of names: %d\n", lpExport->NumberOfNames);
	//lpExport->AddressOfNames
	//По такому же принципу вычисляем адрес массива из строк и первой строки
	lpFuncs = (char**)((DWORD)lpFile + lpSections[i].PointerToRawData + \
		(lpExport->AddressOfNames - \
			lpSections[i].VirtualAddress));
	lpFuncName = (char*)((DWORD)lpFile + lpSections[i].PointerToRawData + \
		(lpFuncs[0] - \
			lpSections[i].VirtualAddress));
	printf("Func name: %s\n", lpFuncName);

	return 0;
}

