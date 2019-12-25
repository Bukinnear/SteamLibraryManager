#pragma once
#include "LibraryFolder.h"

LibraryFolder::LibraryFolder(std::string Path) : RootDirectory(Path) {}

LibraryFolder::LibraryFolder(fs::directory_entry Directory) : RootDirectory(Directory) {}

LibraryFolder::LibraryFolder() {}

const bool LibraryFolder::IsValidDirectory() const
{
	return (fs::exists(RootDirectory) && fs::is_directory(RootDirectory));
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

const void LibraryFolder::RefreshFolderSize()
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