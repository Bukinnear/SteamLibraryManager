#pragma once
#include <string>
#include <stdexcept>
#include <set>
#include <locale>
#include <codecvt>
#include "Windows.h"
#include "LibraryFolder.h"
//#include "winreg.h"
//#include "winerror.h"

// Heavy "inspiration" from:
// https://docs.microsoft.com/en-us/archive/msdn-magazine/2017/may/c-use-modern-c-to-access-the-windows-registry#reading-a-string-value-from-the-registry
// https://stackoverflow.com/questions/42793735/how-to-convert-between-widecharacter-and-multi-byte-character-string-in-windows

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
    std::set<std::string> FindLibraryPaths();

private:
    const std::string FindPrimaryPathFromRegistry();
    const std::wstring RegGetString(HKEY hKey, const std::wstring &subKey, const std::wstring &value) const;

};