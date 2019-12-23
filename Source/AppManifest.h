#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <filesystem>
#include <array>
#include <cinttypes>

struct AppManifest
{
    public:
    const int appid;
    const std::string name;
    const int StateFlags;
    const std::string installdir;
    const uint64_t SizeOnDisk;
    const uint64_t BytesToDownload;
    const uint64_t BytesDownloaded;

    AppManifest(
        int Inp_appid,
        std::string Inp_name,
        int Inp_StateFlags,
        std::string Inp_installdir,
        uint64_t Inp_SizeOnDisk,
        uint64_t Inp_BytesToDownload,
        uint64_t Inp_BytesDownloaded) : 
            appid(Inp_appid),
            name(Inp_name),
            StateFlags(Inp_StateFlags),
            installdir(Inp_installdir),
            SizeOnDisk(Inp_SizeOnDisk),
            BytesToDownload(Inp_BytesToDownload),
            BytesDownloaded(Inp_BytesDownloaded)
    { };

    AppManifest() : 
        appid(0),
        name(""),
        StateFlags(0),
        installdir(""),
        SizeOnDisk(0),
        BytesToDownload(0),
        BytesDownloaded(0)
    { };

    static const AppManifest ReadFromFile(std::string);
    static const bool ContainsField(std::string);
    const bool IsValid() const;

    private:
    static const std::array<std::string, 7> ManifestFields;
};