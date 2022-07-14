#pragma once

int RecentBackgroundColor, RecentForeColor;

void SetColor(unsigned short ForeColor, unsigned short BackGroundColor);
void SetBGColor(unsigned short BackGroundColor);
void SetFColor(unsigned short ForeColor);
#ifdef _WIN32
#include <Windows.h>
void SetColor(unsigned short ForeColor = 7, unsigned short BackGroundColor = 0)
{
	RecentForeColor = ForeColor;
	RecentBackgroundColor = BackGroundColor;
	
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, (ForeColor % 16) | (BackGroundColor % 16 * 16));
}

void SetBGColor(unsigned short BackGroundColor = 0){
	RecentBackgroundColor = BackGroundColor;
	
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, (BackGroundColor % 16 * 16));
}
void SetFColor(unsigned short ForeColor = 7){
	RecentForeColor = ForeColor;
	
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, (ForeColor % 16));
}
/* RBG Support needs win10+
void rgb_init() {																// 初始化
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);		//输入句柄
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);		//输出句柄
	DWORD dwInMode, dwOutMode;
	GetConsoleMode(hIn, &dwInMode);						//获取控制台输入模式
	GetConsoleMode(hOut, &dwOutMode);					//获取控制台输出模式
	dwInMode |= 0x0200;									//更改
	dwOutMode |= 0x0004;
	SetConsoleMode(hIn, dwInMode);						//设置控制台输入模式
	SetConsoleMode(hOut, dwOutMode);					//设置控制台输出模式
}

void rgb_set(int wr,int wg,int wb,int br,int bg,int bb) {						//设置RGB
	printf("\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm",wr,wg,wb,br,bg,bb);	//\033[38表示前景，\033[48表示背景，三个%d表示混合的数
}*/

#elif __linux__
#include <stdio.h>
#include <iostream>
/*
背景颜色范围:	40--49        前景颜色: 30--39
				40: 黑                  30: 黑
				41: 红                  31: 红
				42: 绿                  32: 绿
				43: 黄                  33: 黄
				44: 蓝                  34: 蓝
				45: 紫                  35: 紫
				46: 深绿                36: 深绿
				47: 白色                37: 白色
ANSI控制码:
QUOTE:
  \033[0m  关闭所有属性 
  \033[1m  设置高亮度 
  \03[4m  下划线 
  \033[5m  闪烁 
  \033[7m  反显 
  \033[8m  消隐 
  \033[30m  --  \033[37m  设置前景色 
  \033[40m  --  \033[47m  设置背景色 
  \033[nA  光标上移n行 
  \03[nB  光标下移n行 
  \033[nC  光标右移n行 
  \033[nD  光标左移n行 
  \033[y;xH设置光标位置 
  \033[2J  清屏 
  \033[K  清除从光标到行尾的内容 
  \033[s  保存光标位置 
  \033[u  恢复光标位置 
  \033[?25l  隐藏光标 
  \33[?25h  显示光标
*/
void SetColor(short ForeColor = 7, short BackGroundColor = 0)
{
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

void SetBGColor(short BackGroundColor = 0){
	RecentBackgroundColor = BackGroundColor;
	
	std::string _code = "\033[";
	int BC;
	BackGroundColor += 40;
	BC = BackGroundColor;
	_code = _code + std::to_string(BC) + "m";
	printf(_code.c_str());
}
void SetFColor(short ForeColor = 7){
	RecentForeColor = ForeColor;
	
	std::string _code = "\033[";
	int FC;
	ForeColor += 30;
	FC = ForeColor;
	_code = _code + std::to_string(FC) + "m";
	printf(_code.c_str());
}
#endif
