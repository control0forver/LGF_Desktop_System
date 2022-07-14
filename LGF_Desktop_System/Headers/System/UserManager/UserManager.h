#pragma once

#define USERNAME_LEN 128
#define PASSWORD_LEN 128
#define USERSFILE "./Conf.d/UserManager"

#include <System/Kernel/Kernel.h>

class UserManager
{
public:
	std::string CurrentUsername;

	std::string Users[256]{ "" };
	std::string Passwd[256]{ "" };

	UserManager();

	int Load();
	int Register();
	int Register(std::string Username, std::string Password);
	int SU(std::string Username);

	void ReLoad_UsersList();

	std::string ReadFileToString(std::string path);

private:
	Kernel* kernel = new Kernel();

	void UserLogin(std::string Username);
	void UserLogout(std::string Username);

	std::string CurrentPassword;
	std::string UserLogined[256]{ "" };
	int IUserLogined = -1;
};

