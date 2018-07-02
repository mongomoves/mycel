#pragma once
#ifndef RUN_LINK_H
#define RUN_LINK_H

#include "Link.h"
#include "UStrConverter.h"
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
#include <Windows.h>

void iterate_directory(std::vector<std::experimental::filesystem::path> &filepaths, const std::string &folder);
void print_files(std::vector<std::experimental::filesystem::path> &files, std::string &path);
void run_file(std::experimental::filesystem::path &file, std::string &app);
int get_input_index();

#endif