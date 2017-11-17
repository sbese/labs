#include <stdio.h>
#include <stdlib.h>
const char *err="invalid data";
double ktc(double grad) { return grad-273.15; }

double ktf(double grad) { return (grad-273.15)*1.8+32; }

double ctk(double grad) { return grad+273.15; }

double ctf(double grad) { return grad*1.8+32; }

double ftk(double grad) { return (grad-32)*(5.0/9.0)+273.15; }

double ftc(double grad) { return (grad-32)*(5.0/9.0); }

void Kcon(double con)
{
	if(con<0){ puts(err);}
	else
	{
		printf("%.2f C\n",ktc(con));
		printf("%.2f F\n",ktf(con));
	}
}

void Ccon(double con)
{
	if(ctk(con)<0){ puts(err);}
	else
	{
		printf("%.2f K\n",ctk(con));
		printf("%.2f F\n",ctf(con));
	}
}

void Fcon(double con)
{
	if(ftk(con)<0){ puts(err);}
	else
	{
		printf("%.2f K\n",ftk(con));
		printf("%.2f C\n",ftc(con));
	}
}

int main(int argc, char const *argv[])
{
	if (argc<2 || argc>3)
	{
		puts(err);
	}
	else
	{
		if(argc==2)
		{
			Ccon(atof(argv[1]));
		}
		else
			{
				switch(argv[2][0])
				{
					case 'K' : {Kcon(atof(argv[1])); break;}
					case 'C' : {Ccon(atof(argv[1])); break;}
					case 'F' : {Fcon(atof(argv[1])); break;}
					default : puts(err);
				}
			}
	}
}