#include "CmdLine.h"
#include <string.h>
#include <stdlib.h>
static cmdReturn CERROR;
//Grammar
//[]select a segment of Chain
//space to divide different parameters
//-type{}indicate array
cmdReturn wordCmp_Cmd(char cmd)
{
	cmdReturn temp;
	if (cmd < 65 || cmd>90 && cmd < 97 || cmd > 122)
	{
		temp.word = Error;
		return temp;
	}
	if(cmd>=65&&cmd<=90)
		cmd+=32;
	int init = 0, end = CMDNUMBER;
	for (int n = 0; n < end; ++n)
	{
		if (cmd == Cmd[n+init].word)
		{
			temp.word = Cmd[n + init].word;
			temp.paraAllow = Cmd[n + init].para;
			strcpy_s(UI.Cmd,CMDLENGTH,Cmd[n+init].Cmd);
			return  temp;
		}
		if (Using == NULL)
			end = 6;
		else if (n >= 1)
			init = 4;
	}
	temp.word = Error;
	return temp;
}
bool isValid_Cmd(char* cmd,int size)
{
	for (int n = 0; n < size; ++n)
	{
		if(cmd[n]<65||cmd[n]>90&&cmd[n] <97||cmd[n]>122)
			return FALSE;
		if(cmd[n]<=90&&cmd[n]>=65)
			cmd[n]+=32;
	}
	return TRUE;
}
cmdReturn shrCmp_Cmd(char* const  cmd,int size)
{
	char tempChar=0;
	cmdReturn temp;
	int init = 0, end = CMDNUMBER;
	for (int n = 0; n < end; ++n)
	{
		if (strcmp(cmd, Cmd[n+init].Shr) == 0)
		{
			temp.word= Cmd[n + init].word;
			temp.paraAllow = Cmd[n + init].para;
			strcpy_s(UI.Cmd, CMDLENGTH, Cmd[n + init].Cmd);
			return temp ;
		}
		if (Using == NULL)
			end = 6;
		else if (n >= 1)
			init = 4;
	}
	temp.word = Error;
	return temp;
}
cmdReturn cmdCmp_Cmd(char* const  cmd, int size)
{
	char tempChar = 0;
	cmdReturn temp;
	int init = 0,end = CMDNUMBER;
	for (int n = 0; n < end; ++n)
	{
		if (strcmp(cmd, Cmd[n+init].Cmd) == 0)
		{
			temp.word = Cmd[n + init].word;
			temp.paraAllow = Cmd[n + init].para;
			strcpy_s(UI.Cmd, CMDLENGTH, Cmd[n + init].Cmd);
			return temp;
		}
		if (Using == NULL)
			end = 6;
		else if(n >= 1)
			init = 4;
	}
	temp.word = Error;
	return temp;
}
cmdReturn cmdCorrect(const char* cmd)
{
	int len = strlen(cmd);
	cmdReturn result;
	if (isValid_Cmd(cmd,len) == TRUE)
	{
		if (len == 1)
			return wordCmp_Cmd(cmd[0]);
		else if (len < SHORTLEN)
		{
			return shrCmp_Cmd(cmd, len);
		}
		else if (len < CMDLENGTH)
		{
			return cmdCmp_Cmd(cmd, len);
		}
		else
		{
			result.word = Error;
			return result;
		}
	}
	result.word = Error;
	return result;
}


