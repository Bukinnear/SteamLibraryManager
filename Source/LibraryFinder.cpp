#include "LibraryFinder.h"

RegistryError::RegistryError(const char *message, LONG errorCode) : std::runtime_error{message}, m_errorCode{errorCode} { }

LibraryFinder::LibraryFinder() {}

const std::set<Library, CompareLibraryPaths> LibraryFinder::FindLibraryPaths() const
{
	std::set<Library, CompareLibraryPaths> returnVal;

	auto primaryLibraryPath = FindPrimaryPathFromRegistry();

	if (!primaryLibraryPath.empty())
	{
		fs::directory_entry folder(primaryLibraryPath);
		if (folder.exists())
		{
			returnVal.insert(folder);

			auto vdfPath = Library::LibraryFoldersVDF(primaryLibraryPath);
			auto subLibraries = FindSubLibraries(vdfPath);

			for (auto lib : subLibraries)
			{
				if (Library::IsValidLibrary(lib))
				{
					returnVal.insert(Library(lib));
				}
			}
		}
	}
	return returnVal;
}

const std::vector<fs::directory_entry> LibraryFinder::FindSubLibraries(const fs::directory_entry &vdf) const
{
	std::vector<fs::directory_entry> returnVal;

	std::ifstream file(vdf);
	std::string currentLine;

	while (std::getline(file, currentLine))
	{
		if (currentLine[0] != '\t' || currentLine[0] == '}' || currentLine.length() == 0)
		{
			continue;
		}

		int strStart;
		int strEnd;
		int count;
		
		strEnd = currentLine.find_last_of("\"", currentLine.length()) - 1;

		if (strEnd == currentLine.npos)
		{ continue; }

		strStart = currentLine.find_last_of("\"", strEnd) + 1;

		if (strStart == currentLine.npos)
		{ continue; }
		
		count = strEnd - strStart + 1;
		std::string value = currentLine.substr(strStart, count);
		auto path = fs::directory_entry(value);

		if (Library::IsValidLibrary(path))
		{ returnVal.push_back(path); }
	}
	return returnVal;
}

const std::string LibraryFinder::FindPrimaryPathFromRegistry() const
{
	std::wstring substr = L"InstallPath";
	std::wstring key = L"SOFTWARE\\Valve\\Steam";
	std::wstring rawFoundValue;
	try
	{
		rawFoundValue = RegGetString(HKEY_LOCAL_MACHINE, key, substr);
	}
	catch (const std::exception&) 
	{ 
		std::cout << "\nERROR: Could not get steam directory from registry.\n"; 
		return "";
	}
	
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