#pragma once

#include "stdafx.h"


class CFileHandler
{
    class CFileHandlerIterator
		: std::iterator<std::forward_iterator_tag, LPCSTR>
    {
    public:

        explicit CFileHandlerIterator( const BYTE* pPosition, LONGLONG cbSize ) noexcept
			: m_pPosition( pPosition )
            , m_cbFileSize( cbSize )
            , m_cbOffset( 0 )
        { }

        ~CFileHandlerIterator() = default;

        CFileHandlerIterator( const CFileHandlerIterator& ) = default;
        CFileHandlerIterator( CFileHandlerIterator&& ) = default;

        CFileHandlerIterator& operator=( const CFileHandlerIterator& ) = default;
        CFileHandlerIterator& operator=( CFileHandlerIterator&& ) = default;

        value_type operator*() const noexcept
        { return reinterpret_cast<LPCSTR>( m_pPosition ); }

        bool operator==( const CFileHandlerIterator& other ) const noexcept
        { return this->m_pPosition == other.m_pPosition; }

        bool operator!=( const CFileHandlerIterator& other ) const noexcept
        { return this->m_pPosition != other.m_pPosition; }

        CFileHandlerIterator& operator++();   // prefix
        CFileHandlerIterator operator++(int); // postfix

    private:
        LONGLONG m_cbFileSize, m_cbOffset;
        const BYTE* m_pPosition;
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

