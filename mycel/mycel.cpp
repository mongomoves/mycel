// mycel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mycel.h"

using std::string;
namespace filesystem = std::experimental::filesystem;

//Sets the passed string as the path to User/AppData/Local
void get_save_folder(string &saveFolder)
{
	PWSTR path = NULL;
	HRESULT hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &path);
	if (SUCCEEDED(hr))
	{
		saveFolder = shorten_wstr(path);
	}
	CoTaskMemFree(path);
}

void print_help()
{
	std::cout << std::endl
		<< "======= Mycel v.1.0 =======" << std::endl << std::endl
		<< "Run link: <name>" << std::endl
		<< "Delete link (-A for all): -d / --delete <name>/-A" << std::endl
		<< "New link: -n / --new <name> <app> <folder>" << std::endl
		<< "List links: -ls / --list" << std::endl << std::endl
		<< "===========================" << std::endl << std::endl;
}

//Checks if passed linkName exists, if so places it on pointer, returns true.
bool get_link(std::vector<link> &links, std::string linkName, link &paths)
{
	for (auto it = links.begin(); it != links.end(); ++it)
	{
		if ((*it).name == linkName)
		{
			paths = *it;
			return true;
		}
	}
	return false;
}

//For the -list command, prints all the links the user has created.
void print_links(std::vector<link> &links)
{
	std::cout << "------" << std::endl;
	for (auto it = links.begin(); it != links.end(); ++it)
	{
		std::cout << (*it).name << std::endl;
		std::cout << "App: " << (*it).app << std::endl;
		std::cout << "Folder: " << (*it).folder << std::endl;
		std::cout << "------" << std::endl;
	}
}

int main(int argc, char *argv[])
{
	const string ini_filename("links.ini");
	string iniFilePath;
	std::vector<link> links;
	std::vector<filesystem::path> filepaths;
	link paths;

	get_save_folder(iniFilePath);
	iniFilePath += "\\Mycel\\";

	//If ini file or folder not created, create them.
	if (!filesystem::exists(iniFilePath + ini_filename))
	{		
		if (!filesystem::exists(iniFilePath))
		{
			filesystem::create_directory(iniFilePath);
		}
		std::ofstream of(iniFilePath + ini_filename);
		of.close();
	} 
	links = get_links(iniFilePath + ini_filename);
	
	//Prints version when no arguments are added, just to do something.
	if (argc == 1) 
	{
		print_help();
		return 0;
	}

	for (int i = 1; i < argc; ++i) 
	{
		string arg = argv[i];
		if ((arg == "-ls") || (arg == "--list")) 
		{
			print_links(links);
			return 0;
		} 
		else if (((arg == "-d") || (arg == "--delete")) && argc == 3) 
		{
			if (delete_link(iniFilePath + ini_filename, argv[2]))
			{
				std::cout << "Successful deletion";
				return 0;
			}
			std::cout << "Unsuccessful deletion";
			return 0;
		} 
		else if ((arg == "-n") || (arg == "--new") && argc == 5)
		{
			if (!get_link(links, argv[2], paths))
			{
				if (create_link(iniFilePath + ini_filename, argv[2], argv[3], argv[4]))
				{
					std::cout << "New link " << argv[2] << " created" << std::endl;
					return 0;
				}
				else
				{
					std::cout << "Failed to create new link " << argv[2] << std::endl;
					return 0;
				}
			}
			else
			{
				std::cout << "Link " << argv[2] << " already exists" << std::endl;
				return 0;
			}
		} 
		else 
		{
			//Argument is a supposed link
			if (argc == 2) 
			{
				int chosenIndex;
				if (get_link(links, argv[1], paths))
				{
					iterate_directory(filepaths, paths.folder);
					print_files(filepaths, paths.folder);
					chosenIndex = get_input_index();
					if (chosenIndex == 0)
					{
						return 0;
					}
					//As long as the user is selecting a folder
					while (filesystem::is_directory(filepaths.at(chosenIndex - 1)))
					{
						iterate_directory(filepaths, filepaths.at(chosenIndex - 1).string());
						print_files(filepaths, paths.folder);
						chosenIndex = get_input_index();
						if (chosenIndex == 0)
						{
							return 0;
						}
					}
					run_file(filepaths.at(chosenIndex - 1), paths.app);
				}
				else 
				{
					std::cout << "No such link" << std::endl;
				}
			}
			else
			{
				std::cout << "Incorrect input? Enter --help" << std::endl;
				return 0;
			}
		}
	}
    return 0;
}

