#pragma once
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

#include "console.hpp"

namespace GraphHelper
{
	static std::string Hline(unsigned int i)
	{
		int ii = 0;
		std::string str;
		for (;;)
		{
			if (ii <= i)
			{
				str += "©¤";
				ii++;
			}
			else
			{
				return str;
			}
		}
	}

	static std::string Hline(unsigned int i, char border)
	{
		int ii = 0;
		std::string str;
		for (;;)
		{
			if (ii <= i)
			{
				str += border;
				ii++;
			}
			else
			{
				return str;
			}
		}
	}

	static std::string Vline(unsigned int i, bool double_p)
	{
		using namespace std;
		string str;
		if (double_p)
		{
			for (int ii = 0; ii <= i * 2; ii++)
			{
				str += "©¦\n";
			}
		}
		else
		{
			for (int ii = 0; ii <= i; ii++)
			{
				str += "©¦\n";
			}
		}
		return str;
	}

	static std::string Vline(unsigned int i, char border, bool double_p)
	{
		using namespace std;
		string str;
		if (!double_p)
		{
			for (int ii = 0; ii <= i * 2; ii++)
			{
				str += border;
				str += "\n";
			}
		}
		else
		{
			for (int ii = 0; ii <= i; ii++)
			{
				str += border;
				str += "\n";
			}
		}
		return str;
	}
	/*{
		if (double_p == false)
		{
			int ii = -1;
			std::string str = "©¦";
			for (;;)
			{
				if (ii <= i)
				{
					str += "\n©¦";
					ii++;
				}
				else
				{
					return str;
				}
			}
		}
		else
		{
			if (i <= 0)
			{
				return "function error!\n";
			}
			int ii = -1;
			int iii = 0;
			std::string strr;
			std::string str = "©¦";
			i *= 6;
			for (;;)
			{
				if (iii <= i)
				{
					strr += " ";
					iii++;
				}
				else
				{
					strr += "©¦\n";
					i /= 6;
					break;
				}
			}
			for (;;)
			{
				if (ii <= i)
				{
					str = str + "\n©¦" + strr;
					ii++;
				}
				else
				{
					return str;
				}
			}
		}
	}*/

	static std::string print_box(unsigned int x, unsigned int y, bool drawCorner = true)
	{
		x = x * 2;
		std::string str_box;
		if (drawCorner)
			str_box = "©°" + Hline(x - 2) + "©´\n" + Vline(y, true) + "\n©¸" + Hline(x - 2) + "©¼";
		else
			str_box = Hline(x) + "\n" + Vline(y, true) + "\n" + Hline(x);
		return str_box;
	}

	static std::string print_box(unsigned int x, unsigned int y, char border, bool drawCorner = true)
	{
		x = x * 2;
		std::string str_box;
		if (drawCorner)
			str_box = "©°" + Hline(x - 2, border) + "©´\n" + Vline(y - 2, border, true) + "\n©¸" + Hline(x - 2, border) + "©¼";
		else
			str_box = Hline(x, border) + "\n" + Vline(y, border, true) + "\n" + Hline(x, border);
		return str_box;
	}

	/*
	class ProgressBar
	{
	private:
		std::string Data;
	public:
		char StartBorder = '[';
		char EndBorder = ']';
		char Checked = '*';
		char UnChecked = '-';
		int Width = 10;
		bool AutoUpdate = true;

		// Init
		ProgressBar(){
			Data = "";
			Data.append(_StartBorder);
			for(int i = 0; i <= Width - 2; i++)
				Data.append(UnChecked);
			Data.append(EndBorder);
		}

		// Set Border Function
		void SetBorder(char _StartBorder, char _EndBorder){
			StartBorder = _StartBorder;
			EndBorder = _EndBorder;
		}
		void SetStartBorder(char Border){
			StartBorder = Border;
		}
		void SetEndBorder(char Border){
			EndBorder = Border;
		}

		// Display
		void Update(){
			Data = "";
			Data.append(StartBorder);
			for(int i = 0; i <= Width - 2; i++)
				Data.append(UnChecked);
			Data.append(EndBorder);
		}
		void Display(){
			if (AutoUpdate) Update();
			std::cout << Data << std::flush;
		}
	};
	*/

	class GraphHelper
	{
	private:
		class controls
		{
		public:
			int TextC = -1;
			std::string Text[256];
			void AddText(std::string _Text)
			{
				TextC++;
				Text[TextC] = _Text;
			}
			void RemoveText()
			{
				TextC--;
			}

