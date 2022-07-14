#pragma once
#include <System/Kernel/Kernel.h>
#include <System/UserManager/UserManager.h>

class LegacyGUI
{
public:
	LegacyGUI(Kernel* _kernel, UserManager* _userManager);

	int Terminal_GUI();

	void DisPlayDemo();
private:
	Kernel* kernel;
	UserManager* userManager;
};

