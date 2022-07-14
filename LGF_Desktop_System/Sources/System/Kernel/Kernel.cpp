#include "System/Kernel/Kernel.h"

#include <conio.h>
#include <string>
#include <fstream>

Kernel::Kernel() {
	FullScreen();

	std::cout << "LGF-DS Kernel 1.0.0.0" << std::endl << std::endl;
	std::cout << "Kernel Testing" << std::endl << std::endl;
	std::cout << "ColorTest" << std::endl << std::endl;
	for (int i = 0; i <= 7; i++) {
		SetBGColor(i);
		std::cout << "  ";
	}
	std::cout << std::endl;
	for (int i = 0; i <= 7; i++) {
		SetFColor(i);
		std::cout << "Aa";
	}
	SetColor();
	std::cout << std::endl;;
}

std::string Kernel::GetLine(GetLine_ GetLineStatus, int Size) {
	return GetLinePassword(GetLineStatus, Size, "*");
}

std::string Kernel::GetLinePassword(GetLine_ GetLineStatus, int Size, const char* PasswordChar) {
	char* Data = new char[Size];
	int CharPoint = 0;
	int Char = 0;
	std::string OutData = "";
	if (GetLineStatus == GetLine_Show) {
		while ((Char = _getch()) != '\r')
		{
			if (Char == '\b')
			{
				if (CharPoint > 0)
				{
					CharPoint--;
					Print("\b \b");
				}
				else
				{
					_putch(7);
				}
			}
			else
			{
				_putch(Char);
				Data[CharPoint++] = Char;
			}
		}
		Data[CharPoint] = '\0';
		Print("\n");
		OutData = Data;
	}

	if (GetLineStatus == GetLine_Hide) {
		while ((Char = _getch()) != '\r')
		{
			if (Char == '\b')
			{
				if (CharPoint > 0)
				{
					CharPoint--;
				}
			}
			else
			{
				Data[CharPoint++] = Char;
			}
		}
		Data[CharPoint] = '\0';
		Print("\n");
		OutData = Data;
	}

	if (GetLineStatus == GetLine_Password) {
		while ((Char = _getch()) != '\r')
		{
			if (Char == '\b')
			{
				if (CharPoint > 0)
				{
					CharPoint--;
					Print("\b \b");
				}
				else
				{
					_putch(7);
				}
			}
			else
			{
				Print(PasswordChar);
				Data[CharPoint++] = Char;
			}
		}
		Data[CharPoint] = '\0';
		Print("\n");
		OutData = Data;
	}

	//Data Memory Release
	delete[]Data;

	return OutData;
}

int __cdecl Kernel::GetChar(bool Hide) {
	if (Hide) {
		return _getch();

		/*system("stty -icanon");
		system("stty -echo");

		static char LatestGotChar = getchar();

		system("stty icanon");
		system("stty echo");
		return LatestGotChar;*/
	}
	else
		return getchar();
}

int Kernel::GetCursorPosX() {
	return _GetCursorPos();
}

int Kernel::GetCursorPosY() {
	return _GetCursorPos(false);
}

//int Kernel::SetCurrentDir(char** argv)
//{
//	return _chdir(argv[1]);
//}

int Kernel::SetCurrentDir(const char* path)
{
	return _chdir(path);
}

void Kernel::SetConsolePos(short x, short y) {
	COORD crd = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), crd);
	return;
}

void Kernel::Clear(bool UseClrScr)
{
	if (UseClrScr)
	{
		system("cls");
		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		DWORD mode;
		GetConsoleMode(hStdin, &mode);
		mode &= ~ENABLE_QUICK_EDIT_MODE;  //移除快速编辑模式
		mode &= ~ENABLE_INSERT_MODE;      //移除插入模式
		mode &= ~ENABLE_MOUSE_INPUT;
		SetConsoleMode(hStdin, mode);
		//printf("\x1B[2J\x1B[0;0f");
		//fflush(stdout);
	}
	else
	{
		GotoXY(0, 0);
		PrintFullScreen();
	}
}

