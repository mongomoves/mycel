#include "stdafx.h"
#include "RunLink.h"

namespace filesystem = std::experimental::filesystem;

//ShellExecute the chosen file. App is either default or some other path depending on the link.
void run_file(filesystem::path &file, std::string &app)
{
	if (app == "default")
	{
		if (((int)ShellExecuteW(NULL, L"open", widen_str(file.string()).c_str(), NULL, NULL, SW_NORMAL)) <= 32)
		{
			printf("Error: (%d) \n", GetLastError());
		}
	}
	else
	{
		if ((int)ShellExecuteW(NULL, L"open", widen_str(app).c_str(), widen_str(file.string()).c_str(), NULL, SW_NORMAL) <= 32)
		{
			printf("Error: (%d) \n", GetLastError());
		}
	}
}

//Iterates whatever directory is passed with folder param, adds all paths to vector.
void iterate_directory(std::vector<filesystem::path> &filepaths, const std::string &folder)
{
	for (auto &p : filesystem::directory_iterator(folder))
	{
		filepaths.push_back(p.path());
	}
}

//Prints all paths in passed vectors, but without the original folder path the user entered, for style.
void print_files(std::vector<filesystem::path> &files, std::string &path)
{
	for (auto it = files.begin(); it != files.end(); ++it)
	{
		std::cout << (it - files.begin()) + 1 << ": " << std::string((*it).string(), path.length(), ((*it).string().length()) - 1) << std::endl;
	}
}

//Just returns an int, supposed to be what file or folder the user wants to open.
int get_input_index()
{
	int i;
	std::cout << "Choose file or folder to open (0 to exit): ";
	std::cin >> i;
	return i;
}