#include"struct.h"
#include <conio.h>
#include <string.h>
#include <io.h>
#define NPTEMP Node* temp

bool arrSame(int* arr1, int* arr2,int size)
{
	for (int n = 0; n < size; ++n)
	{
		if(arr1[n] != arr2[n])
			return FALSE;
	}
	return TRUE;
}
int power2(int x)
{
	int result = 1;
	for(int n = 0;n<x;n++,result*=2);
	return result;
}


bool cmpStuInfor(const StuInfor obj1, const StuInfor obj2)
{
	bool result = obj1.GPA == obj2.GPA
	&& arrSame(obj1.Grade,obj2.Grade,7)
	&& strcmp(obj1.ID, obj2.ID)==0
	&& obj1.isMan==obj2.isMan
	&& strcmp(obj1.name,obj2.name)==0;
	return result;
}
StuInfor asStuInfor(char name[NAMESIZE], char ID[12], bool isMan, int Grade[7], double GPA)
{
	StuInfor temp;
	temp.GPA= GPA;
	strcpy_s(temp.name,NAMESIZE, name );
	ARRASSIGN(temp.Grade,Grade,7);
	strcpy_s(temp.ID,IDSIZE,ID);
	temp.isMan = isMan;
	return temp;
}
void tofile_StudInfor(StuInfor* this, FILE* Path)
{
	fprintf(Path, "%s\t", this->name);
	fprintf(Path, "%s\t", this->ID);
	if (this->isMan)
		fprintf(Path, "%s\t", "Male");
	else
		fprintf(Path, "%s\t", "Female");
	for (int n = 0; n < 7; ++n)
		fprintf(Path, "%d\t", this->Grade[n]);
	fprintf(Path, "%f", this->GPA);
}
void print_StuInfor(StuInfor* this)
{
	printf("%s\t",this->name);
	printf("%s\t",this->ID);
	if(this->isMan)
		printf("%s\t","Male");
	else
		printf("%s\t","Female");
	for(int n = 0 ;n<7;++n)
		printf("%d\t",this->Grade[n]);
	printf("%f\n",this->GPA);
}
bool fieldChoose(StuInfor* temp,const char* tempS)
{
	if (strcmp(tempS, "all") == 0)
	{
		scan_StuInfor(&temp);
	}
	else
	{
		CmdUI();
		char* Buffer= instantScan(tempS);
		if (Buffer == NULL)
		{
			ErrorMessage("Manually Terminated",FALSE);
			return FALSE;
		}
		if (strcmp(tempS, "name") == 0)
			strcpy_s(temp->name, 30, Buffer);
		else if (strcmp(tempS, "ID") == 0 || strcmp(tempS, "id") == 0)
			strcpy_s(temp->ID, 12, Buffer);
		else if (strcmp(tempS, "gender") == 0)
		{
			if (strcmp(Buffer, "Male") == 0 || strcmp(Buffer, "male") == 0 || strcmp(Buffer, "MALE") == 0)
				temp->isMan = 1;
			else
				temp->isMan = FALSE;
			}
		else if (strcmp(tempS, "math") == 0)
		{
			temp->Grade[0] = atoi(Buffer);
		}
		else if (strcmp(tempS, "comsys") == 0)
		{
			temp->Grade[1] = atoi(Buffer);
		}
		else if (strcmp(tempS, "imppro") == 0)
		{
			temp->Grade[2] = atoi(Buffer);
			}
		else if (strcmp(tempS, "program") == 0)
		{
			temp->Grade[3] = atoi(Buffer);
		}
		else if (strcmp(tempS, "funpro") == 0)
		{
			temp->Grade[4] = atoi(Buffer);
			}
		else if (strcmp(tempS, "leamet") == 0)
			temp->Grade[5] = atoi(Buffer);
		else if (strcmp(tempS, "busin") == 0)
			temp->Grade[6] = atoi(Buffer);
		else
		{
			ErrorMessage("Invalid input", FALSE);
			return 0;
		}
		return 1;
	}
	
	
	return TRUE;
}
char* instantScan(const char* message)
{
	char Key=0;
	char Buffer[30];
	for (int n = 0; Key != 27;)
	{
		if(message != NULL)
			dynamicHint(message);
		Key=_getch();
		if (Key == 13 || Key == 27 || Key == 8)
		{
			if (Key == 13&&n!=0)
			{
				Buffer[n] = '\0';
				clearAfter(strlen(message)+2);
				return Buffer;
			}
			else if (Key == 8 && n != 0)
			{
				printf("\b \b");
				n--;
			}
		}
		else if (n<29)
		{
			printf("%c",Key);
			Buffer[n] = Key;
			++n;
		}
	}
	return NULL;
}
int drawHint(int Field)
{
	int len=0;
	if (Field == -1)
	{
		printf("--Select             ");
		len = strlen("--Select             ");
	}
	else if (Field == 0)
	{
		printf("--Name             ");
		len = strlen("--Name             ");
	}
	else if (Field == 1)
	{
		printf("--ID             ");
		len = strlen("--ID             ");
	}
	else if (Field == 2)
	{
		printf("--Gender             ");
		len = strlen("--Gender             ");
	}
	else if (Field == 3)
	{
		printf("--Math             ");
		len = strlen("--Math             ");
	}
	else if (Field == 4)
	{
		printf("--ComSys            ");
		len = strlen("--ComSys            ");
	}
	else if (Field == 5)
	{
		printf("--ImpPro            ");
		len = strlen("--ImpPro            ");
	}
	else if (Field == 6)
	{
		printf("--Program            ");
		len = strlen("--Program            ");
	}
	else if (Field == 7)
	{
		printf("--FunPro            ");
		len = strlen("--FunPro            ");
	}
	else if (Field == 8)
	{
		printf("--LeaMet            ");
		len = strlen("--LeaMet            ");
	}
	else if (Field == 9)
	{
		printf("--Busin             ");
		len = strlen("--Busin             ");
	}
	for(int n = 0;n<len;++n)
		printf("\b");
	return len;
}
int scan_StuInfor(StuInfor* this)
{
	StuInfor Buffer;
	char*p;
	char Key = 0;
	char BufferS[30];
	int lastLen[9]={0};
	for (int n = 0,model = 0,sum=0,pos = 0,len;;)
	{
		len = drawHint(model);
		Key = _getch();
		if (Key == 13 || Key == 27 || Key == 8||Key == 32)
		{
			if (Key == 13&&((model==9&&n !=0 )|| (n == 0&&model  == 0)))
			{
				if (model == 0)
				{
					this->name[0]='\0';
					this->ID[0]='\0';
					this->isMan=0;
					for(int m = 0;m<7;m++)
					this->Grade[m]=0;
					this->GPA=0;
					clearAfter(len);
					return 1;
				}
				else if (model>=0&&model<9)
				{
					clearAfter(len);
					return 0;
				}
				else
				{
					sum += Buffer.Grade[pos] = atoi(BufferS);
					Buffer.GPA = sum/7.0;
					clearAfter(len);
					break;
				}
			}
			else if (Key == 13 && model != 9&&n!=0)
			{
				ErrorMessage(" <You have unfinished terms left>",-1);
			}
			else if (Key == 27)
			{
				clearAfter(len);
				return 0;
			}
			else if ((Key == 8 && n != 0)||(Key == 8&&model!=0))
			{
				printf("\b \b");
				n--;
				if (n >= 0)
				{
					BufferS[n] = 0;
				}
				if ((model >= 3 && model <= 9) && n == -1)
				{
					pos--;
				}
				if (n == -1 && model != 0)
				{
					model--;
					n = lastLen[model];
				}
			}
			else if (Key == 32&&model<9&&n!=0)
			{
				printf("%c",Key);
				BufferS[n] = '\0';
				lastLen[model] = n;
				if (model == 0)
				{
					strcpy_s(Buffer.name,30,BufferS);
				}
				else if (model == 1)
				{
					strcpy_s(Buffer.ID,20,BufferS);
				}
				else if (model == 2)
				{
					if(strcmp(BufferS,"Male")==0||strcmp(BufferS,"male")==0|| strcmp(BufferS, "MALE")==0)
						Buffer.isMan=1;
					else
						Buffer.isMan =FALSE;
				}
				else if (model >= 3 && model <= 9)
				{
					sum+=Buffer.Grade[pos] = atoi(BufferS);
					pos++;
				}
				n = 0;
				model++;
			}
		}
		else if ((n < 29&&model == 0)||(n<19&&model == 1)||(n<4&&model==2)||model>2)
		{
			if (model < 3 || ONLYNUM)
			{
				printf("%c", Key);
				BufferS[n] = Key;
				BufferS[n + 1] = '\0';
				++n;
			}
		}
	}
	strcpy_s(this->name, NAMESIZE, Buffer.name);
	strcpy_s(this->ID, IDSIZE, Buffer.ID);
	this->isMan = Buffer.isMan;
	ARRASSIGN(this->Grade, Buffer.Grade, 7);
	this->GPA = Buffer.GPA;
	return 1;
}

