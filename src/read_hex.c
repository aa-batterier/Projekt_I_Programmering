/*
 * Information om utvecklingen.
 * -----------------------------
 *  Inledande skapare: Andreas Johansson.
 *  Datum då det skapades:
 *  Senaste uppdateringen av: Andreas Johansson.
 *  Uppdaterings datum:
 */

/*
 * Fil: read_hex.c
 * ----------------
 */

#include "head_hex.h"

/*
 * Funktion: read_line
 * Användning: Läsa in en rad.
 * ------------------------------
 */
int read_line(char *input,FILE *from)
{
	if (fgets(input,MAX_ARRAY,from) == NULL)
	{
		fprintf(stderr,"Läsing avbröts.\n");
		return 0;
	}
	if (!remove_nl(input))
	{
		skip_line();
	}
	return 1;
}

/*
 * Funktion: remove_nl
 * Användning: Ta bort ny rad tecknet i slutet på en sträng. 
 * ----------------------------------------------------------
 */ 
int remove_nl(char *input)
{
	int i = strlen(input)-1;
	if (input[i] == '\n')
	{
		input[i] = '\0';
		return 1;
	}
	return 0;
}

/*
 * Funktion: skip_line
 * Användning: Hoppar över en hel rad.
 * ------------------------------------
 */
void skip_line(void)
{
	int c;
	while ((c = getchar()) != '\n' || c == EOF);
}

/*
 * Funktion: remove_white
 * Användning: Tar bort alla vita tecken ur fältet som skickas in.
 * ----------------------------------------------------------------
 */
void remove_white(char *input)
{
	char temp[strlen(input)];
	int i = 0;
	for (int j = 0; input[j] != '\0'; j++)
	{
		if (!isspace(input[j]))
		{
			temp[i] = input[j];
			i++;
		}
	}
	temp[i] = '\0';
	i = 0;
	for (; temp[i] != '\0'; i++)
	{
		input[i] = temp[i];
	}
	input[i] = '\0';
}

/*
 * Funktion: ctoh
 * Användning: Gör om tecken fält till heltals fält.
 * --------------------------------------------------
 */
int ctoh(int *to,const char *from)
{
	for (int i = 0; from[i] != '\0'; i++)
	{
		if (isxdigit(from[i]))
		{
			switch (toupper(from[i]))
			{
				/* Om det är en bokstav kan jag inte göra om så som siffror upp till 9. */
				case 'A':
					to[i] = 10;
					break;
				case 'B':
					to[i] = 11;
					break;
				case 'C':
					to[i] = 12;
					break;
				case 'D':
					to[i] = 13;
					break;
				case 'E':
					to[i] = 14;
					break;
				case 'F':
					to[i] = 15;
					break;
				default:
					to[i] = from[i] - '0';
					break;
			}
		}
		else if (from[i] == 'X') /* X betyder blank tecken pga. jag har en funktion som rensar bort alla blank tecken. */
		{
			to[i] = BLANK;
		}
		else
		{
			fprintf(stderr,"Fel tecken: %c.\n",from[i]);
			return 0;
		}
	}
	return 1;
}

/*
 * Funktion: read_input
 * Användning: Läser in rad från stdin.
 * -------------------------------------
 */
int read_input(int to[])
{
	char *input = (char*)calloc(1,MAX_ARRAY);
	if (!read_line(input,stdin))
	{
		fprintf(stderr,"read_line misslyckades.\n");
		return 0;
	}
	remove_white(input);
	input = realloc(input,strlen(input));
	if (!ctoh(to,input))
	{
		fprintf(stderr,"ctoh misslyckades.\n");
		return 0;
	}
	return 1;
}

/*
 * Funktion: read_file
 * Användning: Läser in en rad från fil.
 * --------------------------------------
 */
int read_file(variableT *varPool,char *namn)
{
	char input[MAX_ARRAY],hexNamn[MAX_ARRAY];
	int kvadrat[N1];
	FILE *from;
	if ((from = fopen(namn,"r")) == NULL)
	{
		fprintf(stderr,"Misslyckades att läsa från filen %s.\n",namn);
		return 0;
	}
	while(read_line(input,from))
	{
		printf("Skriv in namn på hexakvaraten: ");
		if (!read_line(hexNamn,stdin))
		{
			fprintf(stderr,"read_line misslyckades.\n");
			return 0;
		}
		remove_white(input);
		remove_white(hexNamn);
		if (hitta_variabler(varPool,hexNamn) > -1)
		{
			fprintf(stderr,"Detta namn är redan tilldelat en annan kvadrat.\nAnvänd ett annat namn.\n");
			return 0;
		}
		if (!ctoh(kvadrat,input))
		{
			fprintf(stderr,"ctoh misslyckades.\n");
			return 0;
		}
		if (!skapa_variable(hexNamn,kvadrat,&varPool[antal_variabler('a')]))
		{
			fprintf(stderr,"skapa_variable misslyckades.\n");
			return 0;
		}
	}
	fclose(from);
	return 1;
}

/*
 * Funktion: read_int
 * Användning: Läser in heltal från stdin.
 * ----------------------------------------
 */
int read_int(void)
{
	int nr = 0;
	char *input = (char*)calloc(1,MAX_ARRAY);
	if (!read_line(input,stdin))
	{
		fprintf(stderr,"read_line misslyckades.\n");
		return -1;
	}
	if (input[0] == '\0')
	{
		fprintf(stderr,"Skriv in ett av talen!\n");
		return -1;
	}
	remove_white(input);
	input = realloc(input,strlen(input));
	for (int i = pow(10,strlen(input)-1),j = 0; i > 0; i /= 10,j++)
	{
		nr += (input[j] - '0') * i;
	}
	return nr;
}
