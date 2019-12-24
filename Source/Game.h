#pragma once
#include "LibraryFolder.h"
#include "AppManifest.h"

#include <filesystem>
#include <string>

namespace fs = std::experimental::filesystem;

class Game
{
	public:
	Game(fs::directory_entry SteamApps, AppManifest AppManifest);
	Game(fs::directory_entry SteamApps, fs::directory_entry In_GameDir);

	const std::string GetName() const;
	const uint64_t GetSize() const;
	const bool CanMove() const;

	private:
	fs::directory_entry SteamAppsDir;
	LibraryFolder GameDir;
	LibraryFolder ShaderDir;
	LibraryFolder WorkshopDir;
	fs::directory_entry WorkshopManifestPath;
	fs::directory_entry ManifestPath;
	AppManifest Manifest;

	const bool PathsAreValid() const;
	const fs::directory_entry SubFolderIDPath(std::string RelativePath) const;

};