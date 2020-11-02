#include <iostream>
#include <string>
#include <Windows.h>
#include <locale>
#include <sysinfoapi.h>

void WriteINFile(const char* path)
{
	//Функция CreateFile создает или открывает каталог, физический диск, том и т.п.Функция возвращает дескриптор, который может быть использован для доступа к объекту.
	HANDLE hFile = CreateFileA(path, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	// Функция CreateFileMapping создает или открывает именованный или безымянный объект отображенного в памяти (проецируемого) файла для заданного файла.
	HANDLE hFileMapping = CreateFileMappingA(hFile, NULL, PAGE_READWRITE, 0, 4096, "writer"); 
	CloseHandle(hFile);
	// Функция MapViewOfFile отображает представление проецируемого файла в адресное пространство вызывающего процесса.
	if (LPVOID p = MapViewOfFile(hFileMapping, FILE_MAP_ALL_ACCESS, 0, 0, 4096))
	{
		std::string str;
		std::cout << " Ввод данных: "; 
		std::getline(std::cin, str);
		//Функция CopyMemory копирует блок памяти из одного места в другой с использованием указателей.
		CopyMemory((PVOID)p, str.c_str(), str.length() * sizeof(char));
		system("pause");
		//Функция UnmapViewOfFile отменяет отображение  представления файла из адресного пространства вызывающего процесса.
		UnmapViewOfFile(p);
		}
		else
			std::cout << " Ошибка: " << GetLastError() << std::endl; 
}
int main()
{
	setlocale(LC_ALL, "Russian");
	std::string path = "C:\\Users\tyuri\Desktop\test.txt";
	WriteINFile(path.c_str());
	return 0;
}
