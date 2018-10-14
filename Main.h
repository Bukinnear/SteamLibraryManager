#pragma once
#include <filesystem>
#include "library.h"

void print_header();
bool save_settings();
bool load_settings();
void run_setup();

std::vector<library> libraries;