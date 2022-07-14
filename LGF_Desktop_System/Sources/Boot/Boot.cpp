#include <Boot/Boot.h>

#include <iostream>
#include <fstream>

Boot::Boot(int argc, char* argv[])
{
	for (;;) {
		WriteText("Conf.d/ReBoot", "0");
		std::cout << "LGF-DS Boot 1.0.0.0" << std::endl << std::endl;
		bootloader = Loader(argc, argv);
		std::string str = ReadFileToString("Conf.d/ReBoot");
		if (str == "0")
			break;
	}
}

std::string Boot::ReadFileToString(std::string path)
{
	std::string str;

	FILE* p_file;
	long lSize;
	char* szBuf;

	p_file = fopen(path.c_str(), "r+");
	if (p_file)
	{
		fseek(p_file, 0, SEEK_END);
		lSize = ftell(p_file);
		fseek(p_file, 0, SEEK_SET);
		szBuf = new char[lSize + 1];
		fread(szBuf, 1, lSize, p_file);
		fclose(p_file);
		szBuf[lSize] = 0;
		str = szBuf;
		delete szBuf;
		return str;
	}
	else
		return "NULL";
}

void Boot::WriteText(std::string path, std::string text) {
	std::ofstream outfile(path);
	outfile << text;
	outfile.close();//关闭文件流
}
