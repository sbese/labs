#include <stdio.h>
int rm (int M)
{
	switch (M)
	{
		case (0):  return  0;
		case (1):  return  1; 
		case (2):  return -1; 
		case (3):  return  0; 
		case (4):  return  0; 
		case (5):  return  1; 
		case (6):  return  1; 
		case (7):  return  2; 
		case (8):  return  3; 
		case (9):  return  3;
		case (10): return  4;
		case (11): return  4;
		case (12): return  5;		
	}
} 

int vg (int Y)
{
	return (Y/4) - (Y/100) + (Y/400);
}
int main(int argc, char const *argv[])
{
	int YY,MM,DD;
	int fdy=0;
	scanf("%d %d %d",&YY,&MM,&DD);
	int i;
	int x;
	for(i=2;i<=YY;i++)
	{
		fdy++;
		if(((i-1)%4==0 && (i-1)%100!=0)||((i-1)%400==0))
		{
			fdy++;
		}

		fdy=fdy%7;
	}
	printf("%d\n",fdy);
	x = 30*(MM-1)+DD+rm(MM-1)+fdy-1;
	x = x%7;
	printf("%d\n",x);
	return 0;
}