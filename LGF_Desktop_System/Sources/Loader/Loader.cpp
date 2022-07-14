#include "Loader/Loader.h"

#include <iostream>

Loader::Loader(int argc, char* argv[])
{
	std::cout << "LGF-DS BootLoader 1.0.0.0" << std::endl << std::endl;

	UserManager userManager = UserManager();
}
