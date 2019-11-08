#include "pch.h"

#pragma region Necessary for linker

#include "../FastReader/FileHandler.cpp"
#include "../FastReader/Win32Error.cpp"

#pragma endregion 

constexpr auto szNoSuchFile = L"./NoSuchFile.txt";
constexpr auto szTextFile = L"./TestFile.txt";

TEST( CFileHandler, NoSuchFile )
{
    ASSERT_THROW(
        CFileHandler file( szNoSuchFile ),
        CWin32Error
	);
}

TEST( CFileHandler, NoSuchFileOutput )
{
    try
    {
        CFileHandler file( szNoSuchFile );
    }
    catch (const CWin32Error& error )
    {
        setlocale( LC_ALL, "russian" );

#ifdef _DEBUG
        std::wcout << std::endl << error.Description() << std::endl;
#else
        UNREFERENCED_PARAMETER( error );

        std::wcout << std::endl << L"Output is available only in debug builds\n" << std::endl;
#endif

    }
}
