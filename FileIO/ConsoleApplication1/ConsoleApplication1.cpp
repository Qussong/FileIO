
#include <iostream>

#include <fstream>
#include <string>
#include <vector>
#include <locale>
#include <codecvt>

#include <thread> // for std::this_thread::sleep_for
#include <chrono> // for std::chrono::milliseconds

std::wifstream readFile;
std::vector<std::wstring> lineContainer;

int main()
{
	readFile.imbue(std::locale(readFile.getloc(), new std::codecvt_utf8<wchar_t>));
	std::wcout.imbue(std::locale(""));

	// OPEN
	readFile.open(L"test.txt");	// 파일 경로 설정
	if (false == readFile.is_open())
		std::cout << "Failed to open file for reading!" << std::endl;

	// READ
	bool bEnd = false;
	std::wstring line;
	while (false == bEnd)
	{
		std::getline(readFile, line);
		lineContainer.push_back(line);

		if (readFile.eof()) 
			bEnd = true;

		if (readFile.fail())
		{
			std::cerr << "An error occurred while reading the file!" << std::endl;
			bEnd = true;
		}
	}

	// MODIFY
	for (int i = 0; i < lineContainer.size(); i++)
	{
		char target = '#';
		size_t pos = lineContainer[i].find(target);

		while (pos != std::string::npos) {
			if (pos != std::string::npos)
			{
				lineContainer[i].replace(pos, 1, L"PLAYER");
			}
			pos = lineContainer[i].find(target, pos + 1);
		}
	}

	// WRITE
	for (int i = 0; i < lineContainer.size(); i++)
	{
		std::wcout << lineContainer[i] << std::endl;
	}


	return 0;
}
