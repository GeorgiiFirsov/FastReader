#include "stdafx.h"

#include "FileHandler.h"
#include "Win32Error.h"


CFileHandler::CFileHandlerIterator& 
CFileHandler::CFileHandlerIterator::operator++()
{
    m_pPosition = reinterpret_cast<const BYTE*>( 
		memchr( m_pPosition, '\n', m_cbFileSize - m_cbOffset ) 
	);

    if(m_pPosition) m_pPosition++;

    return *this;
}


CFileHandler::CFileHandlerIterator
CFileHandler::CFileHandlerIterator::operator++(int)
{
    auto copy = *this;

    ++*this;

    return copy;
}


CFileHandler::CFileHandler()
	: m_pbData( nullptr )
    , m_pbCurrentPosition( nullptr )
    , m_cbFileSize( 0 )
    , m_cbOffset( 0 )
    , m_bIsOpened( false )
{ }


CFileHandler::CFileHandler( const std::wstring& sFileName )
{
    Open( sFileName.c_str() );
}


CFileHandler::~CFileHandler()
{
    Unmap();
}


void CFileHandler::Open( LPCWSTR szFileName )
{
    if(m_bIsOpened) {
        Unmap();
	}

    //
    // Here I get file handle
    //
    CHandle hFile;

    hFile.m_h = CreateFile(
	    szFileName,
        GENERIC_READ,
        FILE_SHARE_READ,
        nullptr,
        OPEN_EXISTING,
        0 /* dwFlagsAndAttributes */,
        nullptr
	);

    if(hFile == INVALID_HANDLE_VALUE) {
        WIN32_ERROR_THROW_LAST();
    }


    //
    // Now let's get file size
    //
    LARGE_INTEGER lSize;
    BOOL bResult = GetFileSizeEx( hFile, &lSize );

    if(!bResult) {
        WIN32_ERROR_THROW_LAST();
    }

    m_cbFileSize = lSize.QuadPart;


    //
    // Here I need to map file into a memory
    //
    CHandle hFileMapping;

    hFileMapping.m_h = CreateFileMapping(
	    hFile,
        nullptr,
        PAGE_READONLY,
        0 /* dwMaximumSizeHigh */,
        0 /* dwMaximumSizeLow */,
        nullptr
	);

    if(!hFileMapping) {
        WIN32_ERROR_THROW_LAST();
    }


    //
    // Filnally I get a pointer to mapped data
    //
    LPVOID pData = MapViewOfFile(
	    hFileMapping,
        FILE_MAP_READ,
        0 /* dwFileOffsetHigh */,
        0 /* dwFileOffsetLow */,
        0 /* dwNumberOfBytesToMap */
	);

    if(!pData) {
        WIN32_ERROR_THROW_LAST();
    }


    //
    // Here I set class member's values
    //
    m_pbData = static_cast<PBYTE>( pData );
    m_pbCurrentPosition = m_pbData;
    m_cbOffset = 0;
    m_bIsOpened = true;
}


void CFileHandler::Close()
{
    Unmap();
}


void CFileHandler::Unmap()
{
    if(m_pbData)
    {
        //
        // m_bIsOpened shoul never be false here
        //
        assert( m_bIsOpened );

        UnmapViewOfFile( m_pbData );

        m_pbData = nullptr;
        m_pbCurrentPosition = nullptr;
        m_cbFileSize = 0;
        m_cbOffset = 0;
        m_bIsOpened = false;
    }
}
