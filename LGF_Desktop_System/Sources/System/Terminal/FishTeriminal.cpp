#include <System/Terminal/FishTerminal.h>
#include <System/LegacyGUI/LegacyGUI.h>

FishTerminal::FishTerminal(Kernel* _kernel, UserManager* _userManager)
{
	kernel = _kernel;
	userManager = _userManager;

	HelpPages[0] = { 
		"Page: 1 of 1\n"
		"-------	-------		-------		-------		-------		-------		-------\n"
		"[Commands]				[Comments]					[Usage]\n"
		"|cd					|Show/Change Dir				|cd [path]\n" 
		"|clear					|Clear Terminal					|clear\n" 
		"|cat					|Display File					|cat [FILE]\n" 
		"|exit					|Exit Terminal					|exit ([exit code])\n" 
		"|help					|Show Help Page					|help ([page])\n" 
		"|ls					|List All Files And Folders			|ls\n" 
		"|GUI					|Init GUI					|GUI\n" 
		"|register				|Register					|register\n"
		"|reboot					|Reboot System					|reboot\n"
		"|su					|Switch User					|su ([user name])\n" 
		"|shutdown				|Shutdown System				|shutdown\n" 
		"-------	-------		-------		-------		-------		-------		-------\n"
	};
}

int FishTerminal::Start()
{
	//Init
	kernel->SetColor();
	kernel->PrintFullScreen();
	kernel->SetBGColor(5);
	kernel->GotoXY(0, 0);
	kernel->PrintCenter("FishTeriminal 1.0.0.0");
	kernel->NewLine();
	kernel->SetBGColor();
	kernel->Print("User "); kernel->SetFColor(5); kernel->Print(userManager->CurrentUsername.c_str()); kernel->SetFColor(); kernel->PrintLine(" login");
	kernel->Print("Type \"help\" to get help.\n\n");

	//Command Vars
	std::string FullCurrentCommandLine = "";
	std::string TFullCurrentCommandLine = "";
	std::string CurrentCommandLine = "";
	std::string CurrentCommandLineLowwer = "";
	std::string CurrentCommandLineArgv = "";
	int CommandFound = 0;

	//Loop
	while (true) {
		//Define
		CommandFound = 0;

		//Print
		kernel->Print("TerminalRunner << ");

		//Get Cmd
		FullCurrentCommandLine = kernel->GetLine();
		TFullCurrentCommandLine = trim(FullCurrentCommandLine);
		CurrentCommandLine = TFullCurrentCommandLine.substr(0, TFullCurrentCommandLine.find_first_of(' '));
		CurrentCommandLineLowwer = CurrentCommandLine;
		transform(CurrentCommandLineLowwer.begin(), CurrentCommandLineLowwer.end(), CurrentCommandLineLowwer.begin(), ::tolower);
		if (strstr(TFullCurrentCommandLine.c_str(), " ") == NULL)//在a中查找b，不存在
			CurrentCommandLineArgv = "";
		else
		{
			CurrentCommandLineArgv = TFullCurrentCommandLine.substr(TFullCurrentCommandLine.find_first_of(' ') + 1);
			CurrentCommandLineArgv = trim(CurrentCommandLineArgv);
		}

		/*std::cout << "FullCurrentCommandLine\"" << FullCurrentCommandLine << "\"" << std::endl;
		std::cout << "CurrentCommandLine\"" << CurrentCommandLine << "\"" << std::endl;
		std::cout << "CurrentCommandLineLowwer\"" << CurrentCommandLineLowwer << "\"" << std::endl;
		std::cout << "CurrentCommandLineArgv\"" << CurrentCommandLineArgv << "\"" << std::endl;*/

		//Cmd Switch
		if (TFullCurrentCommandLine == "")//NULL
			continue;
		if (CurrentCommandLineLowwer == "cd") {
			if (CurrentCommandLineArgv != "")
			{
				if (kernel->SetCurrentDir(CurrentCommandLineArgv.c_str()))
				{
					kernel->Print(std::string("Path: \"" + std::string(kernel->GetCurrentDir()) +  "\"" + CurrentCommandLineArgv + "not exist\n").c_str());
				}
				else
				{
					kernel->Print("cd -- ");
					kernel->PrintLine(CurrentCommandLineArgv.c_str());
				}
			}
			else
			{
				kernel->Print("Current Dir Path: ");
				kernel->PrintLine(kernel->GetCurrentDir());
			}
			CommandFound++;
		}
		if (CurrentCommandLineLowwer == "clear") {
			kernel->Clear();
			CommandFound++;
		}
		if (CurrentCommandLineLowwer == "cat") {
			if (CurrentCommandLineArgv != "")
			{
				kernel->PrintCenter(CurrentCommandLineArgv.c_str());
				kernel->NewLine();
				kernel->Separator();
				kernel->Print(userManager->ReadFileToString(CurrentCommandLineArgv).c_str());
				kernel->NewLine();
			}
			else
			{
				kernel->PrintLine("Usage: cat [FILE]");
			}
			CommandFound++;
		}
		if (CurrentCommandLineLowwer == "exit") {
			kernel->PrintLine(std::string("User: " + userManager->CurrentUsername + " logout").c_str());
			if (CurrentCommandLineArgv != "")
				//exit(stoi(CurrentCommandLineArgv));
				return stoi(CurrentCommandLineArgv);
			else
				//exit(0);
				return 0;
			CommandFound++;
		}
		if (CurrentCommandLineLowwer == "help") {
			if (CurrentCommandLineArgv != "") {
				int page = stoi(CurrentCommandLineArgv);
				page--;
				if (page < 0)
					page = 0;
				kernel->Print(HelpPages[page].c_str());
			}
			else
				kernel->Print(HelpPages[0].c_str());
			CommandFound++;
		}
		if (CurrentCommandLineLowwer == "ls") {
			std::vector<std::string> FolderList;
			getFolders(kernel->GetCurrentDir(), FolderList);
			for (unsigned int i = 0; i < FolderList.size(); i++) {
				if (!strstr(FolderList[i].c_str(), " ") == NULL)
					FolderList[i] = "\"" + FolderList[i] + "\"";
				kernel->SetBGColor(3);
				kernel->Print(FolderList[i].c_str());
				kernel->SetBGColor();
				kernel->Print(" ");
			}
			kernel->NewLine();
			std::vector<std::string> FileList;
			getFiles(kernel->GetCurrentDir(), FileList);
			for (unsigned int i = 0; i < FileList.size(); i++) {
				if (!strstr(FileList[i].c_str(), " ") == NULL)
					FileList[i] = "\"" + FileList[i] + "\"";
				kernel->SetFColor(2);
				kernel->Print(FileList[i].c_str());
				kernel->SetFColor();
				kernel->Print(" ");
			}
			kernel->NewLine();
			CommandFound++;
		}
		if (CurrentCommandLine == "GUI") {
			static LegacyGUI legacyGUI(kernel, userManager);
			legacyGUI.Terminal_GUI();
			CommandFound++;
		}
		if (CurrentCommandLineLowwer == "register") {
			userManager->Register();
			CommandFound++;
		}
		if (CurrentCommandLineLowwer == "reboot") {
			kernel->SetReBoot();
			return 0;
			CommandFound++;
		}
		if (CurrentCommandLineLowwer == "su") {
			if (CurrentCommandLineArgv != "")
			{
				userManager->SU(CurrentCommandLineArgv);
			}
			else
			{
				kernel->PrintLine(std::string("Current User: " + userManager->CurrentUsername).c_str());
			}
			CommandFound++;
		}
		if (CurrentCommandLineLowwer == "shutdown") {
			return 0;
			CommandFound++;
		}

		//CmdF Solve
		if (CommandFound == 0) {
			kernel->Print("Unknown command \"");
			kernel->Print(CurrentCommandLine.c_str());
			kernel->PrintLine("\"");
		}
		if (CommandFound > 1) {
			kernel->Print("Too much command matches of \"");
			kernel->Print(CurrentCommandLine.c_str());
			kernel->PrintLine("\"");
		}
	}

	return 0;
}

