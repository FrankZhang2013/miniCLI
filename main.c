#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_BUFF_LEN 100
#define RET_OK 0
#define RET_ERROR -1
#define RET_EXIT -2

void PrintFloor(int floor)
{
	printf("congrulations ,this is %u floor\n", floor);
}

typedef struct CmdTree
{
	char CmdType[10];
	int CmdLevel;
	struct CmdTree* stSubTree;
	void (*pProcessFun)(int);
}stCmd_Tree;
stCmd_Tree g_GetNode[] = {
	{"Floor 1",1,NULL,PrintFloor},
	{"Floor 2",1,NULL,PrintFloor},
	{"Floor 3",1,NULL,PrintFloor},	
};

stCmd_Tree g_TopCmdNode[]={
	{"help",0,NULL,NULL},
	{"get",0,g_GetNode,NULL},
	{"set",0,NULL,NULL},
};



typedef struct 
{
	char ucCmd[CMD_BUFF_LEN];
	char ucHelpInfo[CMD_BUFF_LEN];
}HelpInfo;

HelpInfo g_HelpInfo[] = {
	{"?","get help info"},
	{"help","et help info"},
	{"quit","exit"},
};

char Cmd[][CMD_BUFF_LEN] = {
	"*******************************************************************\n",
	"**************************Main Menu********************************\n",
	"*******************************************************************\n",
	"1. ?       to get the main menu help infomation\n",
	"2. help    to get the main menu help infomation\n"
	"3. quit    to exit the MiniCli system\n",
	"*******************************************************************\n",
	};
void ModuleInit()
{
	
}
void PrintHelpInfo(char* str)
{
	int i;
	int uiFlag = 0;
	for (i=0; i<sizeof(Cmd)/sizeof(Cmd[0]);++i)
	{
		printf("%s",Cmd[i]);
	}
}
void TrimLeftSpace(char* str)
{
	return;
}
void Upper2Small(char* str)
{
	return;
}

int ExecuteCmd(char* str)
{
	int ret = RET_OK;
	int i;
	int slotid;
	Upper2Small(str);
	TrimLeftSpace(str);
	
	if ((strncmp(str,"?",strlen("?"))==0) || (strncmp(str,"help",strlen("help"))==0))
	{
		PrintHelpInfo(str);	
	}
	else if (strncmp(str,"quit",strlen("quit")) == 0)
	{
		ret = RET_EXIT;
	}
	else if (strncmp(str,"get",strlen("get")) == 0)
	{
		printf("slot <slotid>");
		scanf("%d",&slotid);
		g_GetNode[slotid].pProcessFun(slotid);	
	}

	return ret;
}

int InputCmdProcess(char* pCmdStr)
{
	int ret = RET_OK;
	memset(pCmdStr,0,sizeof(pCmdStr));
	printf("MiniCLI>");	
	scanf("%s",pCmdStr);
	
	printf("MiniCLI>");	
	printf("you putin : %s\n",pCmdStr);
	ret = ExecuteCmd(pCmdStr);
	printf("MiniCLI>");
	
	return ret;	
}

void main()
{
	char CmdStr[CMD_BUFF_LEN] = {0};
	ModuleInit();
	
	while (1)
	{
		if (InputCmdProcess(CmdStr) == RET_EXIT)
		{
			printf("quit................\n");
		}
		else if (InputCmdProcess(CmdStr) != RET_ERROR)
		{
			printf("fail,ret\n");
		}
		else
		{
			printf("sucess\n");
		}
	}
}
