#include "stdafx.h"
#include "iniRW.h"

using std::string;

//Gathers all the information from the ini file in Link objects.
std::vector<link> get_links(const string &file)
{
	std::ifstream ini(file);
	std::vector<link> links;
	std::string line;
	if (ini.is_open())
	{
		link newlink;
		while (getline(ini, line))
		{
			if (line[0] == '[')
			{
				newlink.name = string(line, 1, line.length() - 2);
				getline(ini, line);
				newlink.app = string(line, 4, line.length());
				getline(ini, line);
				newlink.folder = string(line, 7, line.length());
			}
			links.push_back(newlink);
		}
	}
	return links;
}

//Adds new link to the file, with the arguments passed by the user.
bool create_link(const string &file, string link, string app, string folder)
{
	std::ofstream ini(file, std::ofstream::app);
	if (ini.is_open())
	{
		ini << "[" + link + "]\n";
		ini << iniApp + app + "\n";
		ini << iniFolder + folder + "\n";
		ini.close();
		return true;
	}
	return false;
}

//Deletes one named link, or all links from the file.
bool delete_link(const string &file, string link)
{
	if (link == "-A")
	{
		if (remove(file.c_str()) == 0) 
		{
			std::ofstream f(file);
			return true;
		}
		return false;
	}
	string line, fileCopy = file + "Temp";
	std::ofstream iniCopy(fileCopy);
	std::ifstream ini(file);
	if (ini.is_open() && iniCopy.is_open())
	{
		while (std::getline(ini, line))
		{
			if (!(string(line, 1, line.length() - 2) == link))
			{
				iniCopy << line + "\n";
			}
			else
			{
				std::getline(ini, line);
				std::getline(ini, line);
			}
		}
		iniCopy.close();
		ini.close();
		remove(file.c_str());
		rename(fileCopy.c_str(), file.c_str());
		return true;
	}
	return false;
}