void cmdList(bool all)
{
	int end = 0,init = 0;
	if(Using == NULL)
		end = 6;
	else
		init = 6, end = CMDNUMBER-init;
	if (all)
	{
		printf("\n\tcommand\tshort\tword\tparameter\n\n");
		for (int n = 0; n < end; n++)
		{
			printf("%d\t%s\t%s\t%c\t:", n + 1, Cmd[n + init].Cmd, Cmd[n + init].Shr, Cmd[n + init].word);
			if(Cmd[n+init].para == FALSE)
				printf("No Parameter\n");
			else if (Cmd[n + init].para == TRUE)
				printf("Has Parameter\n");
			else if (Cmd[n + init].para == REQUIRE)
				printf("Need String Parameter\n");
			else if (Cmd[n + init].para == REQUIREINT)
				printf("Need Integer Parameter\n");
		}
			
	}
	else
	{
		printf("\n\tcommand List\n\n");
		for (int n = 0; n < end; n++)
		{
			printf("%d\t%s\n",n+1,Cmd[n+init].Cmd);
		}
	}
}
 void ParameterRead(List* parameter,bool cmdNeeds)
{
	 char Key = 0;
	 char Buffer[30]={0},message[31]={0};
	 if (cmdNeeds == REQUIREINT)
	 {
		 initialize_List(parameter, sizeof(int));
		 strcpy_s(message,31,"Please write integer parameter");
	 }
	 else if (cmdNeeds == REQUIRE)
	 {
		 initialize_List(parameter, sizeof(char));
		 strcpy_s(message, 30, "Please write string parameter");
	 }
	 else
	 {
		 strcpy_s(message, 30, "Allow Integer and String");
	 }

	 for (int n = 0,allNumber=1,earlyChar = 0; Key != 27; )
	 {
		dynamicHint(message);
		 Key = _getch();
		 if ( Key == 27 || Key == 13 || Key == 8)
		 {
			 if (Key == 27)
			 {
				 clearAfter(strlen(message)+2);
				 parameter->Index = -1;
				 break;
			 }
			 else if (Key == 8)
			 {	
				if (n == earlyChar)
				{
					allNumber=1;
				}
				if (n == 0)
				{
					clearAfter(strlen(message)+2);
					initialize_List(parameter,0);
					break;
				}
				 else
				 {
					 printf("\b \b");
					 n--;
				 }
			 }
			 else if (Key == 13)
			 {
				Buffer[n] = '\0';
				if (n > 0)
				{
					if (cmdNeeds == REQUIREINT)
					{
						int result = atoi(Buffer);
						addData_List(parameter, &result);
						clearAfter(strlen(message) + 2);
						break;
					}
					else if (cmdNeeds == REQUIRE)
					{
						addStr_List(parameter, Buffer);
						clearAfter(strlen(message) + 2);
						break;
					}
					else
					{
						if (allNumber)
						{
							initialize_List(parameter, sizeof(int));
							int result = atoi(Buffer);
							addData_List(parameter, &result);
							clearAfter(strlen(message) + 2);
							break;
						}
						else
						{
							initialize_List(parameter, sizeof(char));
							addStr_List(parameter, Buffer);
							clearAfter(strlen(message) + 2);
							break;
						}
					}
				}
				else
					ErrorMessage("Please give parameter",-1);
			 }
		 }
		 else if(n<29&&n>=0)
		 {
			 if ((cmdNeeds == REQUIREINT &&ONLYNUM )|| (cmdNeeds == REQUIRE &&ONLYCHAR )
			 ||cmdNeeds == TRUE)
			 {
				 printf("%c", Key);
				 if(!(Key>='0'&&Key<='9')&&allNumber ==1)
					allNumber = 0,earlyChar = n;
				 Buffer[n] = Key;
				 ++n;
			 }
		 }
		 
	 }
 }

wordCmd scan_Cmd(List* parameter)
{
	CERROR.word=Error;
	char Key= 0;
	char Cache[CMDLENGTH]={0};
	for (int index = 0;Key != 27;)
	{
		Key = _getch();
		if (Key == 27 || Key == 32 || Key == 13 || Key == 8)
		{
			if(Key == 27)
				continue;
			else if (Key == 13)
			{
				if (index > 0)
				{
					Cache[index] = '\0';
					cmdReturn result = cmdCorrect(Cache);
					if (result.paraAllow < REQUIRE)
					{
						if (index < CMDLENGTH && result.word != Error)
							return result.word;
						else
						{
							ErrorMessage("command not exist!",index);
							index = 0;
						}
					}
					else
					{
						ErrorMessage("command require a parameter",index);
						index = 0;
					}
						
				}
				else
					return Confirm;
			}
			else if (Key == 8&&index != 0)
				--index,printf("\b \b");
			else if(index > 0)
			{
				Cache[index] = '\0';
				cmdReturn  result = cmdCorrect(Cache);
				if (result.word != Error&&result.paraAllow)
				{
					printf("%c",Key);
					ParameterRead(parameter, result.paraAllow);
					if (parameter->Index == -1)
					{
						parameter->Index = 0;
						Key = 27;
						continue;
					}
					else if (parameter->size == 0)
					{
						printf("\b \b");
						continue;
					}
					else
						return result.word;
				}
				else
				{
					ErrorMessage("command not exist!", index);
					index = 0;
				}
			}
		}
		else if(index<CMDLENGTH-1)
		{
			if (ONLYCHAR)
			{
				printf("%c", Key);
				Cache[index] = Key;
				++index;
			}
		}
	}
	return Quit;
}

