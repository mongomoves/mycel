#pragma once

#ifndef MYCEL_H
#define MYCEL_H

#include "iniRW.h"
#include "Link.h"
#include "RunLink.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <KnownFolders.h>
#include <shlobj.h>
#include <string>
#include <vector>
#include <windows.h>

bool get_link(std::vector<link> &links, std::string linkName, link &paths);
void get_save_folder(std::string &saveFolder);
void print_help();
void print_links(std::vector<link> &links);

#endif
