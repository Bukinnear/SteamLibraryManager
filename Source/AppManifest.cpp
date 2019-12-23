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

const AppManifest AppManifest::Read(std::string path)
{
    if (!std::filesystem::exists(path) || !std::filesystem::is_regular_file(path))
    {
        return AppManifest();
    }

    std::ifstream file(path);

    std::string buffer;

    std::unordered_map<std::string, std::string> map;

    while (std::getline(file, buffer))
    {
        if (buffer[0] != '\t' || buffer[0] == '}')
        {
            continue;
        }

        std::string key;
        std::string value;
        int offset = 2;
        int FirstEnd;
        if (offset >= buffer.length()) { break; }

        std::string key = buffer.substr(offset, (FirstEnd = buffer.find_first_of('\"', offset)) - offset);
        if (!AppManifest::ContainsField(key)) { continue; }

        offset = FirstEnd + 4;
        if (offset >= buffer.length()) { break; }

        value = buffer.substr(offset, buffer.find_first_of('\"', offset) - offset);

        map.insert({key, value});
    }

    try
    {
        int appid = std::stoi(map.at("appid"));
        std::string name = map.at("name");
        int stateflags = std::stoi(map.at("StateFlags"));
        std::string installdir = map.at("installdir");
        uintmax_t sizeondisk = std::stoi(map.at("SizeOnDisk"));
        uintmax_t bytestodownload = std::stoi(map.at("BytesToDownload"));
        uintmax_t bytesdownloaded = std::stoi(map.at("BytesDownloaded"));

        return AppManifest(appid, name, stateflags, installdir, sizeondisk, bytestodownload, bytestodownload);
    }    
    catch(const std::exception& e) { std::cerr << e.what() << '\n'; };     

    return AppManifest();
}