#include <iostream>
#include <string>
#include <Windows.h>
#include <sysinfoapi.h>
#include <locale>

void ReadFRFile(const char* path)
{
	if (HANDLE hFileMapping = OpenFileMappingA(GENERIC_READ | GENERIC_WRITE, FALSE, "writer"))
	{
		if (LPVOID p = MapViewOfFile(hFileMapping, FILE_MAP_ALL_ACCESS, 0, 0, 4096))
		{
			LPSTR msg = static_cast<LPSTR>(p);
			std::cout << " Содержимое из спроецированного файла: " << msg << std::endl;
			UnmapViewOfFile(p);
		}
		else
			std::cout << " Ошибка отображения: " << GetLastError() << std::endl;
		CloseHandle(hFileMapping);
	}
	else
		std::cout << " Ошибка открытия проецируемого файла : " << GetLastError() << std::endl;
}
int main()
{
	setlocale(LC_ALL, "Russian");
	std::string path = "C:\\Users\tyuri\Desktop\test.txt";
	ReadFRFile(path.c_str());
	return 0;
}