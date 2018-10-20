#pragma once
#include <iostream>
#include <string>
#include "Menu.h"
#include "Output.h"
#include "Library.h"

menu::menu(std::vector<library>* libs) : libraries(libs) { }

void menu::start()
{
    /**
     * Display all in libraries vector
     * Accept int (library number)
     * Call library_menu(selected library)
     **/ 

    output::print_sub_header("Libraries");
    
    int index = 1;    

    for (auto library : *libraries)
    {
        std::cout << output::create_menu_item(index, library.path()) << std::endl;
        index++;
    }    
    
    library_menu(*libraries[0].data());
}

void menu::library_menu(library selected_library)
{ 
    int index = 1;
    // output::print_sub_header(selected_library.path());
    output::print_sub_header("Library");
    std::cout << "Current Library:\t" << selected_library.path() << std::endl << std::endl;
    print_back(&index);    

    selected_library.print_all_apps(&index);

    int menu_selection = 4;
    if (menu_selection == 1)
    {
        start();
    }
    else
    {        
        app_menu(selected_library, selected_library.get_app(menu_selection));
    }
}

void menu::app_menu(library selected_library, app selected_app)
{
    std::filesystem::space_info drive = std::filesystem::space(selected_app.path);
    output::print_sub_header("Folder");

    std::cout << "Name:\t\t" << selected_app.path.path().filename().string() << "\nId:\t\t" << selected_app.id << "\nSize:\t\t" << std::fixed << std::setprecision(2) << selected_app.size << " GB" << std::endl;
    std::cout << std::endl << "Available\nSpace:\t\t" << drive.available / 1024 / 1024 / 1024 << " GB" << std::endl;

    // output::print_sub_header("Make a selection:");
    std::cout << std::endl << output::create_menu_item(1, "Back") << std::endl << std::endl;
    std::cout << output::create_menu_item(2, "Move") << std::endl;
}

void menu::print_back(int* index)
{
    std::cout << output::create_menu_item(*index, "Back") << std::endl << std::endl;
    (*index)++;
}