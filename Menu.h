#pragma once
#include <Vector>
#include "Library.h"

class menu
{
    private:
    std::vector<library>* libraries;
    void library_menu(library selected_library);
    void app_menu(library selected_library, app selected_app);
    void print_back(int* index);

    public:
    menu(std::vector<library>* libs);
    void start();
};