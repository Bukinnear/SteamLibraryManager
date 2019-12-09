#pragma once
#include "Test.h"
#include <string>
#include <iostream>

using namespace std;

Test::Test(string Input)
{
    InputVar = Input;
}

string Test::getInput() 
{ 
    return InputVar; 
}