void initialize_List(List* this,oneByte byteSize)
{
	if(this->Space != NULL)
		DEL(this->Space);
	this->Byte = byteSize;
	this->size = 0;
	this->Index = 0;
	this->Space = NULL;
}
void addData_List(List* this, void* data)
{
	if (this->Index == this->size)
	{
		 int tempSize;
		 if(this->size == 0)
			tempSize = 4;
		else
			tempSize = this->size*2;

		void* temp = NEW(tempSize *this->Byte);
		if (this->Space != NULL)
		{
			ARRASSIGN((CP temp),(CP this->Space),this->size*this->Byte);
			DEL(this->Space);
		}
		this->Space = temp;
		this->size = tempSize;
	}
	if (this->size != 0&&data!=NULL)
	{
		if (this->Byte == 4)
			(IP this->Space)[this->Index] = ASINT data;
		else if (this->Byte == 1)
			(CP this->Space)[this->Index] = ASCHAR data;
		
		else if (this->Byte == sizeof(Node*))
		{
			Node** temp = CP this->Space+this->Index*8;
			*temp = data;
		}
		else if (this->Byte == sizeof(Chain))
			(CHP this->Space)[this->Index] = ASCHAIN data;
		else if(this->Byte == sizeof(StuInfor))
			((StuInfor*)this->Space)[this->Index] = *(StuInfor*) data;
	}
	this->Index++;
}
bool isEmpty(List* this)
{
	return  this->Space == NULL;
}
void addStr_List(List* this, char* data)
{
	if (this->Byte == 1)
	{
		int end = strlen(data)+1;
		for(int n = 0;n<end;++n)
			addData_List(this,&data[n]);
		addData_List(this,'\0');
	}
}
int getValInt_List(List* this, INDTYPE pos)
{
	if (this->Byte == sizeof(int))
		return (IP this->Space)[pos];
	return ERROR;
}
double getValDouble_List(List* this, INDTYPE pos)
{
	if(this->Byte == sizeof(double))
		return (DP this->Space)[pos];
	return ERROR;
}
char* getStr_List(List* this)
{
	return (CP this->Space);
}
void* getEle_List(List* this,INDTYPE pos)
{
	char* temp = CP this->Space;
	for (int n = 0; n < pos; ++n, temp += this->Byte);
	return temp;
}
Node* getValNode_List(List* this, INDTYPE pos)
{
	Node** temp =  (Node**)(CP this->Space+pos*8);
	return *temp;
}
Chain* getValChain_List(List* this, INDTYPE pos)
{
	if (this->Byte == sizeof(Chain))
	{
		Chain* temp = CP this->Space+pos*this->Byte;
		return temp;
	}
	return NULL;
}
void deletePtr_List(List* this,INDTYPE pos)
{
	char* temp = CP this->Space;
	int n = 0;
	for (;n<pos;++n, temp += this->Byte);
	DEL(temp);
	for (; n < this->Index; ++n, temp += this->Byte)
		temp = temp += this->Byte;
}
void clear_List(List* this)
{
	if (this->Space != NULL)
	{
		DEL(this->Space);
		this->Space = NULL;
		this->Byte = this->Index = this->size = 0;
	}
}
/// /////////////////////////////////////////////////

