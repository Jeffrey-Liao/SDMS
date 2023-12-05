#include "main.h"

int main()
{
	SMDBMain();
}
/*
static List allTables;
	StuInfor test1 = { "liaorunkang","FKEP8U",TRUE,{0,0,0,0,0,0,0},3.2 }, test2 = { "liumenghao","dafasU",TRUE,{0,0,0,0,0,0,0},4.5 }, test3 = { "liaorunkang","FKEP8U",TRUE,{0,0,0,0,0,0,0},3.2 };
	initialize_List(&allTables,sizeof(Chain));
	addData_List(&allTables,NULL);
	Chain* temp  = getValChain_List(&allTables,0);
	initialize_Chain(temp);
	appendNode_Chain(temp, test1);
	appendNode_Chain(temp, test2);
	appendNode_Chain(temp, test3);
	print_Chain(&temp);
	clear_List(&allTables);*/