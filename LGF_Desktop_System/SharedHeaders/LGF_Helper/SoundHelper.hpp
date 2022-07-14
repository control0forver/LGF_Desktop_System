class SoundHelper
{
  private:
	char *path;

  public:
	void Load(char _path[]);
	void Play();
	void PlayLoop();
	void Abort();
};

#pragma once

#include "console.hpp"

#include <stdlib.h>
#include <thread>
#include <string>
#include <fstream>
#include <iostream>

char *__path;
bool loop;
bool loaded = false;

void th_play()
{
#ifdef _WIN32
#elif __linux__
	//system("play music.ogg>nul 2>nul");
	std::string cmd(__path);
	cmd = "play " + cmd + ">nul 2>nul";
	if (!loop)
	{
		system(cmd.c_str());
	}
	else
	{
		int ret = 0;
		for (; loop;)
		{
			//Console::sleep(1000);
			ret = system(cmd.c_str());
		}
	}
#endif
}
std::thread Th(th_play);

void SoundHelper::Load(char _path[])
{
	std::ifstream ifs;
	ifs.open(_path);
	if (!ifs.is_open()){
		std::cout << std::endl << "SoundHelper Error: file read error!" << "(" << _path <<")"<< std::endl;
		loaded = false;
		return;
	}
	loaded = true;
	path = _path;
	__path = path;
}

void SoundHelper::Play()
{
	if (!loaded) return;
	loop = false;
	Th.detach();
}

void SoundHelper::PlayLoop()
{
	if (!loaded) return;
	loop = true;
	Th.detach();
}

void SoundHelper::Abort()
{
	loop = false;
	//Th.stop();
}