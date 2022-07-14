#pragma once
#include <Loader/Loader.h>

class Boot
{
public:
	//INITIALIZE
	Boot(int argc, char* argv[]);

private:
	static Loader bootloader;

	std::string ReadFileToString(std::string path);
	void WriteText(std::string path, std::string text);
};