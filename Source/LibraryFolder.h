#pragma once
#include <filesystem>
#include <string>
#include <iostream>

namespace fs = std::filesystem;

class LibraryFolder
{
 public:
	LibraryFolder();
	LibraryFolder(const std::string_view &Path);
	LibraryFolder(const fs::directory_entry &Directory);

	const bool IsValidDirectory() const;
	static const bool IsValidDirectory(const fs::directory_entry &);
	static const bool IsValidDirectory(const std::string_view &);
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