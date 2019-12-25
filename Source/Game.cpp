#include "Game.h"

Game::Game(fs::directory_entry SteamApps, AppManifest AppManifest) : SteamAppsDir(SteamApps), Manifest(AppManifest) 
{ 
	if (AppManifest.IsValid())
	{
		GameDir = fs::directory_entry(SteamAppsDir.path().string() + "\\common\\" + Manifest.installdir);

		if (GameDir.IsValidDirectory())
		{
			ShaderDir = IDSubFolderPath("\\shadercache");
			WorkshopDir = IDSubFolderPath("\\workshop");

			if (Manifest.IsValid())
			{
				try
				{
					ManifestPath = fs::directory_entry(SteamAppsDir.path().string() + "\\appmanifest_" + std::to_string(Manifest.appid) + ".acf");
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << '\n';
				}

				std::string WkshopManifest(SteamAppsDir.path().string() + "\\workshop\\appworkshop_" + std::to_string(Manifest.appid) + ".acf");
				
				if (fs::exists(WkshopManifest))
				{ 
					WorkshopManifestPath = fs::directory_entry(WkshopManifest); 
				}
			}
		}
	}
}

Game::Game(fs::directory_entry SteamApps, fs::directory_entry In_GameDir) : SteamAppsDir(SteamApps), GameDir(In_GameDir) 
{ 
	if (GameDir.IsValidDirectory())
	{
		std::cout << "- Manually getting the folder size of \'" << GameDir.Path() << "\'\r\n"; 
		GameDir.RefreshFolderSize();
		std::cout << "- Done.\r\n";
	}
}

const std::string Game::Path() const 
{ 
	return GameDir.Path(); 
}

const std::string Game::Name() const
{
	if (Manifest.IsValid()) 
	{ return Manifest.name; }
	else 
	{ return GameDir.Name(); }
	
}

const uint64_t Game::Size() const
{
	if (Manifest.IsValid())
	{ return Manifest.SizeOnDisk; }
	else
	{ 
		if (!PathsAreValid()) 
		{ return 0; }
		else 
		{ return GameDir.Size(); }        
	}    
}

const bool Game::CanMove() const 
{ 
	return Manifest.IsValid() && PathsAreValid(); 
}

const bool Game::PathsAreValid() const
{
	bool ReturnVal = GameDir.IsValidDirectory();
	if (!ReturnVal) { return ReturnVal; }

	if (WorkshopDir.Path() != "" && !WorkshopDir.IsValidDirectory())
	{
		std::cout << "ALERT:\r\n" << Name() << " Workshop folder \'" << WorkshopDir.Path() << "\' is invalid.\r\n";
		ReturnVal = false;
	}

	if (ShaderDir.Path() != "" && !ShaderDir.IsValidDirectory())
	{
		std::cout << "ALERT:\r\n" << Name() << " Shaders folder \'" << ShaderDir.Path() << "\' is invalid.\r\n";
		ReturnVal = false;
	}
	return ReturnVal;
}

const fs::directory_entry Game::IDSubFolderPath(std::string RelativePath) const
{
	if (RelativePath.empty()) 
	{ return fs::directory_entry(); }

	if (RelativePath[0] != '\\')
	{ RelativePath.insert(0, 1, '\\'); }

	if (RelativePath.back() != '\\')
	{ RelativePath.push_back('\\'); }

	if (Manifest.IsValid()) 
	{ 
		std::string path = SteamAppsDir.path().string() + RelativePath + "\\" + std::to_string(Manifest.appid);
		
		if (fs::exists(path) && fs::is_directory(path))
		{
			return fs::directory_entry(path);
		}
	}
	return fs::directory_entry();
}

bool Game::operator==(const Game & rhs) const { return Path() == rhs.Path(); }
bool Game::operator!=(const Game & rhs) const { return Path() != rhs.Path();}

bool Game::operator<(const Game & rhs) const { return Size() < rhs.Size(); }
bool Game::operator<=(const Game & rhs) const { return Size() <= rhs.Size(); }
bool Game::operator>(const Game & rhs) const { return Size() > rhs.Size(); }
bool Game::operator>=(const Game & rhs) const { return Size() >= rhs.Size(); }