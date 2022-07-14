#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

namespace FileHelper
{
static bool if_file_exist(std::string path)
{
	std::fstream _file;
	_file.open(path, std::ios::in);
	if (!_file)
	{
		return false;
	}
	else
	{
		return true;
	}
}

static std::string readFileIntoString(char *filename)
{
	std::ifstream ifile(filename);
	//将文件读入到ostringstream对象buf中
	std::ostringstream buf;
	char ch;
	while (buf && ifile.get(ch))
		buf.put(ch);
	//返回与流对象buf关联的字符串
	return buf.str();
}
}