#include "keylogger.h"

HINSTANCE hinst;
static HHOOK handlekeyboard = NULL;

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wparam, LPARAM lparam)
{
	printf("i pressed a key!\n");
	return (CallNextHookEx(handlekeyboard, nCode, wparam, lparam));
}

void	setwinhook()
{
	handlekeyboard = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
	if (handlekeyboard == NULL)
		printf("c'est nul\n");
	else
		printf("c'est pas nul\n");
	printf("coucou\n");
}

int	main(void)
{
	setwinhook();
	return (0);
}