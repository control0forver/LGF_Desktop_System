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
void rgb_init() {																// ��ʼ��
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);		//������
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);		//������
	DWORD dwInMode, dwOutMode;
	GetConsoleMode(hIn, &dwInMode);						//��ȡ����̨����ģʽ
	GetConsoleMode(hOut, &dwOutMode);					//��ȡ����̨���ģʽ
	dwInMode |= 0x0200;									//����
	dwOutMode |= 0x0004;
	SetConsoleMode(hIn, dwInMode);						//���ÿ���̨����ģʽ
	SetConsoleMode(hOut, dwOutMode);					//���ÿ���̨���ģʽ
}

void rgb_set(int wr,int wg,int wb,int br,int bg,int bb) {						//����RGB
	printf("\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm",wr,wg,wb,br,bg,bb);	//\033[38��ʾǰ����\033[48��ʾ����������%d��ʾ��ϵ���
}*/

#elif __linux__
#include <stdio.h>
#include <iostream>
/*
������ɫ��Χ:	40--49        ǰ����ɫ: 30--39
				40: ��                  30: ��
				41: ��                  31: ��
				42: ��                  32: ��
				43: ��                  33: ��
				44: ��                  34: ��
				45: ��                  35: ��
				46: ����                36: ����
				47: ��ɫ                37: ��ɫ
ANSI������:
QUOTE:
  \033[0m  �ر��������� 
  \033[1m  ���ø����� 
  \03[4m  �»��� 
  \033[5m  ��˸ 
  \033[7m  ���� 
  \033[8m  ���� 
  \033[30m  --  \033[37m  ����ǰ��ɫ 
  \033[40m  --  \033[47m  ���ñ���ɫ 
  \033[nA  �������n�� 
  \03[nB  �������n�� 
  \033[nC  �������n�� 
  \033[nD  �������n�� 
  \033[y;xH���ù��λ�� 
  \033[2J  ���� 
  \033[K  ����ӹ�굽��β������ 
  \033[s  ������λ�� 
  \033[u  �ָ����λ�� 
  \033[?25l  ���ع�� 
  \33[?25h  ��ʾ���
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
