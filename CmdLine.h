#pragma once
#ifndef CMDLINE_H
#define CMDLINE_H
#define CMDNUMBER 16
#define SHORTLEN 4
#define REQUIRE 2
#define REQUIREINT 3
#define MAINUI "Main"
#include "struct.h"
enum wordCmd
{
	Error=0,
	Empty=1,
	Confirm=13,
	Create='c',
	Append='a',
	Insert='i',
	Change='n',
	Delete='d',
	Search='s',
	Find='f',
	Print='p',
	Destroy='e',
	Help='h',
	Locate='l',
	Move='m',
	Quit='q',
	Select= 'o',
	list = 't',
	Deuse = 'u',
	Copy='y'
};
typedef enum wordCmd wordCmd;

static struct 
{
	bool para;
	enum wordCmd word;
	const char Shr[SHORTLEN];
	const char Cmd[CMDLENGTH];
}Cmd[CMDNUMBER]={
{TRUE,Help,"he","help"},
{FALSE,Quit,"qu","quit"},
{REQUIRE,Create,"cre","create"},
{REQUIRE,Select,"sel","select"}, 
{FALSE,list,"ls","list"},
{REQUIRE,Destroy,"de","destroy(x)"},
{TRUE,Append,"app","append"},
{REQUIREINT,Insert,"in","insert"},
{REQUIREINT,Change,"ch","change"},
{REQUIREINT,Delete,"del","delete"},
{REQUIRE,Search,"sea","search"},
{REQUIREINT,Find,"fi","find(x)"},
{FALSE,Print,"pr","print"}, 
{FALSE,Deuse,"deu","deuse(x)"},
{REQUIREINT,Move,"mv","move(x)"},
{REQUIREINT,Copy,"cp","copy(x)"}
};
typedef struct cmdReturn
{
	wordCmd word;
	bool paraAllow;
}cmdReturn;
//check command is correct/ exist
cmdReturn cmdCorrect(const char* cmd);
//read command from terminal then return 
//word type command and parameter
wordCmd scan_Cmd(List* parameter);
//list all command
void cmdList(bool all);
//receive true or false from user
bool confirmUI();
//clear x byte chars from the terminal
void clearChar(int num);
//restore all tables
static List allTables;
int SMDBMain();
//the pointer of table which we are using
static Chain* Using=NULL ;
//Main command function
int CmdMain(wordCmd task, List* parameter);

#endif