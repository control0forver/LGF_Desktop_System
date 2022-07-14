#pragma once
#ifdef _WIN32
#include <direct.h>
// MSDN recommends against using getcwd & chdir names
#define cwd _getcwd
#define cd _chdir
#else
#include "unistd.h"
#define cwd getcwd
#define cd chdir
#endif

#include <iostream>

char buf[4096]; // never know how much is needed

char *getdir()
{
	return cwd(buf, sizeof buf);
}

int setdir(char **argv)
{
	return cd(argv[1]);
}