#include "LibraryFinder.h"

RegistryError::RegistryError(const char * message, LONG errorCode) : std::runtime_error{message}, m_errorCode{errorCode} { }

LibraryFinder::LibraryFinder() {}

const std::wstring LibraryFinder::RegGetString(HKEY hKey, const std::wstring & subKey, const std::wstring & value)
{
	DWORD dataSize{};
	LONG retCode = ::RegGetValueW(
	hKey,
	subKey.c_str(),
	value.c_str(),
	RRF_RT_REG_SZ,
	nullptr,
	nullptr,
	&dataSize);

	if (retCode != ERROR_SUCCESS)
	{
		throw RegistryError { "Cannot read string from registry", retCode };
	}

	std::wstring data;
	data.resize(dataSize / sizeof(wchar_t));

	retCode = ::RegGetValueW(
	hKey,
	subKey.c_str(),
	value.c_str(),
	RRF_RT_REG_SZ,
	nullptr,
	&data[0],
	&dataSize);

	if (retCode != ERROR_SUCCESS)
	{
		throw RegistryError { "Cannot read string from registry", retCode };
	}

	DWORD stringLengthInWchars = dataSize / sizeof(wchar_t);

	stringLengthInWchars--; // Exclude the NUL written by the Win32 API
	data.resize(stringLengthInWchars);

	return data;
}