Node* new_Node(Node* Father, Node* Son, StuInfor newData)
{
	Node* Temp = (Node*)malloc(sizeof(Node));
	Temp->next = Son;
	if (Father != NULL)
		Father->next = Temp;
	//assign values from newData
	strcpy_s(Temp->dataZone.name, NAMESIZE,newData.name);
	Temp->dataZone.isMan =newData.isMan;
	strcpy_s(Temp->dataZone.ID, IDSIZE, newData.ID);
	ARRASSIGN(Temp->dataZone.Grade, newData.Grade,7);
	Temp->dataZone.GPA = newData.GPA;
	return Temp;
}
Node* del_Node(Node* this, Node* Father)
{
	if(Father!=NULL)
		Father->next = this->next;
	DEL(this);
	return Father;
}
int next_Count(Node* this)
{
	int n = 0;
	for (;this != NULL;++n,INC(this) );
	return n;
}
bool isEnd(Node* this)
{
	return this->next == NULL;
}
Node* link_Node(Node* this,Node* newNext)
{
	Node* Temp;
	if (this->next != NULL&&newNext != NULL)
	{
		Temp = this->next;
		newNext->next = Temp;
	}
	this->next = newNext;
}

/////////////////////////////////////////
void clear_Chain(Chain* this)
{
	if (this->Head != NULL)
	{
		for (Node* waitDel = this->Head, *temp = waitDel->next; temp != NULL; INC(temp))
		{
			free(waitDel);
			waitDel = temp;
		}
		this->Head = this->End = NULL;
		this->size = 0;
	}
}
void initialize_Chain(Chain* this)
{
	this->Head = NULL;
	this->End = NULL;
	this->size = 0;
}
bool isOutRange(Chain* this,INDTYPE Index)
{
	return Index >= this->size;
}
Node* appendNode_Chain(Chain* this, StuInfor newData)
{
	this->size++;
	if (this->Head == NULL)
	{
		return this->Head =this->End= new_Node(NULL,NULL,newData);
	}
	return this->End = new_Node(this->End,NULL,newData);
}
Node* locateNode_Chain(Chain* this, INDTYPE pos)
{
	if (isOutRange(this ,pos))
		return NULL;
	Node* temp = this->Head;
	static Node* LastNode = NULL;
	static int Last = -1;
	if (pos == Last)
		return LastNode;
	for (int n = 0; n < pos; ++n, INC(temp));
	return LastNode = temp;
}	
Node* insertNode_Chain(Chain* this, INDTYPE pos, StuInfor newData)
{
	if (isOutRange(this, pos))
		return NULL;
	if (pos != 0)
	{
		if (pos == this->size)
		{
			return appendNode_Chain(this,newData);
		}
		pos -= 1;
		Node* goalPlace = locateNode_Chain(this, pos);
		return goalPlace->next = new_Node(goalPlace, goalPlace->next, newData);
	}
	else
	{
		Node* goalPlace = locateNode_Chain(this, pos);
		if(this->Head ==this->End)
			this->End = goalPlace;
		return this->Head = new_Node(NULL, goalPlace, newData);
	}
	this->size++;
}
int findNode_Chain(Chain* this, StuInfor newData)
{
	Node* temp = this->Head;
	for (int n = 0; n < this->size; ++n, INC(temp))
	{
		if (cmpStuInfor(temp->dataZone, newData))
			return n;
	}
	return -1;
}
List searchNode_Chain(Chain* this, StuInfor newData)
{
	List result;
	initialize_List(&result,sizeof(Node*));
	Node* temp = this->Head;
	for (int n = 0; temp != NULL; ++n,INC(temp))
	{
		if (cmpStuInfor(temp->dataZone, newData))
			addData_List(&result, temp);
	}
	return result;
}
List searchBy_Chain(Chain* this, const char* field, void* data)
{
	List result;
	initialize_List(&result, sizeof(Node*));
	Node* temp = this->Head;
	int Index = 0;
	if (strcmp(field, "name") == 0)
	{
		for (int n = 0; n < this->size; ++n,INC(temp))
		{
			if(strcmp((CP data),temp->dataZone.name))
				addData_List(&result,temp);
		}
	}
	else if (strcmp(field, "ID") == 0)
	{
		for (int n = 0; n < this->size; ++n, INC(temp))
		{
			if (strcmp((CP data), temp->dataZone.ID))
				addData_List(&result, temp);
		}
	}
	else if (strcmp(field, "gender") == 0)
	{
		for (int n = 0; n < this->size; ++n, INC(temp))
		{
			if (ASCHAR data == temp->dataZone.isMan)
				addData_List(&result, temp);
		}
	}
	else if (strcmp(field, MATH) == 0)
	{
		for (int n = 0; n < this->size; ++n, INC(temp))
		{
			if (ASINT data == temp->dataZone.Grade[Index])
				addData_List(&result, temp);
		}
	}
	else if (++Index,strcmp(field, COMSYS) == 0)
	{
		for (int n = 0; n < this->size; ++n, INC(temp))
		{
			if (ASINT data == temp->dataZone.Grade[Index])
				addData_List(&result, temp);
		}
	}
	else if (++Index,strcmp(field, IMPPRO) == 0)
	{
		for (int n = 0; n < this->size; ++n, INC(temp))
		{
			if (ASINT data == temp->dataZone.Grade[Index])
				addData_List(&result, temp);
		}
	}
	else if (++Index,strcmp(field, PROGRA) == 0)
	{
		for (int n = 0; n < this->size; ++n, INC(temp))
		{
			if (ASINT data == temp->dataZone.Grade[Index])
				addData_List(&result, temp);
		}
	}
	else if (++Index, strcmp(field, FUNPRO) == 0)
	{
		for (int n = 0; n < this->size; ++n, INC(temp))
		{
			if (ASINT data == temp->dataZone.Grade[Index])
				addData_List(&result, temp);
		}
	}
	else if (++Index, strcmp(field, LEAMET) == 0)
	{
		for (int n = 0; n < this->size; ++n, INC(temp))
		{
			if (ASINT data == temp->dataZone.Grade[Index])
				addData_List(&result, temp);
		}
	}
	else if (++Index, strcmp(field, BUSINN) == 0)
	{
		for (int n = 0; n < this->size; ++n, INC(temp))
		{
			if (ASINT data == temp->dataZone.Grade[Index])
				addData_List(&result, temp);
		}
	}
	else
	{
		result.Index = 0;
	}
	return result;
}
void printAt_Chain(Chain* this, INDTYPE index)
{
	if(!isOutRange(this,index))
	print_StuInfor(&locateNode_Chain(this,index)->dataZone);
}
void deleteNode_Chain(Chain* this, INDTYPE pos)
{
	if (this->Head != NULL)
	{
		Node* temp = locateNode_Chain(this, pos);
		if (temp == this->Head)
			this->Head = temp->next;
		else if (temp == this->End)
			this->End = locateNode_Chain(this, pos - 1);
		else
		{
			Node* prev = locateNode_Chain(this, pos - 1);
			prev->next = temp->next;
		}
		DEL(temp);
		this->size--;
	}
}
void fileExport_Chain(Chain* this, const char* Path)
{
	FILE* fileObj;
	fopen_s(&fileObj ,Path,"w");
	Node* temp = this->Head;
	for (int n = 0; n < this->size; ++n, INC(temp))
	{
		if(n != 0)
		fprintf(fileObj,"\n");
		tofile_StudInfor(&temp->dataZone, fileObj);
	}
		
	fclose(fileObj);
}
bool fileImport_Chain(Chain* this, const char* Path)
{
	FILE* fileObj;
	fopen_s(&fileObj, Path, "r");
	if (fileObj != NULL)
	{
		while (feof(fileObj)== 0)
		{
			StuInfor result;
			const char temp[6];
			int n = 0;
			fscanf_s(fileObj, "%s %s %s", result.name, NAMESIZE, result.ID, IDSIZE,temp ,6);
			if (strcmp(temp, "male"))
				result.isMan = TRUE;
			else
				result.isMan = FALSE;
			for(int n = 0;n<7;++n)
				fscanf_s(fileObj, "%d", &result.Grade[n]);
			fscanf_s(fileObj,"%lf",&result.GPA);
			appendNode_Chain(this, result);
		}
		fclose(fileObj);
		return TRUE;
	}
	return FALSE;

}
void print_Chain(Chain* this)
{
	Node* temp = this->Head;
	for (int n = 0; n < this->size; n++, INC(temp))
	{
		printf("%d\t",n+1);
		print_StuInfor(&temp->dataZone);
	}
		
}