#pragma once
#include <iostream>
#include "Output.h"

void output::print_header()
{
    std::cout << std::endl << "-------------------------------------------\n-                                         -\n-          Steam Library Manager          -\n-                                         -\n-------------------------------------------" << std::endl;
}

void output::print_sub_header(std::string sub_header)
{
    std::cout << std::endl << "-------------------------------------------\n"<< " " << sub_header << "\n-------------------------------------------" << std::endl << std::endl;
}

std::string output::create_menu_item(int index, std::string menu_item)
{   
    return " " + std::to_string(index) + ".\t" + menu_item;
}