#pragma once
#include <System/Kernel/Kernel.h>
#include <System/UserManager/UserManager.h>
#include <System/Terminal/dirent.h>

#include <iostream>
#include <algorithm>
#include <ctype.h>
#include <vector>
#include <string>
#include <functional>
#include <io.h>

class FishTerminal
{
public:
	FishTerminal(Kernel* _kernel, UserManager* _userManager);

	int Start();

	std::string HelpPages[1];

private:
	Kernel* kernel;
	UserManager* userManager;

	void getFolders(std::string path, std::vector<std::string>& fileVec); 
	void getFiles(std::string path, std::vector<std::string>& fileVec);

    std::string& lTrim(std::string& ss);
    std::string& rTrim(std::string& ss);
	std::string& trim(std::string& st);
	std::string getFileName(std::string path);

};

