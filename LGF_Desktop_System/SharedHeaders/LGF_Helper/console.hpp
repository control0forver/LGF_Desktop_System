#pragma once

#include <stdio.h>
#include <iostream>

namespace Console
{
    void clrscr()
    {
        printf("\x1B[2J\x1B[0;0f");
        fflush(stdout);
    }

    void sleep(int milliseconds);

    void flush()
    {
        std::cout << std::flush;
    };

    void putch(char ch)
    {
        putchar(ch);
        printf("\033[1C");
    }

    void gotoxy(short x, short y);

    int getch(void);

    void terminal_lnbuf(int yn);

    void terminal_echo(int yn);

    void display_delay(char text[], int delay, int speed_add = 0)
    {
        bool first = true;
        for (int i = 0; i <= strlen(text); i++)
        {
            if (!first)
            {
                delay -= speed_add;
            }
            else
                first = false;
            Console::sleep(delay);
            std::cout << text[i] << std::flush;
        }
    }

#ifdef _WIN32
#include <windows.h>
    const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //���ھ��

    void sleep(int milliseconds)
    {
        Sleep(milliseconds);
    }
    void gotoxy(short x, short y)
    {
        COORD crd = {x, y};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), crd);
        return;
    }
    int getch(void)
    {
        char a;
        system("stty -icanon"); //关闭终端缓冲区
        system("stty -echo");   //关闭终端回显
        a = getchar();
        system("stty icanon"); //打开终端缓冲区
        system("stty echo");   //打开终端回显
        return a;
    }
    void hide_cursor()
    {
        CONSOLE_CURSOR_INFO cursor;
        cursor.bVisible = 0;
        cursor.dwSize = 1;
        SetConsoleCursorInfo(handle, &cursor);
    }
    void show_cursor()
    {
        CONSOLE_CURSOR_INFO cursor;
        cursor.bVisible = 1;
        cursor.dwSize = 1;
        SetConsoleCursorInfo(handle, &cursor);
    }
#elif __linux__
#include <unistd.h>
#include <termio.h>
    void sleep(int milliseconds)
    {
        usleep(milliseconds * 1000);
    }
    void gotoxy(short x, short y)
    {
        printf("%c[%d;%df", 0x1B, y, x);
        return;
    }
    void terminal_lnbuf(int yn)
    {
        struct termios oldt, newt;
        tcgetattr(0, &oldt);
        newt = oldt;
        if (!yn)
            newt.c_lflag &= ~ICANON;
        else
            newt.c_lflag |= ICANON;
        tcsetattr(0, TCSANOW, &newt);
    }

    void terminal_echo(int yn)
    {
        struct termios oldt, newt;
        tcgetattr(0, &oldt);
        newt = oldt;
        if (!yn)
            newt.c_lflag &= ~ECHO;
        else
            newt.c_lflag |= ECHO;
        tcsetattr(0, TCSANOW, &newt);
    }
    int getch()
    {
        register int ch;
        terminal_lnbuf(0);
        terminal_echo(0);
        ch = getchar();
        terminal_lnbuf(1);
        terminal_echo(1);
        return ch;
    }
    void hide_cursor()
    {
        printf("\033[?25l");
        return;
    }
    void show_cursor()
    {
        printf("\033[?25h");
        return;
    }
#endif
}