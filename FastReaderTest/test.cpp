#include "pch.h"

#pragma region Necessary for linker

#include "../FastReader/FileHandler.cpp"
#include "../FastReader/Win32Error.cpp"

#pragma endregion 

constexpr auto szNoSuchFile = L"./NoSuchFile.txt";
constexpr auto szTextFile = L"../TestFile.txt";

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

TEST( CFileHandler, ExistingFile )
{
    ASSERT_NO_THROW(
        CFileHandler file( szTextFile );
    );
}

TEST( CFileHandler, ExistingFileOutput )
{
    CFileHandler file( szTextFile );

#ifdef _DEBUG
    std::cout << std::endl;

    for(const auto line : file) {
        std::cout << line;
    }

    std::cout << std::endl << std::endl;
#else
    std::wcout << std::endl << L"Output is available only in debug builds\n" << std::endl;
#endif

}



TEST( Timing, CFileHandler )
{
    CFileHandler file( szTextFile );

    auto start = std::chrono::high_resolution_clock::now();

    for(const auto& line : file)
    {
        std::string sTest = line;
        UNREFERENCED_PARAMETER( sTest );
    }

    auto finish = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( finish - start );

    std::cout << std::endl
              << "CFileHandler: " << duration.count() << " ns."
              << std::endl << std::endl;
}


TEST( Timing, fstream )
{
    std::ifstream file( szTextFile );

    auto start = std::chrono::high_resolution_clock::now();

    std::string line;
    while(std::getline( file, line ))
    {
        std::string sTest = line;
        UNREFERENCED_PARAMETER( sTest );
    }

    auto finish = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( finish - start );

    std::cout << std::endl
              << "std::ifstream: " << duration.count() << " ns."
              << std::endl << std::endl;
}