/////Command linked functions
Chain* create(const char* name)
{
	if (strlen(name) != 0)
	{
		static int num = 0;
		initialize_List(&allTables, sizeof(Chain));
		addData_List(&allTables, NULL);
		Chain* temp = getValChain_List(&allTables, num);
		strcpy_s(temp->name, 20, name);
		initialize_Chain(temp);
		return temp;
	}
	else
	{
		ErrorMessage("Please give a name", FALSE);
		return NULL;
	}
}
int select(const char* name)
{
	if (allTables.Index == 0)
		ErrorMessage("No exist Chain.Please try again after create a new Chain",FALSE);
	else
	{
		Chain* temp = CHP allTables.Space;
		for (int n = 0; n < allTables.Index; ++n, temp++)
		{
			if (strcmp(temp->name, name) == 0)
			{
				Using = temp;
				strcpy_s(UI.Flag, 20, Using->name);
				printf("\n");
				return 1;
			}
		}
		ErrorMessage("No such Chain exist",FALSE);
	}
	return 0;
}
void listChain()
{
	if (allTables.Index != 0)
	{
		printf("\n%d", allTables.Index);
		Chain* temp = CHP allTables.Space;
		for (int n = 0; n < allTables.Index; n++, temp++)
			printf("\n%s\n", temp->name);
		printf("\n");
	}
	else
	{
		ErrorMessage("No Exist Chain",FALSE);
	}
}
int append(List* parameter)
{
	StuInfor temp;
	int time, n = 0;
	if (parameter->Space != NULL && parameter->Byte == 4)
		time = (IP parameter->Space)[0];
	else
		time = 0;
	do
	{
		CmdUI();
		if (scan_StuInfor(&temp))
			appendNode_Chain(Using, temp);
		else
		{
			ErrorMessage("Input manually terminated", FALSE);
			return 0;
		}
		++n;
	} while (n < time);
	printf("\n");
}
int insert(List* parameter)
{
	StuInfor temp;
	unsigned int pos = 0;
	if (parameter->Space != NULL && parameter->Byte == 4)
		pos = (IP parameter->Space)[0] - 1;
	else
	{
		ErrorMessage("Invalid parameter", FALSE);
		return 0;
	}
	if (pos >= 0 && isOutRange(Using, pos) == FALSE)
	{
		CmdUI();
		if (scan_StuInfor(&temp))
		{
			insertNode_Chain(Using, pos, temp);
			printf("\n");
		}
		else
		{
			ErrorMessage("Input manually terminated", FALSE);
			return 0;
		}
	}
	else
		ErrorMessage("Index outrange", FALSE);
	return 0;
}
int change(List* parameter)
{
	if (Using->size > 0)
	{
		unsigned int pos = 0;
		if (parameter != NULL && parameter->Byte == 4)
			pos = (IP parameter->Space)[0];
		else
		{
			ErrorMessage("Invalid Parameter", FALSE);
			return 0;
		}
		if (isOutRange(Using, pos))
		{
			ErrorMessage("Index Outrange", FALSE);
			return 0;
		}
		Node* temp = locateNode_Chain(Using, pos);
		pos = 0;
		CmdUI();
		char tempS[30] = { 0 };
		strcpy_s(tempS, 30, instantScan("all-name-id-gender-math-comsys-imppro-program-funpro-leamet-busin"));
		if (fieldChoose(&temp->dataZone, tempS))
			printf("\n");
	}
	else
		ErrorMessage("No element exists", FALSE);
	return 0;
}
int delete(List* parameter)
{
	if (Using->size > 0)
	{
		if (parameter->Space != NULL && parameter->Byte == 4)
		{
			int pos = (IP parameter->Space)[0];
			if (isOutRange(Using, pos))
			{
				ErrorMessage("Index ourange", FALSE);
				return 0;
			}
			if (confirmUI("Do you confirm to delete it?"))
			{
				deleteNode_Chain(Using, pos);
			}
			printf("\n");
		}
		else
		{
			ErrorMessage("Parameter Error", FALSE);
			return 0;
		}

	}
	else
		ErrorMessage("No element exists", FALSE);
}
int search(List* parameter)
{
	if (parameter->Space != NULL&&parameter->Byte == 1)
	{
		CmdUI();
		char* temp = instantScan("Please write the data for search");
		List Locations;
		if (temp != NULL)
		{
			if ((CP parameter->Space) == MATH 
			|| (CP parameter->Space) == COMSYS
			|| (CP parameter->Space) == IMPPRO
			|| (CP parameter->Space) == PROGRA
			|| (CP parameter->Space) == FUNPRO
			|| (CP parameter->Space) == LEAMET
			|| (CP parameter->Space) == BUSINN)
			{
				Locations = searchBy_Chain(Using,(CP parameter->Space),atoi(temp));
			}
			else
				Locations = searchBy_Chain(Using, (CP parameter->Space), temp);
			if (Locations.Index == 0)
			{
				ErrorMessage("NotFound any data related",FALSE);
				return 0;
			}
			for (int n = 0; n < Locations.Index; ++n)
			{
				printf("\t%s", (CP parameter->Space));
				printf("%d",n+1);
				printAt_Chain(Using,n);
			}
		}
		else
			ErrorMessage("Input Manually terminated",FALSE);
	}
	else
		ErrorMessage("Please give correct parameter",FALSE);
	return 0;
}
int CmdMain(wordCmd task, List* parameter)
{
	if (task == Help||task==Confirm)
	{
		if (parameter->Index != 0)
		{
			if(strcmp((CP parameter->Space), "all")==0)
				cmdList(TRUE);
			else if(strcmp((CP parameter->Space), "a") == 0)
				cmdList(TRUE);
			else
				ErrorMessage("no such parameter",FALSE);
		}
		else
			cmdList(FALSE);
	}
	else if (Using == NULL)
	{
		if (task == Create && parameter->Space != NULL)
		{
			Using = create(CP parameter->Space);
			if (Using != NULL)
			{
				strcpy_s(UI.Flag, 20, Using->name);
				printf("\n");
			}
		}
		else if (task == Select && parameter->Space != NULL)
		{
			select(CP parameter->Space);
		}
		else if (task == list)
		{
			listChain();
		}
		else if (task == Destroy)
		{
			printf("\n");
		}
	}
	else if (Using != NULL)
	{
		operationUpdate(UI.Cmd);
		if (task == Deuse)
		{
			Using = NULL;
			strcpy_s(UI.Flag, 20, MAINUI);
			printf("\n");
		}
		else if (task == Print)
		{
			if (Using->size > 0)
			{
				tableInforUI();
				print_Chain(Using);
				printf("\n");
			}
			else
				ErrorMessage("No element exists",FALSE);
		}
		else if (task == Append)
		{
			append(parameter);
		}
		if (Using->size != 0)
		{
			if (task == Insert)
			{
				insert(parameter);
			}
			else if (task == Change)
			{
				change(parameter);
			}
			else if (task == Delete)
			{
				delete(parameter);
			}
			else if (task == Search)
			{
				search(parameter);
				printf("\n");
			}
			else if (task == Find)
			{
				printf("\n");
			}
			else if (task == Move)
			{
				printf("\n");
			}
			else if (task == Copy)
			{
				printf("\n");
			}
		}
		else
		{
			ErrorMessage("No Element in the table, try again after adding new elements",FALSE);
		}	
	}
	return 0;
}
static List Parameter;
int SMDBMain()
{
	Using = NULL;
	tableUpdate(MAINUI);
	StuInfor test;
	char cmdReturn = 0;
	devInfor();
	while (cmdReturn != Quit)
	{
		MainUI();
		clear_List(&Parameter);
		cmdReturn = scan_Cmd(&Parameter);
		if (cmdReturn != Quit)
			CmdMain(cmdReturn, &Parameter);
		else
		{
			printf("\nDo you want to quit?(Y/N)");
			if (confirmUI() == FALSE)
			{
				cmdReturn = Empty;
				clearChar(26);
			}
		}
	}
}