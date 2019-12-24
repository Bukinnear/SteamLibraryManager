#include "Game.h"

Game::Game(fs::directory_entry SteamApps, AppManifest AppManifest) : SteamAppsDir(SteamApps), Manifest(AppManifest) 
{ 
    if (AppManifest.IsValid())
    {
        GameDir = fs::directory_entry(SteamAppsDir.path().string() + "\\common\\" + Manifest.installdir);

        if (GameDir.IsValidDirectory())
        {
            ShaderDir = SubFolderIDPath("\\shadercache");
            WorkshopDir = SubFolderIDPath("\\workshop");

            if (Manifest.IsValid())
            {
                ManifestPath = fs::directory_entry(SteamAppsDir.path().string() + "appmanifest_" + std::to_string(Manifest.appid) + ".acf");                

                std::string WkshopManifest(SteamAppsDir.path().string() + "\\workshop\\appworkshop_" + std::to_string(Manifest.appid) + ".acf");
                if (fs::exists(WkshopManifest))
                { WorkshopManifestPath = fs::directory_entry(WkshopManifest); }
            }
        }
    }
}

Game::Game(fs::directory_entry SteamApps, fs::directory_entry In_GameDir) : SteamAppsDir(SteamApps), GameDir(In_GameDir) 
{ 
    if (GameDir.IsValidDirectory())
    {
        std::cout << "Manually getting the folder size of \'" << GameDir.GetFolderPath() << "\'\r\n"; 
        GameDir.RefreshFolderSize();
        std::cout << "Done.\r\n\r\n";
    }
}

const std::string Game::GetName() const
{
    if (Manifest.IsValid()) 
    { return Manifest.name; }
    else 
    { return GameDir.GetFolderName(); }
    
}

const uint64_t Game::GetSize() const
{
    if (Manifest.IsValid())
    { return Manifest.SizeOnDisk; }
    else
    { 
        if (!PathsAreValid()) 
        { return 0; }
        else 
        { return GameDir.GetFolderSize(); }        
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

    if (WorkshopDir.GetFolderPath() != "" && !WorkshopDir.IsValidDirectory())
    {
        std::cout << "ALERT:\r\n" << GetName() << " Workshop folder \'" << WorkshopDir.GetFolderPath() << "\' is invalid.\r\n";
        ReturnVal = false;
    }

    if (ShaderDir.GetFolderPath() != "" && !ShaderDir.IsValidDirectory())
    {
        std::cout << "ALERT:\r\n" << GetName() << " Shaders folder \'" << ShaderDir.GetFolderPath() << "\' is invalid.\r\n";
        ReturnVal = false;
    }
    return ReturnVal;
}

const fs::directory_entry Game::SubFolderIDPath(std::string RelativePath) const
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