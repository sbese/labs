#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

const char *err = "err";
struct mem
{
	int value;
	struct mem *next;
	struct mem *previous;
};

typedef struct mem memory;
typedef memory * Memoryptr;

Memoryptr Memory = NULL;

struct cmd
{
	int index;
	char command[256];
	struct cmd *next;
	struct cmd *previous;
};
typedef struct cmd command;
typedef command * Commandptr;
Commandptr Command=NULL;

int isaction(char *);
void atc(char *, Commandptr *);
void atm(Memoryptr *, int);
void move_to(Commandptr *, int);
void action(char *);

int stack[10];
int stack_pointer;



int main(int argc, char const *argv[])
{
	stack_pointer = 0;

	FILE *f = fopen("iw","r");

	char line[256];
	while(!feof(f))
	{
		fgets(line,256,f);
		if (isaction(line))
		{
			atc(line,&Command);
		}
		else
		{
			printf("1%s\n",err);
			exit(1);
		}
	}
	fclose(f);
	atc("NULL",&Command);
	atm(&Memory,0);
	move_to(&Command,0);
	do
	{

		action(Command->command);
		Command=Command->next;

	} while(!strstr(Command->command, "NULL"));

	return 0;
}

void action(char * operaton)
{

	if ((strstr(operaton,"inc")) !=NULL)
	{
		Memory->value++;
	}

	else if ((strstr(operaton,"dec")) !=NULL)
	{
		Memory->value--;
	}

	else if ((strstr(operaton,"printc")) !=NULL)
	{
		printf("%c",(char)((int)(Memory->value)));
	}

	else if ((strstr(operaton,"print")) !=NULL)
	{
		printf(":: %d",Memory->value);
	}

	else if ((strstr(operaton,"get")) !=NULL)
	{
	    printf("\n>> ");
		scanf("%d", &(Memory->value));	
	}

	else if ((strstr(operaton,"begin")) !=NULL)
	{
		if(Memory->value == 0)
			while(!strstr(Command->command,"end"))
				Command= Command -> next;
		else if(stack[stack_pointer] != Command->index)
		{
			stack[stack_pointer] = Command->index;
			stack_pointer++;
		}
	}

	else if ((strstr(operaton,"end")) !=NULL)
	{
		if (Memory->value != 0)
		{
			move_to(&Command,stack[stack_pointer-1]);
		}
		else
		{
			stack[stack_pointer-1] = 0;
			stack_pointer--;
		}
	}

	else if ((strstr(operaton,"movl")) !=NULL)
	{
		if(Memory->previous==NULL)
			atm(&Memory,0);
		Memory= Memory->previous;
	}

	else if ((strstr(operaton,"movr")) !=NULL)
	{
		if(Memory->next==NULL)
			atm(&Memory,1);
		Memory= Memory->next;
	}
}

int isaction(char *line)
{
	if(strstr(line, "inc") || strstr(line, "dec") || strstr(line, "movl") || 
	strstr(line, "movr") || strstr(line, "get") || strstr(line, "printc") || 
	strstr(line, "print") || strstr(line, "begin") || strstr(line, "end") || strstr(line, "*")) 
	return 1;
	else return 0;
}

void atc (char *line, Commandptr *command_chain)
{
	if ((*command_chain)==NULL)
	{
		if((*command_chain = malloc(sizeof(command))) == NULL)
		{
			printf("%s123\n",err);
			exit(-1);
		}
		(*command_chain)->index = 0;
		strcpy((*command_chain)->command, line);
		(*command_chain)->previous=NULL;
		(*command_chain)->next=NULL;
	}
	else
	{
		Commandptr new_command;
		if((new_command = malloc(sizeof(command))) == NULL)
		{
			printf("2%s\n",err);
			exit(-1);
		}
		else 
		{
			new_command->index = (*command_chain)->index +1;
			strcpy(new_command->command, line);
			(*command_chain)->next=new_command;
			new_command->previous=(*command_chain);
			new_command->next=NULL;
			(*command_chain)=new_command;
		}
	}
}

void atm(Memoryptr *list, int lr)
{
	if (*list==NULL)
	{
		if((*list = malloc(sizeof(memory)))==NULL)
		{
			printf("3%s\n",err);
			exit(-1);
		}
		(*list)->value = 0;
		(*list)->next=NULL;
		(*list)->previous=NULL;		
	}
	else
	{
		Memoryptr memory_chain;
		if((memory_chain = malloc(sizeof(memory)))==NULL)
		{
			printf("4%s\n",err);
			exit(-1);
		}
		memory_chain->value = 0;
		if(lr==0)
		{
			(*list)->previous=memory_chain;
			memory_chain->next=(*list);
			memory_chain->previous=NULL;

		}
		else if(lr==1)
		{
			(*list)->next=memory_chain;
			memory_chain->previous=(*list);
			memory_chain->next=NULL;

		}
	}
}

void move_to(Commandptr *list, int index)
{
	if((*list)->index > index)
	{
		while((*list)->index > index)
		{
			*list = (*list)->previous;
		}
	}
	else if((*list)->index < index)
	{
		while((*list)->index < index)
		{
			*list = (*list)->next;
		}
	}
	else return;
}