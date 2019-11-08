#include "stdafx.h"

#include "Win32Error.h"


CWin32Error::CWin32Error( DWORD dwErrorCode )
{
    LPWSTR szDescription = nullptr;

    DWORD cchWritten = ::FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        dwErrorCode,
        MAKELANGID( LANG_NEUTRAL, SUBLANG_SYS_DEFAULT ),
        reinterpret_cast<LPWSTR>( &szDescription ),
        0 /* nSize */,
        nullptr
    );

    if(!cchWritten) 
    {
        DWORD dwLastError = ::GetLastError();
        std::string sError = "Fatal error: " + std::to_string( dwLastError );
        throw std::runtime_error( sError );
    }

    m_dwCode = dwErrorCode;
    m_sDescription = std::wstring( szDescription, cchWritten );

    ::LocalFree( szDescription );
}
