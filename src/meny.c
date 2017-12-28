/*
 * Information om utvecklingen.
 * -----------------------------
 *  Inledande skapare: Andreas Johansson.
 *  Datum då det skapades:
 *  Senaste uppdateringen av: Andreas Johansson.
 *  Uppdaterings datum:
 */

/*
 * Fil: meny.c 
 * ----------------
 */

#include "head_hex.h"

/*
 * Funktion: read_terminal
 * Användning: Läser in kvadrat från terminalen.
 * ----------------------------------------------
 */
int read_terminal(variableT *varPool)
{
	int platt[N1],kvadrat[N2][N2];
	char namn[MAX_ARRAY];
	printf("Namn på Hexakvadrat: ");
	if (!read_line(namn,stdin))
	{
		fprintf(stderr,"read_line misslyckades.\n");
		return 0;
	}
	remove_white(namn);
	if (hitta_variabler(varPool,namn) > -1)
	{
		fprintf(stderr,"Detta namn är redan tilldelat en annan kvadrat.\nAnvänd ett annat namn.\n");
		return 0;
	}
	printf("Hexakvadrat:\n");
	for (int i = 0; i < N2; i++)
	{
		if (!read_input(kvadrat[i]))
		{
			fprintf(stderr,"read_input misslyckades\n");
			return 0;
		}
	}
	platta_ut(platt,kvadrat,N2);
	if (!skapa_variable(namn,platt,&varPool[antal_variabler('a')]))
	{
		fprintf(stderr,"skapa_variable misslyckades.\n");
		return 0;
	}
	return 1;
}

/*
 * Funktion: read_file_kvadrat
 * Användning: Läser in kvadrater från fil.
 * -----------------------------------------
 */
int read_file_kvadrat(variableT *varPool)
{
	char namn[MAX_ARRAY];
	printf("Filnamn: ");
	if (!read_line(namn,stdin))
	{
		fprintf(stderr,"read_line misslyckades.\n");
		return 0;
	}
	remove_white(namn);
	if (!read_file(varPool,namn))
	{
		fprintf(stderr,"read_file misslyckades.\n");
		return 0;
	}
	return 1;
}

/*
 * Funktion: test_kvadrat
 * Användning: Testar att kvadraten stämmer.
 * ------------------------------------------
 */
int test_kvadrat(variableT *varPool)
{
	int pos;
	char namn[MAX_ARRAY];
	printf("Hexakvadratens namn: ");
	if (!read_line(namn,stdin))
	{
		fprintf(stderr,"read_line misslyckades");
		return 0;
	}
	remove_white(namn);
	if ((pos = hitta_variabler(varPool,namn)) < 0)
	{
		fprintf(stderr,"Kunde inte hitta kvadraten.\n");
		return 0;
	}
	if (kontroll_kvadrat(varPool[pos].kvadrat))
	{
		printf("Kvadraten är magisk.\n");
	}
	else
	{
		printf("Kvadraten är inte magisk.\n");
	}
	return 1;
}

/*
 * Funktion: write_terminal
 * Användning: Skriver ut kvadraten till terminalen.
 * --------------------------------------------------
 */
int write_terminal(variableT *varPool)
{
	int pos;
	char namn[MAX_ARRAY];
	printf("Hexakvadratens namn: ");
	if (!read_line(namn,stdin))
	{
		fprintf(stderr,"read_line misslyckades.\n");
		return 0;
	}
	remove_white(namn);
	if ((pos = hitta_variabler(varPool,namn)) < 0)
	{
		fprintf(stderr,"Kunde inte hitta kvadraten.\n");
		return 0;
	}
	write_stdout(varPool[pos].kvadrat,N1,N2);
	return 1;
}

/*
 * Funktion: write_to_file
 * Användning: Skriver ut kvadraterna till fil.
 * ---------------------------------------------
 */
int write_to_file(variableT *varPool)
{
	char namn[MAX_ARRAY];
	printf("Filnamn: ");
	if (!read_line(namn,stdin))
	{
		fprintf(stderr,"read_line misslyckades.\n");
		return 0;
	}
	remove_white(namn);
	if (!write_file(varPool,namn))
	{
		fprintf(stderr,"write_file misslyckades.\n");
		return 0;
	}
	return 1;
}

/*
 * Funktion: spel
 * Användning: Fylla i de tomma luckorna i kvadraten.
 * ---------------------------------------------------
 */
int spel(variableT *varPool)
{
	int svarighet,pos,sant_falskt = 1,antal = antal_variabler('a'),platt[N1],kvadrat[N2][N2];
	printf("Välj svårighetsgrad 1 - 8: ");
	if ((svarighet = read_int()) < 0)
	{
		fprintf(stderr,"read_int misslyckades.\n");
		return 0;
	}
	srand((int)time(NULL));
	if (svarighet < 0 || svarighet > 8)
	{
		fprintf(stderr,"Välj svårighets grad mellan 1 och 8!\n");
		return 0;
	}
	do
	{
		if (antal == 0)
		{
			fprintf(stderr,"Finns inga kvadrater att spela med.\n");
			return 0;
		}
		else if (antal == 1)
		{
			pos = 0;
		}
		else
		{
			pos = rand()%antal;
		}
		if (kontroll_kvadrat(varPool[pos].kvadrat))
		{
			slump(varPool[pos].kvadrat,svarighet);
			write_stdout(varPool[pos].kvadrat,N1,N2);
			printf("Skriv in kvadraten igen och fyll i rätt siffror där det saknas:\n");
			for (int i = 0; i < N2; i++)
			{
				if (!read_input(kvadrat[i]))
				{
					fprintf(stderr,"read_input misslyckades\n");
					return 0;
				}
			}
			platta_ut(platt,kvadrat,N2);
			if (kontroll_kvadrat(platt))
			{
				printf("Kvadraten är magisk.\n");
			}
			else
			{
				printf("Kvadraten är inte magisk.\n");
			}
			sant_falskt = 0;
		}
		else
		{
			sant_falskt = 1;
		}
	}while(sant_falskt && antal > 1);
	return 1;
}
