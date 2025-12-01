#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
#ifdef _WIN32
#include <windows.h>
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
DWORD dwMode = 0;
GetConsoleMode(hOut, &dwMode);
dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
SetConsoleMode(hOut, dwMode);
#endif
ANSIstyle currentStyle;
class ANSIstyle
{
private:
	const string style[18] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "21", "22", "23", "24", "25", "26", "27", "28", "29"};

public:
	bool MERGE_CURSOR_POS_USE_ITS = 0, MERGE_WINDOW_SIZE_USE_ITS = 0, MERGE_BG_COLOR_USE_ITS = 0, MERGE_TEXT_COLOR_USE_ITS = 0, MERGE_SETTINGS_USE_ITS = 0;
	int styleFs = 0;
	/*
		styleF(lag)s详解
		0b（17位以上忽略）
		1 \033[1m         // 加粗/增加强度
		2 \033[2m         // 暗淡/降低强度
		3 \033[3m         // 斜体（很少支持）
		4 \033[4m         // 下划线
		5 \033[5m         // 慢速闪烁
		6 \033[6m         // 快速闪烁
		7 \033[7m         // 反显
		8 \033[8m         // 隐藏
		9 \033[9m         // 删除线
		10\033[21m        // 双下划线（很少支持）
		11\033[22m        // 正常强度
		12\033[23m        // 非斜体
		13\033[24m        // 非下划线
		14\033[25m        // 非闪烁
		15\033[27m        // 非反显
		16\033[28m        // 非隐藏
		17\033[29m        // 非删除线
	*/
	pair<long long, long long> cursor_pos;
	pair<long long, long long> window_size;
	uint8_t bg_color[3] = {0, 0, 0}, text_color[3] = {255, 255, 255};
	ostream &operator>>(ostream &os)
	{
		os << "\033[0m";
		for (int i = 0; i < 17; i++)
		{
			if ((styleFs >> i) & 1)
			{
				os << "\033[" + style[i] + "m" << flush;
			}
		}
		os << "\033[38;2;" + to_string(text_color[0]) + ';' + to_string(text_color[1]) + ';' + to_string(text_color[2]) + "m" << "\033[48;2;" + to_string(bg_color[0]) + ';' + to_string(bg_color[1]) + ';' + to_string(bg_color[2]) + "m" << flush;
		currentStyle = *this;
		return os;
	}
	ANSIstyle &operator|(ANSIstyle style1)
	{
		if (MERGE_SETTINGS_USE_ITS)
		{
			MERGE_CURSOR_POS_USE_ITS = style1.MERGE_CURSOR_POS_USE_ITS,
			MERGE_WINDOW_SIZE_USE_ITS = style1.MERGE_WINDOW_SIZE_USE_ITS,
			MERGE_BG_COLOR_USE_ITS = style1.MERGE_BG_COLOR_USE_ITS,
			MERGE_TEXT_COLOR_USE_ITS = style1.MERGE_TEXT_COLOR_USE_ITS,
			MERGE_SETTINGS_USE_ITS = style1.MERGE_SETTINGS_USE_ITS;
		}
		if (MERGE_CURSOR_POS_USE_ITS)
			cursor_pos = style1.cursor_pos;
		if (MERGE_WINDOW_SIZE_USE_ITS)
			window_size = style1.window_size;
		if (MERGE_BG_COLOR_USE_ITS)
			memcpy(bg_color, style1.bg_color, 3);
		if (MERGE_TEXT_COLOR_USE_ITS)
			memcpy(text_color, style1.text_color, 3);
		styleFs |= style1.styleFs;
		return *this;
	}
	ANSIstyle &operator|=(ANSIstyle style1)
	{
		if (MERGE_SETTINGS_USE_ITS)
		{
			MERGE_CURSOR_POS_USE_ITS = style1.MERGE_CURSOR_POS_USE_ITS,
			MERGE_WINDOW_SIZE_USE_ITS = style1.MERGE_WINDOW_SIZE_USE_ITS,
			MERGE_BG_COLOR_USE_ITS = style1.MERGE_BG_COLOR_USE_ITS,
			MERGE_TEXT_COLOR_USE_ITS = style1.MERGE_TEXT_COLOR_USE_ITS,
			MERGE_SETTINGS_USE_ITS = style1.MERGE_SETTINGS_USE_ITS;
		}
		if (MERGE_CURSOR_POS_USE_ITS)
			cursor_pos = style1.cursor_pos;
		if (MERGE_WINDOW_SIZE_USE_ITS)
			window_size = style1.window_size;
		if (MERGE_BG_COLOR_USE_ITS)
			memcpy(bg_color, style1.bg_color, 3);
		if (MERGE_TEXT_COLOR_USE_ITS)
			memcpy(text_color, style1.text_color, 3);
		styleFs |= style1.styleFs;
		return *this;
	}
};