void Kernel::Print(const char* format)
{
	std::cout << format << std::flush;
}

void Kernel::PrintCenter(const char* format)
{
	int CRight = ConsoleWidth;
	CRight /= 2;
	CRight -= strlen(format) / 2;

	printf("\033[%dC", CRight);
	printf(format);
}

void Kernel::PrintLine(const char* format)
{
	std::cout << format << std::endl;
}

void Kernel::PrintFullScreen(const char Char)
{
	std::string Str = "";

	for (int i = 0; i <= ConsoleHeight; i++)
		for (int i = 0; i <= ConsoleWidth; i++)
			Str += Char;

	std::cout << Str << std::flush;
}

void Kernel::NewLine(bool CharLine)
{
	if (CharLine)
		Print("\n");
	else
		GotoXY(0, (short)GetCursorPosY() + 1);
}

void Kernel::GotoXY(short x, short y)
{
	COORD crd = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), crd);
	return;
}

void Kernel::SetColor(short ForeColor, short BackGroundColor) {
	RecentForeColor = ForeColor;
	RecentBackgroundColor = BackGroundColor;

	std::string _code = "\033[";
	int FC, BC;
	ForeColor += 30;
	BackGroundColor += 40;
	FC = ForeColor;
	BC = BackGroundColor;
	_code = _code + std::to_string(FC) + ";" + std::to_string(BC) + "m";
	printf(_code.c_str());
}

void Kernel::SetBGColor(short BackGroundColor)
{
	RecentBackgroundColor = BackGroundColor;

	std::string _code = "\033[";
	int BC;
	BackGroundColor += 40;
	BC = BackGroundColor;
	_code = _code + std::to_string(BC) + "m";
	printf(_code.c_str());
}

void Kernel::SetFColor(short ForeColor)
{
	RecentForeColor = ForeColor;

	std::string _code = "\033[";
	int FC;
	ForeColor += 30;
	FC = ForeColor;
	_code = _code + std::to_string(FC) + "m";
	printf(_code.c_str());
}

void Kernel::SetReBoot(bool NeedReboot)
{
	std::ofstream outfile("Conf.d/ReBoot");
	outfile << "1";
	outfile.close();//关闭文件流
}

void Kernel::Separator(const char SepChar)
{
	std::string SepStr = "";

	for (int i = 0; i <= ConsoleWidth; i++)
		SepStr += SepChar;

	std::cout << SepStr << std::endl;
}

void Kernel::SleepThread(int MilliSec, bool AlertBefore, bool AlertAfter, int AlertMilliSecBefore, int AlertMilliSecAfter, int AlertHzBefore, int AlertHzSecAfter)
{
	if (AlertBefore)
		MilliSec -= AlertMilliSecBefore;
	if (AlertAfter)
		MilliSec -= AlertMilliSecAfter;
	if (AlertBefore)
		Beep(AlertHzBefore, AlertMilliSecBefore);
	if (MilliSec > 0)
		Sleep(MilliSec);
	if (AlertAfter)
		Beep(AlertHzSecAfter, AlertMilliSecAfter);
}

char* Kernel::GetCurrentDir()
{
	return _getcwd(DirBuf, sizeof DirBuf);
}


// PRIVATE
int Kernel::_GetCursorPos(bool X) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0, 0 }; //光标位置
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		if (X)
			return csbi.dwCursorPosition.X;
		if (!X)
			return csbi.dwCursorPosition.Y;
	}
	else
		return -1;

	return -1;
}

void Kernel::FullScreen()
{
	HANDLE Hand;
	CONSOLE_SCREEN_BUFFER_INFO Info;
	Hand = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(Hand, &Info);
	SMALL_RECT rect = Info.srWindow;
	COORD size = { rect.Right + 1 ,rect.Bottom + 1 };	//定义缓冲区大小，保持缓冲区大小和屏幕大小一致即可取消边框 
	SetConsoleScreenBufferSize(Hand, size);

	ConsoleWidth = rect.Right;
	ConsoleHeight = rect.Bottom;
}