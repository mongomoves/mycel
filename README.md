# mycel

First C++ project, mainly for practice.

Command line tool that enables the user to create a named "link" between one folder and one application. 
The user can then call the program with the named link as an argument and see the contents of the folder and a file with the linked application.

Arguments for the program:
Help: -h or --help
Delete link: -d / --delete <name>/-A (-A for all)
New link: -n / --new <name> <app> <folder>
List links: -ls / --list
Run link: <name>

<app> and <folder> should be full paths to whatever.

Executable should be placed in folder where it can write and read from .ini file, since this is the way it stores links.

