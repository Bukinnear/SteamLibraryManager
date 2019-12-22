#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <filesystem>
#include <memory>


class ManifestReader
{
public:
    static const std::unique_ptr<std::unordered_map<std::string, std::string>> Read(std::string);
};