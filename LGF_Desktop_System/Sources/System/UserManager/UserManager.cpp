#include <System/UserManager/UserManager.h>
#include <System/Terminal/FishTerminal.h>

#include <conio.h>
#include <iostream>
#include <fstream>

void split(const std::string& s, std::vector<std::string>& tokens, const std::string& delimiters);
void WriteText(std::string path, std::string text);

UserManager::UserManager()
{
	using namespace std;

	CurrentUsername = "";
	CurrentPassword = "";

	std::string str = ReadFileToString(USERSFILE);
	std::vector<std::string> Lines;
	split(str, Lines, "\n");
	for (int i = 0; i < Lines.size(); i++) {
		Users[i] = Lines[i].substr(0, Lines[i].find_first_of(':'));
		Passwd[i] = Lines[i].substr(Lines[i].find_first_of(':') + 1);
	}
	if (Lines.size() == 0) {
		Register();
		kernel->SetReBoot();
	}
	else
		Load();
}

int UserManager::Load()
{
	int RetriedC = 1;
	for (; RetriedC <= 3; RetriedC++) {
		kernel->NewLine();
		kernel->Print("UserManager 1.0.0.0\n");
		kernel->PrintLine("UserManager -- Login");
		kernel->Separator();
		kernel->Print("Username: ");
		CurrentUsername = kernel->GetLine(kernel->GetLine_Show, USERNAME_LEN);

		kernel->Print("Password of "); kernel->Print(CurrentUsername.c_str()); kernel->Print(": ");
		CurrentPassword = kernel->GetLinePassword(kernel->GetLine_Password, PASSWORD_LEN);
		for (int i = 0; i <= 256; i++) {
			if (CurrentUsername == Users[i] && CurrentPassword == Passwd[i]) {
				RetriedC = -1;
				break;
			}
		}
		if (RetriedC == -1)
			break;

		Beep(1500, 150);
	}

	if (RetriedC > 3)
	{
		kernel->PrintLine("To much errors after 3 retries.");
		kernel->SleepThread(1800);

		return -1;
	}

	UserLogin(CurrentUsername);
	/*for (int i = 0; i <= 7; i++) {
		kernel->SetBGColor(i);
		kernel->PrintFullScreen();
		_getch();
	}*/
	FishTerminal FT = FishTerminal(kernel, this);
	FT.Start();

	//Uninstall
	UserLogout(CurrentUsername);
	return 0;
}

int UserManager::Register() {
	kernel->NewLine();
	kernel->Print("UserManager 1.0.0.0\n");
	kernel->PrintLine("UserManager -- Register");
	kernel->Separator();
	std::string str = ReadFileToString(USERSFILE);
	std::string uName, _pWord, pWord;

	kernel->Print("Username: ");
	uName = kernel->GetLine();

	for (;;) {
		kernel->Print(std::string("Password of " + uName + ": ").c_str());
		_pWord = kernel->GetLine(kernel->GetLine_Password);
		kernel->Print("Confirm Password: ");
		pWord = kernel->GetLine(kernel->GetLine_Password);
		if (pWord == _pWord)
			break;
		else
			kernel->PrintLine("Password error, please try again.\n");
	}
	str = uName + ":" + pWord + "\n" + str + '\0';
	WriteText(USERSFILE, str);

	ReLoad_UsersList();

	return 0;
}

int UserManager::Register(std::string Username, std::string Password)
{
	std::string str = ReadFileToString(USERSFILE);
	std::string uName, pWord;

	uName = Username;
	pWord = Password;

	str = uName + ":" + pWord + "\n" + str + '\0';
	WriteText(USERSFILE, str);

	ReLoad_UsersList();

	return 0;
}

int UserManager::SU(std::string Username) {
	int RetriedC = 1;
	std::string _CurrentUsername, _CurrentPassword;
	_CurrentUsername = Username;
	for (; RetriedC <= 3; RetriedC++) {
		kernel->NewLine();
		kernel->Print("UserManager 1.0.0.0\n");
		kernel->PrintLine("UserManager -- Switch User");
		kernel->Separator();

		kernel->Print("Password of "); kernel->Print(_CurrentUsername.c_str()); kernel->Print(": ");
		_CurrentPassword = kernel->GetLinePassword(kernel->GetLine_Password, PASSWORD_LEN);
		for (int i = 0; i <= 256; i++) {
			if (_CurrentUsername == Users[i] && _CurrentPassword == Passwd[i]) {
				RetriedC = -1;
				break;
			}
		}
		if (RetriedC == -1)
			break;

		Beep(1500, 150);
	}

	if (RetriedC > 3)
	{
		kernel->PrintLine("To much errors after 3 retries.");
		kernel->SleepThread(1800);

		return -1;
	}

	CurrentPassword = _CurrentPassword;
	UserLogin(_CurrentUsername);
	/*for (int i = 0; i <= 7; i++) {
		kernel->SetBGColor(i);
		kernel->PrintFullScreen();
		_getch();
	}*/
	FishTerminal FT = FishTerminal(kernel, this);
	FT.Start();

	//Uninstall
	UserLogout(CurrentUsername);
	return 0;
}

void UserManager::ReLoad_UsersList()
{
	CurrentUsername = "";
	CurrentPassword = "";

	std::string str = ReadFileToString(USERSFILE);
	std::vector<std::string> Lines;
	split(str, Lines, "\n");
	for (int i = 0; i < Lines.size(); i++) {
		Users[i] = Lines[i].substr(0, Lines[i].find_first_of(':'));
		Passwd[i] = Lines[i].substr(Lines[i].find_first_of(':') + 1);
	}
	if (Lines.size() == 0) {
		Register();
		ReLoad_UsersList();
	}
}

void UserManager::UserLogin(std::string Username)
{
	IUserLogined++;
	UserLogined[IUserLogined] = Username;
	CurrentUsername = UserLogined[IUserLogined];
}

void UserManager::UserLogout(std::string Username)
{
	UserLogined[IUserLogined] = "";
	IUserLogined--;
	CurrentUsername = UserLogined[IUserLogined];
}

std::string UserManager::ReadFileToString(std::string path)
{
	std::string str;

	FILE* p_file;
	long lSize;
	char* szBuf;

	p_file = fopen(path.c_str(), "r+");
	if (p_file)
	{
		fseek(p_file, 0, SEEK_END);
		lSize = ftell(p_file);
		fseek(p_file, 0, SEEK_SET);
		szBuf = new char[lSize + 1];
		fread(szBuf, 1, lSize, p_file);
		fclose(p_file);
		szBuf[lSize] = 0;
		str = szBuf;
		delete szBuf;
		return str;
	}
	else
		return "NULL";
}

void split(const std::string& s, std::vector<std::string>& tokens, const std::string& delimiters)
{
	std::string::size_type lastPos = s.find_first_not_of(delimiters, 0);
	std::string::size_type pos = s.find_first_of(delimiters, lastPos);
	while (std::string::npos != pos || std::string::npos != lastPos) {
		tokens.push_back(s.substr(lastPos, pos - lastPos));//use emplace_back after C++11
		lastPos = s.find_first_not_of(delimiters, pos);
		pos = s.find_first_of(delimiters, lastPos);
	}
}

void WriteText(std::string path, std::string text) {
	std::ofstream outfile(path);
	outfile << text;
	outfile.close();//关闭文件流
}