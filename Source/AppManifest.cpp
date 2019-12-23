#include "AppManifest.h"

const std::array<std::string, 7> AppManifest::ManifestFields = {"appid", "name", "StateFlags", "installdir", "SizeOnDisk", "BytesToDownload", "BytesDownloaded"};
const bool AppManifest::ContainsField(std::string s)
{
    for (auto a : ManifestFields)
    {
        if (a == s) { return true; }
    }
    return false;
}

const AppManifest AppManifest::ReadFromFile(std::string path)
{
    if (!std::filesystem::exists(path) || !std::filesystem::is_regular_file(path))
    {
        return AppManifest();
    }

    std::ifstream file(path);

    std::string FileInput;

    std::unordered_map<std::string, std::string> map;

    while (std::getline(file, FileInput))
    {
        if (FileInput[0] != '\t' || FileInput[0] == '}')
        {
            continue;
        }

        std::string key;
        std::string value;
        int offset = 2;
        int FirstEnd;

        if (offset >= FileInput.length()) { break; }

        key = FileInput.substr(offset, (FirstEnd = FileInput.find_first_of('\"', offset)) - offset);
        if (!AppManifest::ContainsField(key)) { continue; }

        offset = FirstEnd + 4;
        if (offset >= FileInput.length()) { break; }

        value = FileInput.substr(offset, FileInput.find_first_of('\"', offset) - offset);

        map.insert({key, value});
    }

    try
    {
        int a;

        int appid = std::stoi(map.at("appid"));
        std::string name = map.at("name");
        int stateflags = std::stoi(map.at("StateFlags"));
        std::string installdir = map.at("installdir");
        uint64_t sizeondisk = std::stoull(map.at("SizeOnDisk"));
        uint64_t bytestodownload = std::stoull(map.at("BytesToDownload"));
        uint64_t bytesdownloaded = std::stoull(map.at("BytesDownloaded"));

        return AppManifest(appid, name, stateflags, installdir, sizeondisk, bytestodownload, bytestodownload);
    }    
    catch(const std::exception& e) { std::cerr << "\r\nERROR:\r\nCould not create an AppManifest for: " << path << "\r\nError Details:\r\n" << e.what() << '\r\n'; };     

    return AppManifest();
}

const bool AppManifest::IsValid() const 
{ 
    return appid != 0 && name != ""; 
}