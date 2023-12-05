#pragma once
#include"UI.h"
#ifndef STRUCT_H
#define STRUCT_H
#define FNAME "name"
#define FID "ID"
#define FGENDER "gender"
#define FGRADE "grade"
#define FGPA "GPA"

#define MATH "math"
#define COMSYS "comsys"
#define IMPPRO "imppro"
#define PROGRA "program"
#define FUNPRO "funpro"
#define LEAMET "leamet"
#define BUSINN "busin"

#define NEWNODE (Node*)malloc(sizeof(Node))
#define NEW(x) malloc(x)
#define NEWT(x) (x*)malloc(sizeof(x))
#define DEL(x) free(x)

#define INC(x) (x = x->next)
#define ARRASSIGN(x,y,size) for(int n =0;n<size;++n) x[n] = y[n]
#define ASINT *(int*)
#define ASCHAR *(char*)
#define ASDOUBLE *(double*)
#define ASNODE *(Node*)
#define ASSTUINF *(StuInfor*)
#define ASCHAIN *(Chain*)
#define INDTYPE unsigned int
#define IP (int*)
#define CP (char*)
#define FP (float*)
#define DP (double*)
#define NP (Node*)
#define CHP (Chain*)

#define IDSIZE 12

typedef struct Field
{
	void* Space;
	const char* name;
}Field;

typedef struct StuInfor
{
	char name[NAMESIZE];
	char ID[12];
	bool isMan;
	int Grade[7];
	double GPA;
}StuInfor;
typedef struct Dstruct
{
	Field* Data;
}Dstruct;
void dynamicHint(const char* string);
char* instantScan(const char* message);
StuInfor asStuInfor(char name[NAMESIZE],char ID[12],bool isMan,int Grade[7],double GPA);
bool cmpStuInfor(const StuInfor obj1, const StuInfor obj2);
void tofile_StudInfor(StuInfor* this,FILE* Path);
StuInfor fromFile_StudInfor(FILE* Path);
int scan_StuInfor(StuInfor* this);
void print_StuInfor(StuInfor* this);
typedef struct List
{
	void* Space;
	oneByte Byte;
	int Index;
	int size;
}List;
void addData_List(List* this, void* data);
void initialize_List(List* this,oneByte byteSize);
int getValInt_List(List* this,INDTYPE pos);
double getValDouble_List(List* this, INDTYPE pos);
void addStr_List(List* this, char* data);
char* getStr_List(List* this);
void clear_List(List* this);
void deleteEle_List(List* this, INDTYPE pos);
void* getEle_List(List* this, oneByte byteSize, INDTYPE pos);
typedef struct Node
{
	StuInfor dataZone;
	struct Node* next;
}Node;
Node* new_Node(Node* Father, Node* Son, StuInfor newData);
Node* del_Node(Node* this,Node* Father);
int next_Count(Node* this);
bool isEnd(Node* this); 
Node* link_Node(Node* this,Node* newNext);
Node* getValNode_List(List* this, INDTYPE pos);
typedef struct Chain
{
	char name[20];
	Node* Head;
	Node* End;
	int size;
}Chain;
void initialize_Chain(Chain* this);
Node* appendNode_Chain(Chain* this, StuInfor newData);
Node* locateNode_Chain(Chain* this,INDTYPE pos);
Node* insertNode_Chain(Chain* this, INDTYPE pos, StuInfor newData);
int findNode_Chain(Chain* this, StuInfor newData);
List searchNode_Chain(Chain* this,StuInfor newData);
List searchBy_Chain(Chain* this,const char* field,void* data);
void clear_Chain(Chain*);
void fileExport_Chain(Chain*,const char* Path);
void deleteNode_Chain(Chain* this, int pos);
bool fileImport_Chain(Chain* this, const char* Path);
void print_Chain(Chain*this);
void printAt_Chain(Chain* this,INDTYPE index);
bool isOutRange(Chain* this, INDTYPE Index);
Chain* getValChain_List(List* this, INDTYPE pos);
bool fieldChoose(StuInfor* temp, const char*);
#endif
