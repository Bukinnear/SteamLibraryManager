#pragma once
#include "LibraryFolder.h"

LibraryFolder::LibraryFolder(const std::string_view &Path) : RootDirectory(Path) {}

LibraryFolder::LibraryFolder(const fs::directory_entry &Directory) : RootDirectory(Directory) {}

LibraryFolder::LibraryFolder() {}

const bool LibraryFolder::IsValidDirectory() const
{
	return (fs::exists(RootDirectory) && fs::is_directory(RootDirectory));
}

const bool LibraryFolder::IsValidDirectory(const fs::directory_entry &folder)
{
	return (fs::exists(folder) && fs::is_directory(folder));
}

const bool LibraryFolder::IsValidDirectory(const std::string_view &folder)
{
	return (fs::exists(folder) && fs::is_directory(folder));
}

const std::string LibraryFolder::Name() const
{
	return RootDirectory.path().filename().string();
}

const std::string LibraryFolder::Path() const
{
	return RootDirectory.path().string();
}

const uint64_t LibraryFolder::Size() const
{
	return FolderSize; 
}

void LibraryFolder::RefreshFolderSize()
{
	if (!IsValidDirectory() || fs::is_empty(RootDirectory)) { FolderSize = 0; }
	
	uint64_t Size = 0;

	for (auto & p : fs::recursive_directory_iterator(RootDirectory))
	{
		if (fs::is_directory(p) || fs::is_empty(p)) 
		{
			continue; 
		}
		try
		{
			Size += (fs::file_size(p));
		}
		catch(const std::exception& e)
		{
			std::cerr << "\r\nSomething went wrong while getting the file size of \'" << p.path() << "\':\r\n" << e.what() << '\r\n';
		}
	}
	FolderSize = Size;
}

const bool LibraryFolder::operator==(const LibraryFolder & rhs) const { return Path() == rhs.Path(); }
const bool LibraryFolder::operator!=(const LibraryFolder & rhs) const { return Path() != rhs.Path(); }
const bool LibraryFolder::operator<(const LibraryFolder & rhs) const { return Size() < rhs.Size(); }
const bool LibraryFolder::operator<=(const LibraryFolder & rhs) const { return Size() <= rhs.Size(); }
const bool LibraryFolder::operator>(const LibraryFolder & rhs) const { return Size() > rhs.Size(); }
const bool LibraryFolder::operator>=(const LibraryFolder & rhs) const { return Size() >= rhs.Size(); }