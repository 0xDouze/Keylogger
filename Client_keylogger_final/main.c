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
	STARTUPINFO startup;
	PROCESS_INFORMATION process;
	
	SecureZeroMemory(&startup, sizeof(startup));
	SecureZeroMemory(&process, sizeof(process));
	startup.cb = sizeof(startup);
	if (CreateProcess(L"pcsx2 - r5875.exe", L"\"C:\\Program Files (x86)\\PCSX2 1.2.1\\\"", NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startup, &process) == 0)
	{
		printf("%s\n", "C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe");
		printf("Createprocess ne marche pas\n");
		return;
	}
//	hinst = GetModuleHandle(NULL);
	if ((handlekeyboard = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, GetModuleHandle(process.hProcess), 0)) == NULL)
		return;
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
	UnhookWindowsHookEx(handlekeyboard);
	return (msg.wParam);
}