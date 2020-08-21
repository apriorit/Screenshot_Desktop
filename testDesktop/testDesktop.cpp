// testDesktop.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace guards;

void SaveVectorToFile(const std::wstring& fileName, const std::vector<unsigned char>& data)
{
    HANDLE hFile = CreateFileW(fileName.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, 0, NULL);
    if(hFile == INVALID_HANDLE_VALUE)
		throw std::logic_error("SaveVectorToFile : can't open file ");
    guards::CHandleGuard fileGuard(hFile);
    DWORD bytesWriten = 0;
	if(!WriteFile(hFile, &data[0], (DWORD)data.size(), &bytesWriten, 0))
		throw std::logic_error("SaveVectorToFile : can't write to file ");
}

int _tmain(int argc, _TCHAR* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: [file name]" << std::endl;
        return 0;
    }
    std::vector<unsigned char> dataScreen;
    ScreenShooter::CaptureScreen(dataScreen);

    const wchar_t* filename = argv[1];
    SaveVectorToFile(filename, dataScreen);
    return 0;
}

