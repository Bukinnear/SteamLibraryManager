#pragma once
#include <filesystem>
#include "library.h"

bool save_settings();
bool load_settings();
void run_setup();

std::vector<library> libraries;