#pragma once
#include <string>
#include <stdexcept>
#include "Windows.h"
//#include "winreg.h"
//#include "winerror.h"

// This document lifted from:
// https://docs.microsoft.com/en-us/archive/msdn-magazine/2017/may/c-use-modern-c-to-access-the-windows-registry#reading-a-string-value-from-the-registry

class RegistryError : public std::runtime_error
{
public:
    RegistryError(const char * message, LONG errorCode);
    LONG ErrorCode() const noexcept { return m_errorCode; }

private:
  LONG m_errorCode;
};

class LibraryFinder
{
public:
    LibraryFinder();

    const std::wstring RegGetString(HKEY hKey, const std::wstring & subKey, const std::wstring & value);

private:

};