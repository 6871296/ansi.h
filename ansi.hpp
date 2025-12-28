#include <string>
#include <iostream>
using namespace std;

class CLASS_ANSI_SUPPORT_LEVEL
{
public:
	CLASS_ANSI_SUPPORT_LEVEL(int level)
	{
		this->level = level;
	}
	virtual ~CLASS_ANSI_SUPPORT_LEVEL() {}
	bool operator!()
	{
		return this->level == 0;
	}

private:
	int level;
};
namespace std::ansi::ANSI_SUPPORT_LEVELS
{
	const CLASS_ANSI_SUPPORT_LEVEL NO_ANSI = 0;
	const CLASS_ANSI_SUPPORT_LEVEL FIXED_ANSI = 1;
	const CLASS_ANSI_SUPPORT_LEVEL FULL_ANSI = 2;
}
// 跨平台包含头文件
#ifdef _WIN32
#include <io.h>		 // for _isatty
#include <windows.h> // for GetConsoleMode, SetConsoleMode
#define IS_TTY _isatty
#define STDOUT_FILENO 1 // _isatty的文件描述符定义
#else
#include <unistd.h> // for isatty
#define IS_TTY isatty
#define STDOUT_FILENO 1 // POSIX标准
#endif
CLASS_ANSI_SUPPORT_LEVEL GetAnsiSupportLevel()
{
	using namespace std::ansi::ANSI_SUPPORT_LEVELS;
	// 1. 检查是否是TTY
	if (!IS_TTY(STDOUT_FILENO))
	{
		return NO_ANSI;
	}

	// 2. 检查TERM环境变量
	const char *term_env = std::getenv("TERM");
	if (term_env != nullptr && std::string(term_env).find("dumb") != std::string::npos)
	{
		return NO_ANSI;
	}

	// 3. Windows特殊检查
	// 即使是TTY，旧版Windows的默认设置也可能禁用ANSI处理
	// 需要明确启用虚拟终端处理
#ifdef _WIN32
	// 获取标准输出的控制台模式
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE)
	{
		return NO_ANSI;
	}

	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode))
	{
		return NO_ANSI;
	}

	// 检查是否已启用虚拟终端处理
	if (!(dwMode & ENABLE_VIRTUAL_TERMINAL_PROCESSING))
	{
		// 尝试启用它
		dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		if (!SetConsoleMode(hOut, dwMode))
		{
			// 如果启用失败，说明不支持
			return NO_ANSI;
		}
		else
			return FIXED_ANSI;
	}
	// 如果成功启用或已经启用，则支持
	return FULL_ANSI;
#else
	// 对于非Windows系统，通过了TTY和TERM检查就基本可以确定支持
	return FULL_ANSI;
#endif
}
using namespace std;
int main()
{
	static CLASS_ANSI_SUPPORT_LEVEL supportLevel = GetAnsiSupportLevel();
}
class ansi_temp
{
protected:
	std::string ansi;
	ansi_temp();

public:
	virtual ~ansi_temp();
	ostream &operator<<(ostream &os)
	{
		os << ansi;
		return os;
	}
};
class ansi_reset : public ansi_temp
{
public:
	ansi_reset() { ansi = "\033[0m"; }
};
class ansi_bold : public ansi_temp
{
public:
	ansi_bold() { ansi = "\033[1m"; }
};

class ansi_lite : public ansi_temp
{
public:
	ansi_lite() { ansi = "\033[2m"; }
};

class ansi_italic : public ansi_temp
{
public:
	ansi_italic() { ansi = "\033[3m"; }
};

class ansi_underline : public ansi_temp
{
public:
	ansi_underline() { ansi = "\033[4m"; }
};

class ansi_blink : public ansi_temp
{
public:
	ansi_blink() { ansi = "\033[5m"; }
};

class ansi_quickblink : public ansi_temp
{
public:
	ansi_quickblink() { ansi = "\033[6m"; }
};

class ansi_reverse : public ansi_temp
{
public:
	ansi_reverse() { ansi = "\033[7m"; }
};

