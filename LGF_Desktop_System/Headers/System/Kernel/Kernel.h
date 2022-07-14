#pragma once

#include <iostream>
#include <Windows.h>
#include <direct.h>

class Kernel {
public:
	Kernel();

	//Datas
	int RecentBackgroundColor, RecentForeColor;
	int ConsoleWidth, ConsoleHeight;

	//Enums
	enum GetLine_ {
		GetLine_Show,
		GetLine_Hide,
		GetLine_Password
	};

	//System API Functions
	std::string GetLine(GetLine_ GetLineStatus = GetLine_Show, int Size = 128);
	std::string GetLinePassword(GetLine_ GetLineStatus = GetLine_Show, int Size = 128, const char* PasswordChar = "*");

	int __cdecl GetChar(bool Hide = false);
	int GetCursorPosX();
	int GetCursorPosY();
	//int SetCurrentDir(char** argv);
	int SetCurrentDir(const char* path);

	void Clear(bool UseClrScr = true);
	void Print(const char* format);
	void PrintCenter(const char* format);
	void PrintLine(const char* format);
	void PrintFullScreen(const char Char = ' ');
	void NewLine(bool CharLine = true);
	void GotoXY(short x, short y);
	void SetConsolePos(short x = 0, short y = 0);
	/*0 - 9
	0: 黑色  1: 红色  2: 绿色  3: 黄色 
	4: 蓝色  5: 紫色  6: 深绿  7: 白色*/
	void SetColor(short ForeColor = 7, short BackGroundColor = 0);
	/*0 - 9
	0: 黑色  1: 红色  2: 绿色  3: 黄色
	4: 蓝色  5: 紫色  6: 深绿  7: 白色*/
	void SetBGColor(short BackGroundColor = 0);
	/*0 - 9
	0: 黑色  1: 红色  2: 绿色  3: 黄色
	4: 蓝色  5: 紫色  6: 深绿  7: 白色*/
	void SetFColor(short ForeColor = 7);
	void SetReBoot(bool NeedReboot = true);
	void Separator(const char SepChar = '-');
	void SleepThread(int MilliSec = 1000, bool AlertBefore = false, bool AlertAfter = false, int AlertMilliSecBefore = 450, int AlertMilliSecAfter = 900, int AlertHzBefore = 659, int AlertHzSecAfter = 700);

	char* GetCurrentDir();


private:
	char DirBuf[4096];

	int _GetCursorPos(bool X = true);

	void FullScreen();
};