#pragma once
#include "Main.h"
#include <string>
#include <iostream>
#include "Test.h"

using namespace std;

/*
cl /EHsc Main.cpp Test.cpp  /nologo /std:c++latest
cd C:\Code\SteamLibraryManager
*/

int main(int argc, char const *argv[])
{
    string Input;
    cout << "Please provide an input:";
    cin >> Input;

    Test *test = new Test(Input);    
    cout << "Your input is: " << test->getInput();
}