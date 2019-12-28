#include "LibraryFinder.h"

RegistryError::RegistryError(const char *message, LONG errorCode) : std::runtime_error{message}, m_errorCode{errorCode} { }

LibraryFinder::LibraryFinder() {}

std::set<std::string> LibraryFinder::FindLibraryPaths()
{
	std::set<std::string> returnVal;

	auto primaryLib = FindPrimaryPathFromRegistry();

	if (!primaryLib.empty())
	{
		if (LibraryFolder::IsValidDirectory(primaryLib))
		{
			returnVal.insert(primaryLib);
		}
	}


	return returnVal;
}

const std::string LibraryFinder::FindPrimaryPathFromRegistry()
{
	std::wstring substr = L"InstallPath";
	std::wstring key = L"SOFTWARE\\Valve\\Steam";
	std::wstring rawFoundValue = RegGetString(HKEY_LOCAL_MACHINE, key, substr);
	int rawLength = rawFoundValue.length();

	int sizeOfRawValue = WideCharToMultiByte(
		CP_UTF8, // charset
		WC_NO_BEST_FIT_CHARS, //Don't convert character to "best fit"
		rawFoundValue.c_str(), // input
		rawLength, // length of input
		NULL, // no output
		0, // no output size (will return size needed)
		NULL,
		NULL
	);

	std::string convertedValue;

	if (sizeOfRawValue)
	{
		convertedValue.resize(sizeOfRawValue);

		WideCharToMultiByte(
			CP_UTF8, // charset
			WC_NO_BEST_FIT_CHARS, //Don't convert character to "best fit"
			rawFoundValue.c_str(), // input
			rawFoundValue.length(), // length of input
			&convertedValue[0], // output
			sizeOfRawValue, //size of output
			NULL,
			NULL
		);
	}
	return convertedValue;
}

const std::wstring LibraryFinder::RegGetString(HKEY hKey, const std::wstring & subKey, const std::wstring & value) const
{	
	DWORD dataSize{};
	LONG retCode = ::RegGetValueW(
	hKey,
	subKey.c_str(),
	value.c_str(),
	RRF_RT_REG_SZ | RRF_SUBKEY_WOW6432KEY,
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
	RRF_RT_REG_SZ | RRF_SUBKEY_WOW6432KEY,
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