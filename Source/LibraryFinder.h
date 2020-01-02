#pragma once
#include <string>
#include <stdexcept>
#include <set>
#include <vector>
#include "Windows.h"
#include "LibraryFolder.h"
#include "Library.h"
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
    const std::set<Library, CompareLibraryPaths> FindLibraryPaths() const;

protected:
    const std::vector<fs::directory_entry> FindSubLibraries(const fs::directory_entry &) const;
    const std::string FindPrimaryPathFromRegistry() const;
    const std::wstring RegGetString(HKEY hKey, const std::wstring &subKey, const std::wstring &value) const;

private:

};

/*
main reg locations:
32-bit: HKEY_LOCAL_MACHINE\SOFTWARE\Valve\Steam
64-bit: HKEY_LOCAL_MACHINE\SOFTWARE\Wow6432Node\Valve\Steam

secondary locations:
\steamapps\libraryfolders.vdf

*/