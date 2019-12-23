#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <filesystem>
#include <array>

struct AppManifest
{
public:
    const int appid;
    const std::string name;
    const int StateFlags;
    const std::string installdir;
    const uintmax_t SizeOnDisk;
    const uintmax_t BytesToDownload;
    const uintmax_t BytesDownloaded;

    AppManifest(
    int Inp_appid,
    std::string Inp_name,
    int Inp_StateFlags,
    std::string Inp_installdir,
    uintmax_t Inp_SizeOnDisk,
    uintmax_t Inp_BytesToDownload,
    uintmax_t Inp_BytesDownloaded) : 
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

    static const AppManifest Read(std::string);
    static const bool ContainsField(std::string);

private:
    static const std::array<std::string, 7> ManifestFields;
};

class ManifestReader
{
public:
};