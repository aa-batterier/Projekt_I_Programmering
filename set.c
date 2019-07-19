/*
 * Information om utvecklingen.
 * -----------------------------
 *  Inledande skapare: Andreas Johansson.
 *  Datum då det skapades:
 *  Senaste uppdateringen av: Andreas Johansson.
 *  Uppdaterings datum:
 */

/*
 * Fil: set.c
 * ----------------
 */

#include "head_hex.h" 

/*
 * Funktion: noll_kvadrat
 * Användning: Nollställer fältet.
 * --------------------------------
 */
void noll_kvadrat(int **kvadrat,int rad,int kolumn)
{
	for (int i = 0; i < rad; i++)
	{
		for (int j = 0; j < kolumn; j++)
		{
			/* Använder 16 som 0 pga. 0 finns med bland siffrorna som ska jämföras. */
			kvadrat[i][j] = BLANK;
		}
	}
}

/*
 * Funktion: generate_set
 * Användning: Genererar alla delmängder.
 * ---------------------------------------
 */
void generate_set(int **sets)
{
	int set[N2],rad = 0,sum = 0;
	/* Nollställer sets. */
	noll_kvadrat(sets,SET,N2);
	for (int i = 0; i < N1; i++)
	{
		set[0] = i;
		for (int j = 0; j < N1; j++)
		{
			if (i == j) /* Ser till så att samma siffra inte förekommer mer än en gång. */
			{
				continue;
			}
			set[1] = j;
			for (int k = 0; k < N1; k++)
			{
				if (i == k || j == k)
				{
					continue;
				}
				set[2] = k;
				for (int l = 0; l < N1; l++)
				{
					if (i == l || j == l || k == l)
					{
						continue;
					}
					set[3] = l;
					for (int m = 0; m < N2; m++)
					{
						sum += set[m];
					}
					if (sum == 30)
					{
						if (!set_exist(sets,set,SET,N2))
						{
							cpy_int_array(sets[rad],set,N2);
							rad++;
						}
					}
					sum = 0;
				}
			}
		}
	}
}

/*
 * Funktion: set_exist
 * Användning: Testar om delmängden existerar.
 * ---------------------------------------------
 */
int set_exist(int **sets,int *set,int antalSet,int storlek)
{
	for (int i = 0; i < antalSet; i++)
	{
		int lika = 0;
		for (int j = 0; j < N2; j++)
		{
			for (int k = 0; k < N2; k++)
			{
				if (sets[i][j] == set[k])
				{
					lika++;
				}
			}
		}
		if (lika == storlek)
		{
			return 1;
		}
	}
	return 0;
}

/*
 * Funktion: kombo_set
 * Användning: Kombinerar ihop alla delmängder till kvadrater.
 * -------------------------------------------------------------
 */
void kombo_set(int **kvadSet,int **sets)
{
	int kvad[N2][N2],rad = 0,platt[N1];
	/* Nollställer kvadSet. */
	noll_kvadrat(kvadSet,KVAD,N1);
	/*Kombinerar ihop delmängderna till kvadrater. */
	for (int i = 0; i < SET; i++)
	{
		/*Tilldelar sets[0] värdet på kvad[i].*/
		cpy_int_array(kvad[0],sets[i],N2);
		for (int j = 0; j < SET; j++)
		{
			if (i == j)
			{
				continue;
			}
			cpy_int_array(kvad[1],sets[j],N2);
			for (int k = 0; k < SET; k++)
			{
				if (i == k || j == k)
				{
					continue;
				}
				cpy_int_array(kvad[2],sets[k],N2);
				for (int l = 0; l < SET; l++)
				{
					if (i == l || j == l || k == l)
					{
						continue;
					}
					cpy_int_array(kvad[3],sets[l],N2);
					/* I ovanstående kod har jag plockat ut fyra delmängder. */
					platta_ut(platt,kvad,N2);
					/* Tilldelar kvadSet sina värden, alltså de mängder jag vill ha till kvadrater. */
					if (kontroll_array(platt,N1))
					{
						/* Nu ska jag testa dem för att se så de inte har samma siffra. */
						if (!set_exist(kvadSet,platt,KVAD,N1))
						{
							cpy_int_array(kvadSet[rad],platt,N1);
							rad++;
						}
					}
				}
			}
		}
	}
}

/*
 * Funktion: memory_set
 * Användning: Tilldelar minne till delmängderna.
 * -----------------------------------------------
 */
void memory_set (int **set,int rad,int kolumn)
{
	for (int i = 0; i < rad; i++)
	{
		set[i] = (int*)malloc(kolumn*sizeof(int));
	}
}

/*
 * Funktion: free_set
 * Användning: Släpper minnet till delmängderna.
 * ----------------------------------------------
 */
void free_set (int **set,int rad)
{
	for (int i = 0; i < rad; i++)
	{
		free(set[i]);
	}
}
