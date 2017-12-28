/*
 * Information om utvecklingen.
 * -----------------------------
 *  Inledande skapare: Andreas Johansson.
 *  Datum då det skapades:
 *  Senaste uppdateringen av: Andreas Johansson.
 *  Uppdaterings datum:
 */

/*
 * Fil: misc.c
 * ----------------
 */

#include "head_hex.h"

/*
 * Funktion: platta_ut
 * Användning: Plattar ut en kvadrat till ett fält.
 * -------------------------------------------------
 */
void platta_ut(int platt[],int kvadrat[][N2],int n)
{
	int i = 0;
	for (int j = 0; j < n; j++) /* Rad. */
	{
		for (int k = 0; k < N2; k++) /* Kolumn. */
		{
			platt[i] = kvadrat[j][k];
			i++;
		}
	}
}

/*
 * Funktion: cpy_int_array
 * Användning: Kopierar ett heltals fält till ett annat heltals fält.
 * -------------------------------------------------------------------
 */
void cpy_int_array(int *to,int *from,int n)
{
	for (int i = 0; i < n; i++)
	{
		to[i] = from[i];
	}
}

/*
 * Funktion: cpy_str_array
 * Användning: Kopierar en sträng till en annan sträng.
 * -----------------------------------------------------
 */
void cpy_str_array(char *to,char *from)
{
	int i = 0;
	for (; from[i] != '\0'; i++)
	{
		to[i] = from[i];
	}
	to[i] = '\0';
}

/*
 * Funktion: slump
 * Användning: Ersätter n st slump valda siffror med blank tecken(X).
 * -------------------------------------------------------------------
 */
void slump(int kvadrat[N1],int n)
{
	int i = 0,a,b[n],f;
	for (int i = 0; i < n; i++)
	{
		b[i] = BLANK; /* BLANK (16) är bra att ha som "noll" tal pga. a kommer aldrig att bli 16. */
	}
	srand((int)time(NULL));
	while (i < n)
	{
		f = 0;
		a = rand()%16;
		for (int j = 0; j < n; j++)
		{
			if (a == b[j])
			{
				f++;
			}
		}
		if (!f)
		{
			kvadrat[a] = BLANK;
			b[i] = a;
			i++;
		}
	}
}

/*
 * Funktion: skapa_variable
 * Användning: Skapar en variabel av typen varibleT.
 * --------------------------------------------------
 */
int skapa_variable(char *namn,int *kvadrat,variableT *var)
{
	if (antal_variabler('a') == MAX_VAR)
	{
		fprintf(stderr,"Kan inte skapa mer variabler.\n");
		return 0;
	}
	var->klen = N1;
	var->kvadrat = (int*)malloc(N1*sizeof(int));
	var->namn = (char*)malloc(MAX_ARRAY*sizeof(char));
	cpy_int_array(var->kvadrat,kvadrat,N1);
	cpy_str_array(var->namn,namn);
	var->nlen = strlen(var->namn);
	var->namn = (char*)realloc(var->namn,var->nlen+1);
	antal_variabler('n');
	return 1;
}

/*
 * Funktion: free_pool
 * Användning: Fri gör en pool med variabler.
 * ---------------------------------
 */
void free_pool(variableT *varPool)
{
	for (int i = 0; i < antal_variabler('a'); i++)
	{
		free(varPool[i].kvadrat);
		free(varPool[i].namn);
	}
}

/*
 * Funktion: antal_variabler
 * Användning: Håller koll på hur många variabler som används.
 * --------------------------------------------------------------
 */
int antal_variabler(char val)
{
	static int antal = 0;
	switch (val)
	{
		case 'n':
			antal += 1;
			break;
		case 'r':
			antal -= 1;
			break;
		case 'a':
			break;
		default:
			return -1;
	}
	return antal;
}

/*
 * Funktion: hitta_variabler
 * Användning: Hittar den variablen man letar efter.
 * --------------------------------------------------
 */
int hitta_variabler(variableT *var,char *namn)
{
	int antal = antal_variabler('a');
	for (int i = 0; i < antal; i++)
	{
		if (strncmp(namn,var[i].namn,var[i].nlen) == 0)
		{
			return i;
		}
	}
	return -1;
}
