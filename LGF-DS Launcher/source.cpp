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
		cfi.dwFontSize.X = 8; //�ֿ�
		cfi.dwFontSize.Y = 18;//�ָ�
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;//��ϸ
		wcscpy_s(cfi.FaceName, L"Terminal"); //�������壬�˴���Ϊ��������
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

		HANDLE Hand;
		CONSOLE_SCREEN_BUFFER_INFO Info;
		Hand = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(Hand, &Info);
		SMALL_RECT rect = Info.srWindow;
		COORD size = { rect.Right + 1 ,rect.Bottom + 1 };	//���建������С�����ֻ�������С����Ļ��Сһ�¼���ȡ���߿� 
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
		mode &= ~ENABLE_QUICK_EDIT_MODE;  //�Ƴ����ٱ༭ģʽ
		mode &= ~ENABLE_INSERT_MODE;      //�Ƴ�����ģʽ
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
�������ܣ��ͷ���Դ�ļ�

����˵����DWORD dwResName   ָ��Ҫ�ͷŵ���ԴID�ţ���IDR_EXE
		  LPCSTR lpResType ָ���ͷŵ���Դ����Դ����
		  LPCSTR lpFilePathName ָ���ͷź��Ŀ���ļ���

����ֵ���ɹ��򷵻�TRUE,ʧ�ܷ���FALSE
*/
BOOL FreeResFile(DWORD dwResName, LPCSTR lpResType, LPCSTR lpFilePathName)
{
	HMODULE hInstance = ::GetModuleHandle(NULL);//�õ�����ʵ�����  

	HRSRC hResID = ::FindResource(hInstance, MAKEINTRESOURCE(dwResName), lpResType);//������Դ  
	HGLOBAL hRes = ::LoadResource(hInstance, hResID);//������Դ  
	LPVOID pRes = ::LockResource(hRes);//������Դ  

	if (pRes == NULL)//����ʧ��  
	{
		return FALSE;
	}
	DWORD dwResSize = ::SizeofResource(hInstance, hResID);//�õ����ͷ���Դ�ļ���С  
	HANDLE hResFile = CreateFile(lpFilePathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//�����ļ�  

	if (INVALID_HANDLE_VALUE == hResFile)
	{
		//TRACE("�����ļ�ʧ�ܣ�");  
		return FALSE;
	}

	DWORD dwWritten = 0;//д���ļ��Ĵ�С     
	WriteFile(hResFile, pRes, dwResSize, &dwWritten, NULL);//д���ļ�  
	CloseHandle(hResFile);//�ر��ļ����  

	return (dwResSize == dwWritten);//��д���С�����ļ���С�����سɹ�������ʧ��  
}

//ȡ����󻯣���С��
void SizeGoAway() {
	SetWindowLongPtrA(
		GetConsoleWindow(),
		GWL_STYLE,
		GetWindowLongPtrA(GetConsoleWindow(), GWL_STYLE) & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
}

//ȡ���ر�  ����ʹ�ã�����ר��
void DeleteGoAway() {
	DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE),
		SC_CLOSE, MF_DISABLED);
	DrawMenuBar(GetConsoleWindow());
}