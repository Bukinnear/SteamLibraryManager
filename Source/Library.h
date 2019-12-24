#pragma once
#include "LibraryFolder.h"
#include "AppManifest.h"
#include "Game.h"

#include <iostream>
#include <filesystem>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <set>

struct Compare
{
	using is_transparent = void;

	bool operator()(const LibraryFolder & lhs, const LibraryFolder & rhs) const
	{
		return lhs.GetFolderPath() < rhs.GetFolderPath();
	}

	bool operator()(const LibraryFolder & lhs, const std::string & rhs)
	{
		return lhs.GetFolderPath() < rhs;
	}

	bool operator()(const std::string & lhs, const LibraryFolder & rhs)
	{
		return lhs < rhs.GetFolderPath();
	}    

	bool operator()(const LibraryFolder & lhs, const float & rhs)
	{
		return lhs.GetFolderSize() < rhs;
	}

	bool operator()(const float & lhs, const LibraryFolder & rhs)
	{
		return lhs < rhs.GetFolderSize();
	}
};

class Library : public LibraryFolder
{
	public:
	Library(std::string Path); 

	const bool ContainsFolder(std::string) const;

	protected:
	fs::directory_entry SteamAppsDir;
	fs::directory_entry CommonDir;
	std::vector<std::shared_ptr<Game>> GameList;

	const std::vector<std::shared_ptr<Game>> BuildLibraryList() const;
	const std::unique_ptr<std::unordered_map<std::string, AppManifest>> GetAllManifests() const;
	
	private:
};


	//Library(const char * Path);
	//const std::set<LibraryFolder, Compare> * const GetLibraryList() const;
	//std::set<LibraryFolder, Compare> FolderList;