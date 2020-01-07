#pragma once
#include "Library.h"

Library::Library(std::string Path) : LibraryFolder(Path)
{
	steamAppsDir = fs::directory_entry(Path + "\\steamapps");
	commonDir = fs::directory_entry(Path + "\\steamapps\\Common");

	if (IsValidLibrary())
	{ BuildLibraryList(); }
	else
	{ std::cout << "\r\nERROR:\r\nLibrary at path \'" << RootDirectory.path().string() << "\' is not a valid library. Could not locat steamapps\\common.\r\n"; }
}

Library::Library(fs::directory_entry &Path) : LibraryFolder(Path)
{
	steamAppsDir = fs::directory_entry(Path.path().string() + "\\steamapps");
	commonDir = fs::directory_entry(steamAppsDir.path().string() + "\\Common");

	if (IsValidLibrary())
	{
		BuildLibraryList();
	}
	else
	{
		std::cout << "\r\nERROR:\r\nLibrary at path \'" << RootDirectory.path().string() << "\' is not a valid library. Could not locate steamapps\\common.\r\n";
	}
}

const bool Library::ScanningRequired() const
{
	return !foldersToManuallyScan.empty();
}

void Library::ScanFolders()
{
	for (auto folder : foldersToManuallyScan)
	{
		std::cout << "Scanning: " << folder->FolderName() << " ... ";
		folder->RefreshSize();
		std::cout << "Done\n";
	}
}

const bool Library::IsValidLibrary() const
{
	return commonDir.exists() && commonDir.is_directory();
}

const bool Library::IsValidLibrary(fs::directory_entry &inFolder)
{
	std::string inCommonPath = inFolder.path().string() + "\\steamapps\\common";
	fs::directory_entry inCommonDir(inCommonPath);
	return inCommonDir.exists() && inCommonDir.is_directory();
}

const bool Library::IsValidLibrary(std::string_view inFolder)
{
	std::string inCommonPath = inFolder.data();
	inCommonPath += +"\\steamapps\\common";
	fs::directory_entry inCommonDir(inCommonPath);
	return inCommonDir.exists() && inCommonDir.is_directory();
}

const fs::directory_entry Library::LibraryFoldersVDF(const std::string_view &in_SteamDirectory)
{
	fs::directory_entry returnVal;
	
	if (fs::directory_entry(in_SteamDirectory).exists())
	{
		std::string vdfPath(in_SteamDirectory.data());
		vdfPath += "\\steamapps\\libraryfolders.vdf";

		returnVal = fs::directory_entry(vdfPath);
	}
	return returnVal;
}

void Library::ListFolders() const
{
	std::cout << "\nOutputting folders for " << Path() << "\n----------\n";
	for (auto a : gameList)
	{
		std::cout << a->Name() << "\t\t\t\tSize: " << a->Size()/1024/1024/1024 << "GB\n";
	}
}

void Library::BuildLibraryList()
{
	gameList.clear();
	foldersToManuallyScan.clear();

	if (!IsValidLibrary()) { return; }

	UMapPtr_str_app manifestList = AllManifests();

	for (auto gameFolder : fs::directory_iterator(commonDir))
	{
		auto findResult = manifestList->find(gameFolder.path().filename().string());
		if (findResult != manifestList->end())
		{
			AppManifest manifest = findResult->second;
			if (manifest.IsValid())
			{
				std::shared_ptr<Game> newGame = std::make_shared<Game>(steamAppsDir, manifest);
				gameList.push_back(newGame);
			}
		}
		else
		{ 
			std::shared_ptr<Game> newGame = std::make_shared<Game>(steamAppsDir, gameFolder);
			gameList.push_back(newGame);
			foldersToManuallyScan.push_back(newGame);
		}
	}
}

const UMapPtr_str_app Library::AllManifests() const
{
	UMapPtr_str_app returnMap(new std::unordered_map<std::string, AppManifest>);

	for (auto filepath : fs::directory_iterator(steamAppsDir))
	{
		auto filename = filepath.path().filename().string();

		auto isAppManifest = filename.find("appmanifest_");
		auto notCorrect = filename.npos;

		if (!fs::is_regular_file(filepath) || isAppManifest == notCorrect) { continue; }

		AppManifest manifest = AppManifest::ReadFromFile(filepath.path().string());
		if (manifest.IsValid()) 
		{ 
			returnMap->insert({manifest.installdir, manifest});
		}
	}
	return returnMap;
}
