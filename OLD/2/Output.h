#pragma once
#include <string>

namespace output
{
    void print_header();
    void print_sub_header(std::string sub_header);
    std::string create_menu_item(int index, std::string menu_item);
};