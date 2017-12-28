/*
 * Information om utvecklingen.
 * -----------------------------
 *  Inledande skapare: Andreas Johansson.
 *  Datum då det skapades:
 *  Senaste uppdateringen av: Andreas Johansson.
 *  Uppdaterings datum:
 */

/*
 * Fil: main.c
 * ----------------
 */

#include "head_hex.h"

/* Huvud funktionen. */
int main(void)
{
	/* orig_platt är standard kvadraten. */
	int sant_falskt = 1,val,orig_platt[] = {0,13,2,15,14,8,7,1,11,3,12,4,5,6,9,10},**sets = (int**)malloc(SET*sizeof(int*)),**kvadSets = (int**)malloc(KVAD*sizeof(int*));
	/* Skapa pool med variabler. */
	variableT *varPool = (variableT*)malloc(MAX_VAR*sizeof(variableT));
	/* Initserar standard kvadraten. */
	if (!skapa_variable("platt",orig_platt,&varPool[antal_variabler('a')]))
	{
		fprintf(stderr,"skapa_variable misslyckades.\n");
		exit(1);
	}
	/* Skapar och tilldelar delmängderna. */
	memory_set(sets,SET,N2);
	memory_set(kvadSets,KVAD,N1);
	generate_set(sets);
	kombo_set(kvadSets,sets);
	printf("Magisk Hexadecimal Kvadrat.\n\n");
	do
	{
		printf("Meny:\n1.Läs in kvadraten från terminalen.\n2.Läs in kvadraten från fil.\n3.Testa om kvadraten stämmer.\n4.Skriv ut kvadraten till terminalen.\n5.Skriv ut kvadraten till fil.\n6.Fyll i luckorna.\n7.Generera delmängder.\n8.Kvadrater från delmängderna.\n0.Avsluta\n\nVal: ");
		if ((val = read_int()) < 0)
		{
			fprintf(stderr,"read_int misslyckades\n\n");
			continue;
		}
		switch (val)
		{
			case 0:
				sant_falskt = 0;
				break;
			case 1:
				read_terminal(varPool);
				break;
			case 2:
				read_file_kvadrat(varPool);
				break;
			case 3:
				test_kvadrat(varPool);
				break;
			case 4:
				write_terminal(varPool);
				break;
			case 5:
				write_to_file(varPool);
				break;
			case 6:
				spel(varPool);
				break;
			case 7:
				write_set(sets,SET,N2);
				break;
			case 8:
				for (int i = 0; i < KVAD; i++)
				{
					printf("\n");
					write_stdout(kvadSets[i],N1,N2);
				}
				break;
			default:
				fprintf(stderr,"Fel val.\n");
				break;
		}
		printf("\n");
	}while(sant_falskt);
	printf("Avslutar ...\n");
	free_set(sets,SET);
	free_set(kvadSets,KVAD);
	free_pool(varPool);
	free(varPool);
	free(sets);
	free(kvadSets);
	exit(0);
}
