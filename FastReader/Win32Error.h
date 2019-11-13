#pragma once

#include "stdafx.h"

class CWin32Error
{
public:
    explicit CWin32Error( DWORD dwErrorCode );

    DWORD Code() const noexcept { return m_dwCode; }
    LPCWSTR Description() const { return m_sDescription.c_str(); }

private:
    DWORD m_dwCode;
    std::wstring m_sDescription;
};

#define WIN32_ERROR_THROW_LAST() throw CWin32Error( GetLastError() )