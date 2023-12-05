#pragma once
#ifndef UI_H
#define UI_H
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#define TRUE 1
#define FALSE 0
#define ERROR -1
#define CMDLENGTH 15
#define NAMESIZE 30
#define ONLYCHAR ( (65 <= Key && Key <= 90)||(97 <= Key && Key <= 122))
#define ONLYNUM ( 48 <= Key && Key <= 57)
#define VERSION "v.0.1-23-080-debug"
#define UPDATE "2023-Dec-04-Hungary-Liao Runkang"
//the name of table which we are using
typedef char bool;
typedef char oneByte;
struct 
{
	const char Flag[NAMESIZE];
	const char Cmd[CMDLENGTH];
	int RunTime;
}UI;
static void devInfor()
{
	printf("version: %s | last update infor: %s\n", VERSION,UPDATE);
}
static void clearChar(int num)
{
	for (int n = 0; n < num; ++n)
		printf("\b \b");
}
static void clearAfter(int size)
{
	for (int n = 0; n < size; n++)
		printf(" ");
	for (int n = 0; n < size; n++)
		printf("\b");
}
static bool confirmUI()
{
	char Key = _getch();
	if (Key == 27 || Key == 'n' || Key == 'N')
		return FALSE;
	else
		return TRUE;
}
static void dynamicHint(const char* string)
{
	if (string != NULL)
	{
		int len = 15;
		printf("--%s             ", string);
		len += strlen(string);
		for (int n = 0; n < len; ++n)
			printf("\b");
	}
}
static char ErrorMessage(const char* message, int Inline)
{
	if (message != NULL)
	{
		char c = 0;
		if (Inline == 0)
			printf("\n");
		else if (Inline > 0)
			clearChar(Inline);
		printf("%s(Press any key to continue)", message);
		c = _getch();
		clearChar(strlen(message) + 27);
		return c;
	}
	return 0;
}
static void MainUI()
{
	printf("%s::", UI.Flag);
	UI.RunTime++;
}
static void tableUpdate(const char* string)
{
	strcpy_s(UI.Flag, NAMESIZE, string);
}
static void CmdUI()
{
	printf("\n%s->%s::", UI.Flag, UI.Cmd);
	UI.RunTime++;
}
static void operationUpdate(const char* string)
{
	strcpy_s(UI.Cmd, CMDLENGTH, string);
}
static void tableInforUI()
{
	printf("\n\tname\tID\tGender\tMath\tCom\tIP\tP\tFP\tLM\tB\tGPA\n");
}
#endif