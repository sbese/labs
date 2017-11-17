#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

const char *err="err";
struct stackstruct
{
	int value;
	struct stackstruct * prev;
};
typedef struct stackstruct Stack;
typedef Stack *stack;
stack st = NULL;

const char *sep =" ";
char *stringpart;

int pop(stack*);
void push(stack*,int	);

int isoperator(char*);
void operation(char,int,int);

int main(int argc, char const *argv[])
{
	char line[1024];
	fgets(line,1024,stdin);
	stringpart=strtok(line,sep);
	while(stringpart!=NULL)
	{
		if(isoperator(stringpart))
		{
			operation(stringpart[0], pop(&st),pop(&st));
		}
		else
		{
			push(&st,atoi(stringpart));
		}
		stringpart=strtok(NULL,sep);
	}
	printf("%d\n",st->value);
}

void push(stack	*line, int value)
{
	stack new_el;
	if((new_el=malloc(sizeof(Stack)))!=NULL)
	{
		new_el->value=value;
		new_el->prev=(*line);
		(*line)=new_el;
	}
	else
	{
		printf("%s\n",err);
	}
}

int pop (stack	*line)
{
	int rvalue=(*line)->value;
	stack del_el = (*line);
	(*line)=(*line)->prev;
	free(del_el);
	return rvalue;	

}

int isoperator(char	* symbol)
{
	if((strstr(symbol , "+" )) || (strstr(symbol , "-")) || (strstr(symbol , "*")) || (strstr(symbol , "/")))
		return 1;
	else return 0;
}

void operation(char op,int x, int	y)
{
	int	 result;
	switch(op)
	{
		case '+': result=x+y; break; 
		case '-': result=x-y; break; 
		case '*': result=y*x; break; 
		case '/': result=x/y; break; 		
	}
	push(&st,result);
}