#pragma once
#ifndef INI_RW_H
#define INI_RW_H

#include "Link.h"
#include <string>
#include <fstream>
#include <vector>

const std::string iniApp = "app=";
const std::string iniFolder = "folder=";

std::vector<link> get_links(const std::string &file);
bool create_link(const std::string &file, std::string link, std::string app, std::string folder);
bool delete_link(const std::string &file, std::string link);

#endif