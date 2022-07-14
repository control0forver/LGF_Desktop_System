#include <System/LegacyGUI/LegacyGUI.h>

#include <ConsoleUI/Demo/Demo.h>
#include <ConsoleUI/ConsoleUI.h>
#include <ConsoleUI/ConsoleComCtrl.h>


LegacyGUI::LegacyGUI(Kernel* _kernel, UserManager* _userManager)
{
	kernel = _kernel;
	userManager = _userManager;
}

int LegacyGUI::Terminal_GUI()
{
	using namespace GL;
	ConsoleUI consoleUI(dark_blue);
	bool bExit = false;
	consoleUI.setScreenBufferSize(kernel->ConsoleWidth, kernel->ConsoleHeight);

	ConsolePlane titlePlane(&consoleUI);
	Rect rectTitle;
	rectTitle.X = 0;
	rectTitle.Y = 0;
	rectTitle.nWidth = consoleUI.getConsoleScreenInfo().dwSize.X;
	rectTitle.nHeight = 1;
	consoleUI.setControlRect(&titlePlane, rectTitle, false);
	titlePlane.setBkColor(GL::blue);
	consoleUI.addControl(&titlePlane);
	consoleUI.addEvent(&titlePlane);

	ConsoleLabel titleLabel(&consoleUI);
	titleLabel.setWidth(consoleUI.getConsoleScreenInfo().dwSize.X);
	titleLabel.setAlign(ConsoleLabel::center);
	titleLabel.setPosition(0, 0);
	titleLabel.setTextColor(GL::dark_white);
	titleLabel.setContent("Fish Terminal GUI 1.0.0.0");
	consoleUI.addControl(&titleLabel);

	ConsoleButton btClost(&consoleUI);
	//btClost.setCaption("×");
	btClost.setCaption("X");
	btClost.setSelectable(true);
	btClost.setBkColor(blue);
	btClost.setTextColor(white);
	Rect rectClose;
	rectClose.nWidth = 4;
	rectClose.nHeight = 1;
	rectClose.X = consoleUI.getConsoleScreenInfo().dwSize.X - rectClose.nWidth - 1;
	rectClose.Y = 0;
	consoleUI.setControlRect(&btClost, rectClose, false);
	btClost.setClickedEvent([&](void)->void {
		consoleUI.endLoopEvent();
		consoleUI.endLoopEvent();
		bExit = true;
		});
	consoleUI.addEvent(&btClost);
	consoleUI.addControl(&btClost);

	ConsoleLabel label1(&consoleUI);
	label1.setContent("Register");
	label1.setID("label1");
	label1.setPosition(1, 3);
	label1.setAutoWidth(true);
	consoleUI.addControl(&label1);

	ConsoleInputBox inputBox1(&consoleUI);
	inputBox1.setWidth(16);
	inputBox1.setPosition(2, 4);
	inputBox1.setSelectable(true);
	inputBox1.setID("INPUT_BOX1");
	inputBox1.setBkColor(GL::blue);
	consoleUI.addControl(&inputBox1);
	consoleUI.addEvent(&inputBox1);

	ConsoleLabel label2(&consoleUI);
	label2.setContent("Password");
	label2.setID("label2");
	label2.setPosition(1, 6);
	label2.setAutoWidth(true);
	consoleUI.addControl(&label2);

	ConsoleInputBox inputBox2(&consoleUI);
	inputBox2.setWidth(22);
	inputBox2.setPosition(2, 7);
	inputBox2.setSelectable(true);
	inputBox2.setID("INPUT_BOX2");
	inputBox2.setBkColor(GL::blue);
	consoleUI.addControl(&inputBox2);
	consoleUI.addEvent(&inputBox2);

	ConsoleLabel label3(&consoleUI);
	label3.setContent("Confirm Password");
	label3.setID("label3");
	label3.setPosition(1, 9);
	label3.setAutoWidth(true);
	consoleUI.addControl(&label3);

	ConsoleInputBox inputBox3(&consoleUI);
	inputBox3.setWidth(22);
	inputBox3.setPosition(2, 10);
	inputBox3.setSelectable(true);
	inputBox3.setID("INPUT_BOX3");
	inputBox3.setBkColor(GL::blue);
	consoleUI.addControl(&inputBox3);
	consoleUI.addEvent(&inputBox3);

	ConsoleLabel label4(&consoleUI);
	label4.setContent("Confirm Password Failed");
	label4.setID("label4");
	label4.setPosition(3, 11);
	label4.setAutoWidth(true);
	label4.setTextColor(red);
	label4.setVisible(false);
	consoleUI.addControl(&label4);

	std::function<void(void)> onGetTextClick = [&](void) -> void {
		//consoleUI.redraw();
		if (inputBox2.getContent() == inputBox3.getContent()) {
			label4.setVisible(false);
			consoleUI.redrawControl(&label4);
			userManager->Register(inputBox1.getContent(), inputBox3.getContent());
		}
		else
		{
			label4.setVisible(true);
			consoleUI.redrawControl(&label4);
		}
	};
	ConsoleButton btGetText(&consoleUI);
	btGetText.setCaption("Register");
	btGetText.setSelectable(true);
	Rect rectGetText;
	rectGetText.nWidth = 10;
	rectGetText.nHeight = 1;
	rectGetText.X = 4;
	rectGetText.Y = 12;
	consoleUI.setControlRect(&btGetText, rectGetText, false);
	btGetText.setClickedEvent(onGetTextClick);
	consoleUI.addEvent(&btGetText);
	consoleUI.addControl(&btGetText);

	///////////////////////Loop event////////////////////
	for (; !bExit;)
	{
		//用redraw和startLoopEvent启动新界面
		consoleUI.redraw();
		consoleUI.startLoopEvent();
	}

	return 0;
}

void LegacyGUI::DisPlayDemo()
{
	PlayDemo(0, nullptr);
}
