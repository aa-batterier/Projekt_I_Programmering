/*
 * Information om utvecklingen.
 * -----------------------------
 *  Inledande skapare: Andreas Johansson.
 *  Datum då det skapades:
 *  Senaste uppdateringen av: Andreas Johansson.
 *  Uppdaterings datum:
 */

/*
 * Fil: kontroll.c
 * ----------------
 */

#include "head_hex.h"

/*
 * Funktion: kontroll_array
 * Användning: Kontrollerar att kvadraten endast har en siffra av varje sort.
 * ---------------------------------------------------------------------------
 */
int kontroll_array(const int f[],int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				continue;
			}
			else if (f[i] == f[j])
			{
			//	fprintf(stderr,"Samma siffra förekommer mer än en gång.\n");
				return 0;
			}
		}
	}
	return 1;
}

/*
 * Funktion: kontroll_rad
 * Användning: Kontrollerar att varje rad i kvadraten har summan 30.
 * ------------------------------------------------------------------
 */
int kontroll_rad(const int kvadrat[N1])
{
	int sum = 0;
	for (int i = 0; i < N2; i++)
	{
		for (int j = i*N2; j < i*N2+N2; j++)
		{
			sum += kvadrat[j];
		}
		if (sum != 30)
		{
		//	fprintf(stderr,"En rad är inte lika med 30.\n");
			return 0;
		}
		sum = 0;
	}
	return 1;
}

/*
 * Funktion: kontroll_kolumn
 * Användning: Kontrollerar att summman av varje kolumn är 30.
 * ------------------------------------------------------------
 */
int kontroll_kolumn(const int kvadrat[N1])
{
	int sum = 0;
	for (int i = 0; i < N2; i++)
	{
		for (int j = i; j < N1; j += N2)
		{
			sum += kvadrat[j];
		}
		if (sum != 30)
		{
		//	fprintf(stderr,"En kolumn är inte lika med 30.\n");
			return 0;
		}
		sum = 0;
	}
	return 1;
}

/*
 * Funktion: kontroll_vtillh
 * Användning: Kontrollerar att diagonalen från vänster till höger har summan 30.
 * --------------------------------------------------------------------------------
 */
int kontroll_vtillh(const int kvadrat[N1])
{
	int sum = 0;
	for (int i = 0; i < N1; i += 5)
	{
		sum += kvadrat[i];
	}
	if (sum != 30)
	{
	//	fprintf(stderr,"Diagonalen vänster till höger är inte lika med 30.\n");
		return 0;
	}
	return 1;
}

/*
 * Funktion: kontroll_htillv
 * Användning: Kontrollerar att diagonalen från höger till vänster har summan 30.
 * --------------------------------------------------------------------------------
 */
int kontroll_htillv(const int kvadrat[N1])
{
	int sum = 0;
	for (int i = 12; i > 0; i -= 3)
	{
		sum += kvadrat[i];
	}
	if (sum != 30)
	{
	//	fprintf(stderr,"Diagonalen höger till vänster är inte lika med 30.\n");
		return 0;
	}
	return 1;
}

/*
 * Funktion: kontroll_kvadrat
 * Användning: Kontrollerar att hela kvadraten är magisk.
 * -------------------------------------------------------
 */
int kontroll_kvadrat(const int kvadrat[N1])
{
	if (kontroll_array(kvadrat,N1) && kontroll_rad(kvadrat) && kontroll_kolumn(kvadrat) && kontroll_vtillh(kvadrat) && kontroll_htillv(kvadrat))
	{
		return 1;
	}
	return 0;
}
