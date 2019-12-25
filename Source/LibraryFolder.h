#pragma once
#include <filesystem>
#include <string>
#include <iostream>

namespace fs = std::filesystem;

class LibraryFolder
{
 public:
	LibraryFolder();
	LibraryFolder(std::string Path);
	LibraryFolder(fs::directory_entry Directory);

	const bool IsValidDirectory() const;
	const std::string Name() const;
	const std::string Path() const;
	const uint64_t Size() const;
	const void RefreshFolderSize();

	const bool operator==(const LibraryFolder &) const;
	const bool operator!=(const LibraryFolder &) const;
	const bool operator<(const LibraryFolder &) const;
	const bool operator<=(const LibraryFolder &) const;
	const bool operator>(const LibraryFolder &) const;
	const bool operator>=(const LibraryFolder &) const;
	
protected:
	fs::directory_entry RootDirectory;
	uint64_t FolderSize = 0;

private:

};