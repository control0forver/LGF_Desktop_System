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
	//���ļ����뵽ostringstream����buf��
	std::ostringstream buf;
	char ch;
	while (buf && ifile.get(ch))
		buf.put(ch);
	//������������buf�������ַ���
	return buf.str();
}
}