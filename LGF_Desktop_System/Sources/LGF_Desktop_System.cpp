#include "LGF_Desktop_System.h"
#include <Hooks/keyboard_mouse_hook.h>

#include <iostream>

//System main entry
int main(int argc, char* argv[]) {
	std::cout << "LGF-DS Version 1.0.0.0A" << std::endl << "Copyright 2022, LGF. All rights reserved." << std::endl << std::endl;
	std::cout << "LGF-Studio's Message" << std::endl;
	std::cout << "[Press enter to show]" << std::endl;
	getchar();
	std::cout << std::endl << "  抱歉，我们的团队(LGF-Studio)将要放弃该项目并开源。我们的基础功能实现的貌似不太理想，后续的扩展和开发将会持续遭到困难与问题。" << std::endl;
	std::cout << "我们现在尽量在最后的一点时间里，将该项目尽我们所能的完善。" << std::endl;
	std::cout << "我们希望我们以后将会重拾该项目并对其重新改造，重写。" << std::endl;
	std::cout << "当然，在我们离开的这段时间里，我们也希望会有人有兴趣来研究我们的项目。" << std::endl;
	std::cout << "(See it on https://github.com/control0forver/LGF_Desktop_System)" << std::endl << std::endl;

	std::cout << "LGF-DS Booting..." << std::endl << std::endl;

	LGF_Desktop_System LGFDS;
	LGFDS.boot = Boot(argc, argv);

	std::cout << "LGF-DS Shutdown" << std::endl << std::endl;
	return -0;
}