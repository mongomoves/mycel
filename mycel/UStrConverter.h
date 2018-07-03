#pragma once
#ifndef H_USTRCONV
#define H_USTRCONV

#include <string>
#include <Windows.h>

std::string shorten_wstr(std::wstring wstr);
std::wstring widen_str(std::string str);

#endif