void FishTerminal::getFolders(std::string path, std::vector<std::string>& fileVec)
{
	DIR* dir;
	struct dirent* ent;
	dir = opendir(path.c_str());
	if (dir != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			if (ent->d_type == DT_DIR)
			{
				std::string szFileName = ent->d_name;
				//printf("%d\n", strcmp(".", szFileName.c_str()));
				//printf("%d\n", strcmp("..", szFileName.c_str()));
				if (strcmp(".", szFileName.c_str()) == 0 || strcmp("..", szFileName.c_str()) == 0)
					continue;
				fileVec.push_back(szFileName);
			}
		}
		closedir(dir);
	}
}

void FishTerminal::getFiles(std::string path, std::vector<std::string>& fileVec)
{
	using namespace std;

	// 文件句柄
	intptr_t hFile = 0;
	// 文件信息
	struct _finddata_t fileinfo;

	string p;

	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
		do {
			// 保存文件的全路径
			fileVec.push_back(getFileName(p.assign(path).append("\\").append(fileinfo.name)));

		} while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1

		_findclose(hFile);
	}
}

std::string& FishTerminal::lTrim(std::string& ss)
{
	std::string::iterator   p = find_if(ss.begin(), ss.end(), std::not1(std::ptr_fun(isspace)));
	ss.erase(ss.begin(), p);
	return  ss;
}

std::string& FishTerminal::rTrim(std::string& ss)
{
	std::string::reverse_iterator  p = find_if(ss.rbegin(), ss.rend(), std::not1(std::ptr_fun(isspace)));
	ss.erase(p.base(), ss.end());
	return   ss;
}

std::string& FishTerminal::trim(std::string& st)
{
	lTrim(rTrim(st));
	return   st;
}

std::string FishTerminal::getFileName(std::string path)
{
	std::string pattern = "\\";
	auto result = std::find_end(path.begin(), path.end(), pattern.begin(), pattern.end());
	if (result != path.end()) {
		auto dirName = path.substr(0, std::distance(path.begin(), result) + 1);
		//std::cout << dirName << "\n";
		auto fileName = path.substr(std::distance(path.begin(), result) + 1);
		//std::cout << fileName << "\n";
		auto fileBaseName = fileName.substr(0, fileName.size() - 4);
		//std::cout << fileBaseName << "\n";
		return fileName;
	}
	return std::string();
}
