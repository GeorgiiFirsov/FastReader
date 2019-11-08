#pragma once

#include "stdafx.h"


class CFileHandler
{
    class CFileHandlerIterator
        : std::iterator<std::forward_iterator_tag, LPCSTR>
    {
    public:

        explicit CFileHandlerIterator( const BYTE* pPosition, LONGLONG cbSize ) noexcept
            : m_cbFileSize( cbSize )
            , m_cbOffset( 0 )
            , m_pbPosition( pPosition )
            , m_pbEndOfLine( (PBYTE)memchr( pPosition, '\n', cbSize ) + 1 )
        { }

        ~CFileHandlerIterator() = default;

        CFileHandlerIterator( const CFileHandlerIterator& ) = default;
        CFileHandlerIterator( CFileHandlerIterator&& ) = default;

        CFileHandlerIterator& operator=( const CFileHandlerIterator& ) = default;
        CFileHandlerIterator& operator=( CFileHandlerIterator&& ) = default;

        std::string operator*() const noexcept
        {
            return m_pbEndOfLine
                ? std::string( (CHAR*)m_pbPosition, (CHAR*)m_pbEndOfLine )
                : std::string( (CHAR*)m_pbPosition, m_cbFileSize - m_cbOffset );
        }

        bool operator==( const CFileHandlerIterator& other ) const noexcept
        { return this->m_pbPosition == other.m_pbPosition; }

        bool operator!=( const CFileHandlerIterator& other ) const noexcept
        { return this->m_pbPosition != other.m_pbPosition; }

        CFileHandlerIterator& operator++();   // prefix
        CFileHandlerIterator operator++(int); // postfix

    private:
        LONGLONG m_cbFileSize, m_cbOffset;
        const BYTE* m_pbPosition;
        const BYTE* m_pbEndOfLine;
    };

    using iterator = CFileHandlerIterator;
    using const_iterator = CFileHandlerIterator;

public:
    CFileHandler();
    CFileHandler( const std::wstring& sFileName );

    ~CFileHandler();

    CFileHandler( const CFileHandler& ) = delete;
    CFileHandler( CFileHandler&& ) = delete;

    CFileHandler& operator=( const CFileHandler& ) = delete;
    CFileHandler& operator=( CFileHandler&& ) = delete;
    
    void Open( LPCWSTR szFileName );
    void Close();

    iterator begin() noexcept { return iterator( m_pbData, m_cbFileSize ); }
    iterator end() noexcept { return iterator( nullptr, 0 ); }

    const_iterator cbegin() const noexcept { return const_iterator( m_pbData, m_cbFileSize );}
    const_iterator cend() const noexcept { return const_iterator( nullptr, 0 ); }

private:
    void Unmap();

private:
    const BYTE* m_pbData;
    const BYTE* m_pbCurrentPosition;

    LONGLONG m_cbFileSize;
    LONGLONG m_cbOffset;

    bool m_bIsOpened;
};