			int ListC = -1;
			int SeletedColor;
			int UnseletedColor;
			std::vector<std::string> List;
			void AddListItem(std::string Item)
			{
				ListC++;
				List.push_back(Item);
			}
			void AddList(std::vector<std::string> list)
			{
				// ListC = list.size();
				List.assign(list.begin(), list.end());
			}
		};

		unsigned int Width, Height;
		char Border;
		std::string gui = "";
		std::string Title;
		bool IsInited = false;
		bool UseCorner = false;
		bool UseLine = false;
		bool flushing = false;

		// int drawpos_x = 0;
		// int drawpos_y = 0;

		void drawControls()
		{
			if (Controls.TextC != -1) // Text
			{
				for (int i = 0; i <= Controls.TextC; i++)
				{
					std::cout << Controls.Text[i] << std::endl;
					printf("\033[1C");
				}
			}

			if (Controls.ListC != -1) // List
			{
				for (int i = 0; i <= Controls.ListC; i++)
				{
					std::cout << Controls.List[i] << std::endl;
					printf("\033[1C");
				}
			}
		}

	public:
		controls Controls;

		int init(unsigned int width, unsigned int height, char border, std::string title = "Gui", bool useCorner = false)
		{
			Width = width;
			Height = height;
			Border = border;
			IsInited = true;
			UseCorner = useCorner;
			UseLine = false;
			Title = title;
			return 0;
		}

		// void SetDrawPos(int X, int Y){ drawpos_x = X; drawpos_y = Y; return; }
		// void GetDrawPos(int *X, int *Y){ *X = drawpos_x; *Y = drawpos_y; return; }

		int init(unsigned int width, unsigned int height, std::string title = "Gui")
		{
			Width = width;
			Height = height;
			IsInited = true;
			UseLine = true;
			UseCorner = true;
			Title = title;
			return 0;
		}

		int flush()
		{
			if (!IsInited)
			{
				std::cerr << std::endl
						  << "GraphHelper Error: Try to draw before init!" << std::endl;
				return 1;
			}

			if (gui != "")
				gui = "";

			/*
			if (UseLine)
			{
				if (UseCorner)
					std::cerr << print_box(Width, Height) << std::flush;
				else
					std::cerr << print_box(Width, Height, false) << std::flush;
			}
			else
			{
				if (UseCorner)
					std::cerr << print_box(Width, Height, Border) << std::flush;
				else
					std::cerr << print_box(Width, Height, Border, false) << std::flush;
			}*/

			flushing = true;

			if (UseCorner)
				gui += "©°";
			else
				gui += Border;
			if (UseLine)
				for (int i = 1; i <= Width - 2; i++)
					gui += "©¤";
			else
				for (int i = 1; i <= Width - 2; i++)
					gui += Border;
			if (UseCorner)
				gui += "©´";
			else
				gui += Border;
			gui += "\n";

			if (UseLine)
				gui += "©À";
			else
				gui += Border;
			std::string title = Title.substr(0, Width - 2);
			gui += title;
			for (int i = 1; i <= Width - 2 - strlen(title.data()); i++)
				gui += " ";
			if (UseLine)
				gui += "©È";
			else
				gui += Border;
			gui += "\n";

			if (UseLine)
			{
				gui += "©À";
				for (int i = 1; i <= Width - 2; i++)
					gui += "©¤";
				gui += "©È\n";
			}
			else
			{
				gui += Border;
				for (int i = 1; i <= Width - 2; i++)
					gui += Border;
				gui += Border;
				gui += "\n";
			}

			if (UseLine)
				for (int i = 1; i <= Height; i++)
				{
					gui += "©¦";
					for (int i = 1; i <= Width - 2; i++)
						gui += " ";
					gui += "©¦\n";
				}
			else
				for (int i = 1; i <= Height; i++)
				{
					gui += Border;
					for (int i = 1; i <= Width - 2; i++)
						gui += " ";
					gui += Border;
					gui += "\n";
				}

			if (UseCorner)
				gui += "©°";
			else
				gui += Border;
			if (UseLine)
				for (int i = 1; i <= Width - 2; i++)
					gui += "©¤";
			else
				for (int i = 1; i <= Width - 2; i++)
					gui += Border;
			if (UseCorner)
				gui += "©´";
			else
				gui += Border;

			flushing = false;
			return 0;
		}

		void SetTitle(std::string title)
		{
			Title = title;
			flush();
		}

		int draw()
		{
			if (!IsInited)
			{
				std::cerr << std::endl
						  << "GraphHelper Error: Try to draw before init!" << std::endl;
				return 1;
			}

			if (flushing)
				return 0;

			// Console::gotoxy(drawpos_x, drawpos_y);
			std::cout << gui << std::endl;
			Console::gotoxy(2, 4);
			drawControls();
			return 0;
		}
	};
}