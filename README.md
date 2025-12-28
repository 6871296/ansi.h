# `ansi.hpp`
[English](https://github.com/6871296/ansi.hpp/blob/main/README.md#English)

`ansi.hpp`是为了优化在终端模拟器中常用的**ANSI转义码**而生的。
>你在终端里见到的几乎所有彩色文本、格式文本、等等，都在使用ANSI转义码。

ANSI转义码已经被广泛使用，但其相当复杂，且C/C++还没有只简化ANSI转义码的头文件，一般都需要系统API，所以写了这个头文件。
## 为什么是`ansi.hpp`?
与ANSI列个表对比一下。未全部列出。

|ANSI功能                 |`ansi.hpp`功能|说明       |
|------------------------|--------------|----------|
|`\033[0m`               |`reset`       |默认文本格式|
|`\033[1m`               |`bold`        |加粗       |
|`\033[2m`               |`lite`        |暗淡       |
|`\033[38;2;<R>;<G>;<B>m`|`fg(r,g,b)`   |设置文本颜色|
## 完整功能列表
`using namespace std::ansi;`
| 功能名称 | 功能描述 |
|---------|---------|
| `ANSI_SUPPORT_LEVEL` | ANSI 支持级别检测|
| `reset`| 重置所有 ANSI 属性到默认值 |
| `bold`| 设置文本为粗体 |
| `lite`| 设置文本为浅色/半亮 |
| `italic`| 设置文本为斜体 |
| `underline`| 添加下划线 |
| `blink`| 设置文本为慢速闪烁 |
| `quickblink` | 设置文本为快速闪烁 |
| `reverse` | 反转前景色和背景色 |
| `conceal` | 隐藏文本（用于密码输入等场景） |
| `strike` | 添加删除线 |
| `fg(uint8_t c)` | 设置前景色（256色模式，参数为颜色索引） |
| `fg(uint8_t r,uint8_t g,uint8_t b)` | 设置前景色（RGB模式，参数为红绿蓝分量） |
| `bg(uint8_t c)` | 设置背景色（256色模式，参数为颜色索引） |
| `bg(uint8_t r,uint8_t g,uint8_t b)` | 设置背景色（RGB模式，参数为红绿蓝分量） |
| `cursor_pos(int x,int y)` | 移动光标到指定位置（x列，y行） |
| `cursor_up` | 光标上移一行 |
| `cursor_down` | 光标下移一行 |
| `cursor_left` | 光标左移一列 |
| `cursor_right` | 光标右移一列 |
| `cursor_save` | 保存当前光标位置 |
| `cursor_restore` | 恢复之前保存的光标位置 |
| `clear(int n)` | 清除屏幕（n=0:从光标到屏幕末尾，n=1:从屏幕开始到光标，n=2:整个屏幕） |
| `clear_line(intn)` | 清除行（n=0:从光标到行末，n=1:从行首到光标，n=2:整行） |
| `chace_swap` | 切换到备用屏幕缓冲区 |
| `chace_restore` | 切换回主屏幕缓冲区 |
| `hide_cursor` | 隐藏光标 |
| `show_cursor` | 显示光标 |
之后会补充ANSI的读取类功能（这在C++界可是史无前例的！）
### 关于级别检测
`ANSI_SUPPORT_LEVEL`的值可能有以下三种：
```cpp
namespace std::ansi::ANSI_SUPPORT_LEVELS
{
	const CLASS_ANSI_SUPPORT_LEVEL NO_ANSI;//不支持ANSI
	const CLASS_ANSI_SUPPORT_LEVEL FIXED_ANSI;//终端默认不支持ANSI，修改设置后支持
	const CLASS_ANSI_SUPPORT_LEVEL FULL_ANSI;//支持ANSI
}
```
# English
`ansi.hpp` was born for optimizing **ANSI escape codes**.
>About all of colored text you see in the terminal uses ANSI!

ANSI is now widely used, but it's very complicated, and C/C++ does not currently have any header that just simplifies ANSI(Many of them still needs system API), so i've written this header file.
## Why `ansi.hpp`?
Here's a compare with ANSI. Not all of them.

|ANSI function           |`ansi.hpp`function|info       |
|------------------------|------------------|----------|
|`\033[0m`               |`reset`           |default font|
|`\033[1m`               |`bold`            |bold       |
|`\033[2m`               |`lite`            |make the text more darker|
|`\033[38;2;<R>;<G>;<B>m`|`fg(r,g,b)`       |set text color|

## Full function list
`using namespace std::ansi;`
| Feature Name | Description |
|--------------|-------------|
| `ANSI_SUPPORT_LEVEL`| ANSI support level detection (NO_ANSI/FIXED_ANSI/FULL_ANSI) |
| `reset` | Reset all ANSI attributes to default values |
| `bold` | Set text to bold |
| `lite` | Set text to light/faint |
| `italic` | Set text to italic |
| `underline` | Add underline |
| `blink` | Set text to slow blinking |
| `quickblink` | Set text to rapid blinking |
| `reverse` | Reverse foreground and background colors |
| `conceal` | Hide text (for password input scenarios) |
| `strike` | Add strikethrough |
| `fg(uint8_t c)` | Set foreground color (256-color mode, parameter is color index) |
| `fg(uint8_t r,uint8_t g,uint8_t b)` | Set foreground color (RGB mode, parameters are red, green, blue components) |
| `bg(c)` | Set background color (256-color mode, parameter is color index) |
| `bg(r,g,b)` | Set background color (RGB mode, parameters are red, green, blue components) |
| `cursor_pos(int x,int y)` | Move cursor to specified position (x column, y row) |
| `cursor_up` | Move cursor up one line |
| `cursor_down` | Move cursor down one line |
| `cursor_left` | Move cursor left one column |
| `cursor_right` | Move cursor right one column |
| `cursor_save` | Save current cursor position |
| `cursor_restore` | Restore previously saved cursor position |
| `clear(int n)` | Clear screen (n=0: from cursor to end of screen, n=1: from start of screen to cursor, n=2: entire screen) |
| `clear_line(int n)` | Clear line (n=0: from cursor to end of line, n=1: from start of line to cursor, n=2: entire line) |
| `chace_swap` | Switch to alternate screen buffer |
| `chace_restore` | Switch back to main screen buffer |
| `hide_cursor` | Hide cursor |
| `show_cursor` | Show cursor |
Will add ANSI's fetching functions, whch is unprecedented in the history!
### About support level detection
There's 3 possible values for `ANSI_SUPPORT_LEVEL`:
```cpp
namespace std::ansi::ANSI_SUPPORT_LEVELS
{
	const CLASS_ANSI_SUPPORT_LEVEL NO_ANSI;//Not support ANSI
	const CLASS_ANSI_SUPPORT_LEVEL FIXED_ANSI;//Not have default ANSI support, but useable after changing somme settings
	const CLASS_ANSI_SUPPORT_LEVEL FULL_ANSI;//Support ANSI
}
```