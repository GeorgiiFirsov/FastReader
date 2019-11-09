#include "pch.h"

#pragma region Necessary for linker

#include "../FastReader/FileHandler.cpp"
#include "../FastReader/Win32Error.cpp"

#pragma endregion 

#pragma region Settings

// ----------- Settings -----------
#define _units nanoseconds
#define loops_per_test 3
#define tests_count 10

// ---------- Do not edit ---------
#define units std::chrono::_units

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

    std::vector<size_t> results;
    results.reserve( tests_count );

    for(auto test = 0; test < tests_count; test++)
    {
        auto start = std::chrono::high_resolution_clock::now();

        for(auto tries = 0; tries < loops_per_test; tries++)
        {
            for(const auto& line : file)
            {
                std::string sTest = line;
                UNREFERENCED_PARAMETER( sTest );
            }
        }

        auto finish = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<units>( finish - start );

        results.push_back( duration.count() );
    }

    auto average = static_cast<double>(
        std::accumulate( results.cbegin(), results.cend(), static_cast<size_t>( 0 ) )
    ) / results.size();

    std::cout << std::endl
              << "CFileHandler: " << average
              << std::endl << std::endl;
}


TEST( Timing, fstream )
{
    std::ifstream file( szTextFile );

    std::vector<size_t> results;
    results.reserve( tests_count );

    for(auto test = 0; test < tests_count; test++)
    {
        auto start = std::chrono::high_resolution_clock::now();

        for(auto tries = 0; tries < loops_per_test; tries++)
        {
            std::string line;
            while(std::getline( file, line ))
            {
                std::string sTest = line;
                UNREFERENCED_PARAMETER( sTest );
            }
            file.clear();
            file.seekg( 0, std::ios_base::beg );
        }

        auto finish = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<units>( finish - start );

        results.push_back( duration.count() );
    }

    auto average = static_cast<double>(
        std::accumulate( results.cbegin(), results.cend(), static_cast<size_t>( 0 ) )
    ) / results.size();

    std::cout << std::endl
              << "std::ifstream: " << average
              << std::endl << std::endl;
}