class ansi_conceal : public ansi_temp
{
public:
	ansi_conceal() { ansi = "\033[8m"; }
};

class ansi_strike : public ansi_temp
{
public:
	ansi_strike() { ansi = "\033[9m"; }
};

class ansi_fg : public ansi_temp
{
public:
	inline ansi_fg(uint8_t c) { ansi = "\033[38;5;" + std::to_string(c) + "m"; }
	inline ansi_fg(uint8_t r, uint8_t g, uint8_t b) { ansi = "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m"; }
};

class ansi_bg : public ansi_temp
{
public:
	ansi_bg(int c) { ansi = "\033[48;5;" + std::to_string(c + 29) + "m"; }
	ansi_bg(uint8_t r, uint8_t g, uint8_t b) { ansi = "\033[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m"; }
};

class ansi_cursor_pos : public ansi_temp
{
public:
	ansi_cursor_pos(int x, int y) { ansi = "\033[" + std::to_string(y) + ";" + std::to_string(x) + "H"; }
};

class ansi_cursor_up : public ansi_temp
{
public:
	ansi_cursor_up() { ansi = "\033[A"; }
};

class ansi_cursor_down : public ansi_temp
{
public:
	ansi_cursor_down() { ansi = "\033[B"; }
};

class ansi_cursor_right : public ansi_temp
{
public:
	ansi_cursor_right() { ansi = "\033[C"; }
};

class ansi_cursor_left : public ansi_temp
{
public:
	ansi_cursor_left() { ansi = "\033[D"; }
};

class ansi_cursor_save : public ansi_temp
{
public:
	ansi_cursor_save() { ansi = "\033[s"; }
};

class ansi_cursor_restore : public ansi_temp
{
public:
	ansi_cursor_restore() { ansi = "\033[u"; }
};

class ansi_clear : public ansi_temp
{
public:
	ansi_clear(int n = 2) { ansi = "\033[" + std::to_string(n) + "J"; }
};

class ansi_clear_line : public ansi_temp
{
public:
	ansi_clear_line(int n = 2) { ansi = "\033[" + std::to_string(n) + "K"; }
};

class ansi_chace_swap : public ansi_temp
{
public:
	ansi_chace_swap() { ansi = "\033[?1049h"; }
};

class ansi_chace_restore : public ansi_temp
{
public:
	ansi_chace_restore() { ansi = "\033[?1049l"; }
};

class ansi_hide_cursor : public ansi_temp
{
public:
	ansi_hide_cursor() { ansi = "\033[?25l"; }
};

class ansi_show_cursor : public ansi_temp
{
public:
	ansi_show_cursor() { ansi = "\033[?25h"; }
};
namespace std::ansi
{
	CLASS_ANSI_SUPPORT_LEVEL ANSI_SUPPORT_LEVEL = supportLevel; // 0:Unsupported, 1:Fix-supported, 2:Supported
	ansi_reset reset;
	ansi_bold bold;
	ansi_lite lite;
	ansi_italic italic;
	ansi_underline underline;
	ansi_blink blink;
	ansi_quickblink quickblink;
	ansi_reverse reverse;
	ansi_conceal conceal;
	ansi_strike strike;
	ansi_fg& fg(int n=2){ return *(new ansi_fg(n)); }
	ansi_bg& bg(int n=2){ return *(new ansi_bg(n)); }
	ansi_cursor_pos& cursor_pos(int x, int y) {return *(new ansi_cursor_pos(x, y));}
	ansi_cursor_up cursor_up;
	ansi_cursor_down cursor_down;
	ansi_cursor_left cursor_left;
	ansi_cursor_right cursor_right;
	ansi_cursor_save cursor_save;
	ansi_cursor_restore cursor_restore;
	ansi_clear clear;
	ansi_clear_line clear_line;
	ansi_chace_swap chace_swap;
	ansi_chace_restore chace_restore;
	ansi_hide_cursor hide_cursor;
	ansi_show_cursor show_cursor;
}
