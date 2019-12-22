#include "ManifestReader.h"


const std::unique_ptr<std::unordered_map<std::string, std::string>> ManifestReader::Read(std::string path)
{
    if (!std::filesystem::exists(path) || !std::filesystem::is_regular_file(path)) { return nullptr; }

    std::ifstream file(path);
 
    std::string buffer;   
    std::string key;
    std::string value;

    std::unique_ptr<std::unordered_map<std::string, std::string>> map(new std::unordered_map<std::string, std::string>);

    while (std::getline(file, buffer))
    {
        if (buffer[0] != '\t' || buffer[0] == '}') { continue; }

        int offset = 2;
        int FirstEnd;
        if (offset >= buffer.length()) { break; }

        std::string key = buffer.substr(offset, (FirstEnd = buffer.find_first_of('\"', offset)) - offset);

        offset = FirstEnd + 4;
        if (offset >= buffer.length()) { break; }

        value = buffer.substr(offset, buffer.find_first_of('\"', offset) - offset);

        map->insert({key, value});
    }    
    return map;
}