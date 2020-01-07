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
#include <list>

namespace fs = std::filesystem;

using UMapPtr_str_app = std::unique_ptr<std::unordered_map<std::string, AppManifest>>;

class Library : public LibraryFolder
{
	public:
	Library(std::string Path); 
	Library(fs::directory_entry &);
	const bool ScanningRequired() const;
	void ScanFolders();
	const bool IsValidLibrary() const;
	static const bool IsValidLibrary(fs::directory_entry &);
	static const bool IsValidLibrary(std::string_view);
	static const fs::directory_entry LibraryFoldersVDF(const std::string_view &);
	void ListFolders() const;

	protected:
	fs::directory_entry steamAppsDir;
	fs::directory_entry commonDir;
	std::vector<std::shared_ptr<Game>> gameList;
	std::list<std::shared_ptr<Game>> foldersToManuallyScan;

	void BuildLibraryList();
	const UMapPtr_str_app AllManifests() const;
	
	private:

};