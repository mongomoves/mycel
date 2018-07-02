#include "stdafx.h"
#include "UStrConverter.h"

std::wstring widen_str(std::string str)
{
	int required = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	if (required == 0)
	{
		return std::wstring();
	}
	std::wstring wstr;
	wstr.resize(required);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], wstr.capacity());
	return wstr;
}

std::string shorten_wstr(std::wstring wstr)
{
	int required = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
	if (required == 0)
	{
		return std::string();
	}
	std::string str;
	str.resize(required);
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], required, NULL, NULL);
	return str;
}