#pragma once
#include "LibraryFolder.h"
#include "AppManifest.h"

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class Game
{
	public:
	Game(const fs::directory_entry &SteamApps, const AppManifest &AppManifest);
	Game(const fs::directory_entry &SteamApps, const fs::directory_entry &In_GameDir);

	const int AppID() const;
	const std::string Path() const;
	const std::string Name() const;
	const std::string FolderName() const;
	const uint64_t Size() const;
	const bool CanMove() const;
	void RefreshSize();

	bool operator==(const Game &) const;
	bool operator!=(const Game &) const;
	bool operator<(const Game &) const;
	bool operator<=(const Game &) const;
	bool operator>(const Game &) const;
	bool operator>=(const Game &) const;

	private:
	fs::directory_entry SteamAppsDir;
	LibraryFolder GameDir;
	LibraryFolder ShaderDir;
	LibraryFolder WorkshopDir;
	fs::directory_entry WorkshopManifestPath;
	fs::directory_entry ManifestPath;
	AppManifest Manifest;

	const bool PathsAreValid() const;
	const fs::directory_entry IDSubFolderPath(std::string RelativePath) const;

};