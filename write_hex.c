/*
 * Information om utvecklingen.
 * -----------------------------
 *  Inledande skapare: Andreas Johansson.
 *  Datum då det skapades:
 *  Senaste uppdateringen av: Andreas Johansson.
 *  Uppdaterings datum:
 */

/*
 * Fil: write_hex.c
 * ----------------
 */

#include "head_hex.h"

/*
 * Funktion: itoc
 * Användning: Gör om heltal till tecken.
 * ---------------------------------------
 */
void itoc(char to[], const int from[], int n)
{
	int i = 0;
	for (; i < n; i++)
	{
		if (from[i] > 9)
		{
			switch (from[i])
			{
				case 10:
					to[i] = 'A';
					break;
				case 11:
					to[i] = 'B';
					break;
				case 12:
					to[i] = 'C';
					break;
				case 13:
					to[i] = 'D';
					break;
				case 14:
					to[i] = 'E';
					break;
				case 15:
					to[i] = 'F';
					break;
				case BLANK:
					to[i] = 'X'; /* X representerar blank tecken pga. jag har en funktion som rensar sånt. */
					break;
			}
		}
		else
		{
			to[i] = from[i] + '0';
		}
	}
	to[i] = '\0';
}

/*
 * Funktion: write_stdout
 * Användning: Skriver ut kvadrater till stdout.
 * ----------------------------------------------
 */
void write_stdout(int kvadrat[],int rad,int kolumn)
{
	char ut[rad+1];
	itoc(ut,kvadrat,rad);
	for (int i = 0; i < kolumn; i++)
	{
		for (int j = i*kolumn; j < i*kolumn+kolumn; j++)
		{
			printf("%c ",ut[j]);
		}
		printf("\n");
	}
}

/*
 * Funktion: write_file
 * Användning: Skriver ut kvadraten till fil.
 * -------------------------------------------
 */
int write_file(variableT *varPool, const char namn[])
{
	char ut[N1+1];
	FILE *utfil;
	if ((utfil = fopen(namn,"a")) == NULL)
	{
		fprintf(stderr,"Misslyckades att skriva till filen %s.\n",namn);
		return 0;
	}
	for (int i = 0; i < antal_variabler('a'); i++)
	{
		itoc(ut,varPool[i].kvadrat,N1);
		for (int j = 0; j < strlen(ut); j++)
		{
			fputc(ut[j],utfil);
			fputc(' ',utfil);
		}
		fputc('\n',utfil);
	}
	fclose(utfil);
	return 1;
}

/*
 * Funktion: write_set
 * Använding: Skriver ut delmängder.
 * -----------------------------------
 */
void write_set(int **set,int rad,int kolumn)
{
	char ut[kolumn+1];
	for (int i = 0; i < rad; i++)
	{
		itoc(ut,set[i],kolumn);
		printf("{ ");
		for (int j = 0; j < kolumn; j++)
		{
			printf("%c ",ut[j]);
		}
		printf("}\n");
	}
}
