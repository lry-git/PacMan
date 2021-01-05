#include<Windows.h>
#include"config.h"
void Config:: gotoxy(int x, int y) {// x is the column, y is the row
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄 
	SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置 
	//CloseHandle(hOut);
}
bool Config:: setConsoleColor(short wAttributes) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE)
		return FALSE;
	bool bResult = SetConsoleTextAttribute(hConsole, wAttributes);
	return bResult;
}

void Config:: clrscr(void) //clearscreen: gesamten Bildschirm leeren
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; //variablendklaration
	HANDLE hConsoleOut;
	COORD Home = { 0,0 };
	DWORD dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy); //bis cursorposition leerzeichen ausgeben
	csbiInfo.dwCursorPosition.X = 0; //cursorposition X koordinate festlegen
	csbiInfo.dwCursorPosition.Y = 0; //cursorposition Y koordinate festlegen
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition); //den cursor an die festgelegte koordinate setzen
}