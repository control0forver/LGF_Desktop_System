#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string>
#include <corecrt_io.h>
#include <direct.h>
#include <conio.h>
#include <iostream>

#include "resource.h"

BOOL FreeResFile(DWORD dwResName, LPCSTR lpResType, LPCSTR lpFilePathName);
void SizeGoAway();
void DeleteGoAway();

extern "C"
{
	int main() {
		int LO = 0;
		printf("Launcher Options : \n");
		printf("(1). Launch\n");
		printf("(2). Update And Launch\n");
		for (int i;;)
		{
			i = _getch();
			if (i == 49) {
				LO = 1;
				break;
			}
			if (i == 50)
			{
				printf("Path to system: ");
				LO = 2;
				break;
			}
		}

		if (LO == 2) {
			if (_access("bin", 0) == -1)
				if (_mkdir("bin") == -1)
					return -1;
			if (!FreeResFile(IDR_DLL1, "DLL", "bin\\ANSI32.dll"))
				return -1;
			if (!FreeResFile(IDR_EXE1, "EXE", "bin\\console.exe"))
				return -1;
			if (!FreeResFile(104, "EXE", "bin\\LGF-DS.BIN"))
				return -1;
		}

		std::string System = "";
		printf("System to launch : \n");
		printf("(1). LGF Desktop System (Systems/System)\n");
		printf("(2). Custom Path (Systems/...)\n");
		
		for (int i;;)
		{
			i = _getch();
			if (i == 49) {
				System = "Systems/System";
				break;
			}
			if (i == 50)
			{
				printf("Path to system: ");
				std::cin >> System;
				break;
			}
		}

		printf("Launching...");
		if (_access("bin", 0) == -1)
			if (_mkdir("bin") == -1)
				return -1;
		if (_access("bin\\ANSI32.dll", 0) == -1)
			if (!FreeResFile(IDR_DLL1, "DLL", "bin\\ANSI32.dll"))
				return -1;
		if (_access("bin\\console.exe", 0) == -1)
			if (!FreeResFile(IDR_EXE1, "EXE", "bin\\console.exe"))
				return -1;
		if (_access("bin\\LGF-DS.exe", 0) == -1)
			if (!FreeResFile(104, "EXE", "bin\\LGF-DS.BIN"))
				return -1;
		system("cls");

		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof cfi;
		cfi.nFont = 0;
		cfi.dwFontSize.X = 8; //字宽
		cfi.dwFontSize.Y = 18;//字高
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;//粗细
		wcscpy_s(cfi.FaceName, L"Terminal"); //设置字体，此处设为点阵字体
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

		HANDLE Hand;
		CONSOLE_SCREEN_BUFFER_INFO Info;
		Hand = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(Hand, &Info);
		SMALL_RECT rect = Info.srWindow;
		COORD size = { rect.Right + 1 ,rect.Bottom + 1 };	//定义缓冲区大小，保持缓冲区大小和屏幕大小一致即可取消边框 
		SetConsoleScreenBufferSize(Hand, size);

		HWND hwnd = GetForegroundWindow();
		int cx = GetSystemMetrics(SM_CXSCREEN);
		int cy = GetSystemMetrics(SM_CYSCREEN);

		LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);
		SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);

		SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);

		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		DWORD mode;
		GetConsoleMode(hStdin, &mode);
		mode &= ~ENABLE_QUICK_EDIT_MODE;  //移除快速编辑模式
		mode &= ~ENABLE_INSERT_MODE;      //移除插入模式
		mode &= ~ENABLE_MOUSE_INPUT;
		SetConsoleMode(hStdin, mode);

		SizeGoAway();
		DeleteGoAway();

		_chdir(std::string("bin/" + System).c_str());

		system("title LGF Desktop System");
		system("..\\..\\console.exe ..\\..\\LGF-DS.BIN");

		return 0;
	}
}

/*
函数功能：释放资源文件

参数说明：DWORD dwResName   指定要释放的资源ID号，如IDR_EXE
		  LPCSTR lpResType 指定释放的资源的资源类型
		  LPCSTR lpFilePathName 指定释放后的目标文件名

返回值：成功则返回TRUE,失败返回FALSE
*/
BOOL FreeResFile(DWORD dwResName, LPCSTR lpResType, LPCSTR lpFilePathName)
{
	HMODULE hInstance = ::GetModuleHandle(NULL);//得到自身实例句柄  

	HRSRC hResID = ::FindResource(hInstance, MAKEINTRESOURCE(dwResName), lpResType);//查找资源  
	HGLOBAL hRes = ::LoadResource(hInstance, hResID);//加载资源  
	LPVOID pRes = ::LockResource(hRes);//锁定资源  

	if (pRes == NULL)//锁定失败  
	{
		return FALSE;
	}
	DWORD dwResSize = ::SizeofResource(hInstance, hResID);//得到待释放资源文件大小  
	HANDLE hResFile = CreateFile(lpFilePathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//创建文件  

	if (INVALID_HANDLE_VALUE == hResFile)
	{
		//TRACE("创建文件失败！");  
		return FALSE;
	}

	DWORD dwWritten = 0;//写入文件的大小     
	WriteFile(hResFile, pRes, dwResSize, &dwWritten, NULL);//写入文件  
	CloseHandle(hResFile);//关闭文件句柄  

	return (dwResSize == dwWritten);//若写入大小等于文件大小，返回成功，否则失败  
}

//取消最大化，最小化
void SizeGoAway() {
	SetWindowLongPtrA(
		GetConsoleWindow(),
		GWL_STYLE,
		GetWindowLongPtrA(GetConsoleWindow(), GWL_STYLE) & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
}

//取消关闭  谨慎使用，坑人专用
void DeleteGoAway() {
	DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE),
		SC_CLOSE, MF_DISABLED);
	DrawMenuBar(GetConsoleWindow());
}