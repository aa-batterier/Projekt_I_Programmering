/*
 * Fil: head_hex.h
 * ----------------
 *  Förser projektet magisk hexadecimal kvadrat med verktyg.
 */

#ifndef _head_hex_h
#define _head_hex_h

/* Inkluderar bibliotek som behövs för detta projektet. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

/* Konstanter. */

/*
 * Konstant: N1
 * --------------
 *  Definerar talet 16 så jag inte behöver
 *  skriv 16 så offta och kan lätt ändra det.
 */
#define N1 16

/*
 * Konstant: N2
 * -------------
 *  Definerar talet 4 så jag inte behöver
 *  skriva 4 så ofta och kan lätt ändra det.
 */
#define N2 4

/*
 * Konstant: SET
 * --------------
 *  Definerar antalet unika delmängder där summan blir 30.
 */
#define SET 86

/*
 * Konstant: KVAD
 * ---------------
 *  Definerar antalet unika kvadrater där summan av varje rad blir 30.
 */
#define KVAD 9408

/*
 * Konstant: MAX_ARRAY
 * --------------------
 *  Definerar max antal tecken man kan skriva in.
 */
#define MAX_ARRAY 100

/*
 * Konstant: MAX_VAR
 * -------------------
 *  Definerar max antal variabler som programmet
 *  kan hålla i minne.
 */
#define MAX_VAR 200

/*
 * Konstant: BLANK
 * ----------------
 *  Definerar vilket nummer blank tecknet ska ha.
 *  Jag har satt det just nu till 16, dock
 *  går det att ändra till vilket tecken
 *  som helst över 15.
 */
#define BLANK 16 /* Nummer 16 görs om till '_' vid utskrift. */

/* Typdefinitioner. */

/*
 * Typdefinition: variableT
 * --------------------------
 *  Struckten variable är till för att
 *  kunna lagra kvadrater i variabler.
 */
typedef struct
{
	int *kvadrat,klen,nlen;
	char *namn;
}variableT;

/* Funktion prototyper. */

/* Funktioner i read_hex.c. */

/*
 * Funktion: read_line
 * Användning: Läsa in en rad.
 * ------------------------------
 *  read_line läser in en rad från där
 *  fil pekaren from pekar till.
 *  read_line läser det till fältet input.
 *  Om läsningen avbryts retunerar read_line 0.
 *  Vid lyckad inläsing retunerar read_line 1.
 */
int read_line(char *input,FILE *from);

/*
 * Funktion: remove_nl
 * Användning: Ta bort ny rad tecknet i slutet på en sträng. 
 * ----------------------------------------------------------
 *  remove_nl tar bort ny rad tecknet i slutet på en sträng.
 *  remove_nl retunerar 0 om dn inte behöver ta bort ny rad
 *  och retunerar 1 när den tar bort ny rad.
 */
int remove_nl(char *input);

/*
 * Funktion: skip_line
 * Användning: Hoppar över en hel rad.
 * ------------------------------------
 *  skip_line hoppar över en hel rad via
 *  en loop sats tills den kommer till
 *  ny rad tecken eller EOF.
 */
void skip_line(void);

/*
 * Funktion: remove_white
 * Användning: Tar bort alla vita tecken ur fältet som skickas in.
 * ----------------------------------------------------------------
 *  remove_white tar bort alla vita tecken ur det fältet som
 *  skickas in.
 */
void remove_white(char *input);

/*
 * Funktion: ctoh
 * Användning: Gör om tecken fält till heltals fält.
 * --------------------------------------------------
 *  ctoh skriver ut de tecken som hämtas från
 *  tecken fältet from som heltal till
 *  heltals fältet to.
 *  ctoh retunerar 1 vid lyckad läsning
 *  och 0 vid misslyckad läsning.
 */
int ctoh(int *to,const char *from);

/*
 * Funktion: read_input
 * Användning: Läser in rad från stdin.
 * -------------------------------------
 *  read_input läser in en rad från stdin.
 *  read_input retunerar 0 vid misslyckad
 *  inläsning och 1 vid lyckad inläsning.
 */
int read_input(int to[]);

/*
 * Funktion: read_file
 * Användning: Läser in en rad från fil.
 * --------------------------------------
 *  read_file läser in en rad från den fil
 *  som specificeras vid namn till fältet to.
 *  read_file retunerar 0 vid misslyckad
 *  inläsning och 1 vid lyckad inläsning.
 */
int read_file(variableT *varPool,char *namn);

/*
 * Funktion: read_int
 * Användning: Läser in heltal från stdin.
 * ----------------------------------------
 *  read_int läser in heltal från terminalen.
 *  read_int retunerar 0 vid misslyckad
 *  inläsning och 1 vid lyckad inläsning.
 */
int read_int(void);

/* Funktioner i write_hex.c. */

/*
 * Funktion: itoc
 * Användning: Gör om heltal till tecken.
 * ---------------------------------------
 *  itoc gör om heltal till tecken som funktionen
 *  hämtar från fältet from och skriver tecknen
 *  till fältet to.
 */
void itoc(char to[], const int from[], int n);

/*
 * Funktion: write_stdout
 * Användning: Skriver ut kvadrater till stdout.
 * ----------------------------------------------
 *  write_stdout skriver ut de kvadrater
 *  som skickas in till funktoionen som parameter
 *  till stdout.
 */
void write_stdout(int kvadrat[],int rad,int kolumn);

/*
 * Funktion: write_file
 * Användning: Skriver ut kvadraten till fil.
 * -------------------------------------------
 *  write_file skriver ut kvadraten till den
 *  fil som specificeras via namn.
 *  write_file retunerar 0 om funktionen misslyckas
 *  och 1 om funktionen lyckas.
 */
int write_file(variableT *varPool, const char namn[]);

/*
 * Funktion: write_set
 * Använding: Skriver ut delmängder.
 * -----------------------------------
 *  write_set skriver ut delmängdern.
 *  Kan inte använda write_stdout pga.
 *  write_stdout skriver bara ut 4x4,
 *  men delmängder är bara 1x4.
 */
void write_set(int **set,int rad,int kolumn);

/* Funktioner i kontroll.c. */

/*
 * Funktion: kontroll_array
 * Användning: Kontrollerar att kvadraten endast har en siffra av varje sort.
 * ---------------------------------------------------------------------------
 *  kontroll_array kontrollerar så att alla siffror finns med
 *  i kvadraten. Om inte alla siffor finns med retuneras 0.
 *  Om alla siffror finns med retuneras 1.
 */
int kontroll_array(const int f[],int n);

/*
 * Funktion: kontroll_rad
 * Användning: Kontrollerar att varje rad i kvadraten har summan 30.
 * ------------------------------------------------------------------
 *  kontroll_rad kontrollerar att varje rad i
 *  kvadraten har summan 30. Om summan inte är
 *  30 i någon av raderna retuneras 0, Om
 *  alla rader är lika med 30 retuneras 1.
 */
int kontroll_rad(const int kvadrat[]);

/*
 * Funktion: kontroll_kolumn
 * Användning: Kontrollerar att summman av varje kolumn är 30.
 * ------------------------------------------------------------
 *  kontroll_kolumn kontrollerar att varje kolumn
 *  har summan 30. Om någon kolumn inte har summan
 *  30 retuneras 0. Om varje kolumn har summan 30
 *  retuneras 1.
 */
int kontroll_kolumn(const int kvadrat[]);

/*
 * Funktion: kontroll_vtillh
 * Användning: Kontrollerar att diagonalen från vänster till höger har summan 30.
 * --------------------------------------------------------------------------------
 *  kontroll_vtillh kontrollerar att diagonalen från
 *  vänster till höger har summan 30.
 *  Om diagonalen inte har summan 30 retuneras 0.
 *  Om diagonalen har summan 30 retuneras 1.
 */
int kontroll_vtillh(const int kvadrat[]);

/*
 * Funktion: kontroll_htillv
 * Användning: Kontrollerar att diagonalen från höger till vänster har summan 30.
 * --------------------------------------------------------------------------------
 *  kontroll_htillv kontrollerar att diagonalen från
 *  höger till vänster har summan 30.
 *  Om diagonalen inte har summan 30 retuneras 0.
 *  Om diagonalen har summan 30 retuneras 1.
 */
int kontroll_htillv(const int kvadrat[]);

/*
 * Funktion: kontroll_kvadrat
 * Användning: Kontrollerar att hela kvadraten är magisk.
 * -------------------------------------------------------
 *  kontroll_kvadrat kontrollerar att hela kvadraten är magisk.
 *  kontroll_kvadrat är ett ihop slag av ovanstående funktioner.
 *  Om kvadraten inte är magisk retuneras 0.
 *  Om kvadraten är magisk retuneras 1.
 */
int kontroll_kvadrat(const int kvadrat[]);

/* Funktioner i misc.c. */

/*
 * Funktion: platta_ut
 * Användning: Plattar ut en kvadrat till ett fält.
 * -------------------------------------------------
 *  platta_ut plattar ut en kvadrat till ett fält.
 *  Kvadraten som skickas in plattas ut till fältet
 *  platt.
 */
void platta_ut(int platt[],int kvadrat[][N2],int n);

/*
 * Funktion: cpy_int_array
 * Användning: Kopierar ett heltals fält till ett annat heltals fält.
 * -------------------------------------------------------------------
 *  cpy_int_array kopierar heltals fältet from till heltals fältet to.
 */
void cpy_int_array(int *to,int *from,int n);

/*
 * Funktion: cpy_str_array
 * Användning: Kopierar en sträng till en annan sträng.
 * -----------------------------------------------------
 *  cpy_str_array kopierar en sträng till en annan sträng.
 */
void cpy_str_array(char *to,char *from);

/*
 * Funktion: slump
 * Användning: Ersätter n st slump valda siffror med blank tecken(X).
 * -------------------------------------------------------------------
 *  slump ersätter n stycken upp till 8 siffor med blank tecken (X).
 */
void slump(int kvadrat[],int n);

/*
 * Funktion: skapa_variable
 * Användning: Skapar en variabel av typen varibleT.
 * --------------------------------------------------
 *  skapa_variable tilldelar pekarna i struckten 
 *  variableT dynamiska minnes utrymmen.
 */
int skapa_variable(char *namn,int *kvadrat,variableT *var);

/*
 * Funktion: free_pool
 * Användning: Fri gör en pool med variabler.
 * ---------------------------------
 *  free_pool släpper det dynamiska
 *  minnet som pekarna i structen
 *  variableT pekar på i varje variabel
 *  i poolen.
 */
void free_pool(variableT *varPool);

/*
 * Funktion: antal_variabler
 * Användning: Håller koll på hur många variabler som används.
 * --------------------------------------------------------------
 *  antal_variabler håller koll på hur många variabler som används.
 *  antal_variabler retunerar antalet variabler - 1 och (-1) vid fel.
 *  Skicka in 'n' vid skapandet av ny variabel och 'r' när en variabel
 *  tas bort. 'a' för att enbart retuenera antalet - 1.
 *  antal_variabler start på -1 pga. indexering i fält.
 */
int antal_variabler(char val);

/*
 * Funktion: hitta_variabler
 * Användning: Hittar den variablen man letar efter.
 * --------------------------------------------------
 *  hitta_variabler letar efter namnet på den variabeln
 *  man vill ha i fältet med variabler som skickas in.
 *  När hitta_variabler hittar variabeln man söker efter
 *  retuneras den, om variablen inte hittas retuneras NULL.
 */
int hitta_variabler(variableT *var,char *namn);

/* Funktioner i meny.c.
 * Funktionerna i meny.c är egentligen ur flyttade ur
 * switch case satsen för att underlätta.
 * De ska bara användas i meny systemet. */

/*
 * Funktion: meny
 * Användning: Skapar en meny.
 * ----------------------------
 *  meny skapar en meny vilket man gör valen ifrån.
 *  meny retunerar 0 när användaren vill avsluta.
 *  meny retunerar 1 om allt gick bra.
 *  meny retunerar -1 vid fel. 
 */
//int meny(char val,variableT *varPool);

/*
 * Funktion: read_terminal
 * Användning: Läser in kvadrat från terminalen.
 * ----------------------------------------------
 *  Läser in en kvadrat från terminalen och
 *  skapar och placerar den i en variabel.
 *  Retunerar 1 om funktionen lyckas och 0 om funktionen misslyckas.
 */
int read_terminal(variableT *varPool);

/*
 * Funktion: read_file_kvadrat
 * Användning: Läser in kvadrater från fil.
 * -----------------------------------------
 *  Läser in kvadrater från fil till och
 *  skapar och placerar kvadraterna i minnet.
 *  Retunerar 1 om funktionen lyckas och 0 om funktionen misslyckas.
 */
int read_file_kvadrat(variableT *var);

/*
 * Funktion: test_kvadrat
 * Användning: Testar att kvadraten stämmer.
 * ------------------------------------------
 *  Testar om kvadraten som man skriver in
 *  namnet på är en magisk kvadrat.
 *  Retunerar 1 om funktionen lyckas och 0 om funktionen misslyckas.
 */
int test_kvadrat(variableT *varPool);

/*
 * Funktion: write_terminal
 * Användning: Skriver ut kvadraten till terminalen.
 * --------------------------------------------------
 *  Skriver ut till stdout kvadraten som
 *  man skriver in namnet på.
 *  Retunerar 1 om funktionen lyckas och 0 om funktionen misslyckas.
 */
int write_terminal(variableT *varPool);

/*
 * Funktion: write_to_file
 * Användning: Skriver ut kvadraterna till fil.
 * ---------------------------------------------
 *  Skriver ut alla kvadrater som finns i minnet
 *  till filen som man pekar ut, skapar filen
 *  om den inte finns, annars lägger till i slutet av filen.
 *  Retunerar 1 om funktionen lyckas och 0 om funktionen misslyckas.
 */
int write_to_file(variableT *varPool);

/*
 * Funktion: spel
 * Användning: Fylla i de tomma luckorna i kvadraten.
 * ---------------------------------------------------
 *  Startar ett spel där man ska fylla i rätt siffror
 *  i de tomrum så kvadraten blir magisk.
 *  Retunerar 1 om funktionen lyckas och 0 om funktionen misslyckas.
 */
int spel(variableT *varPool);

/* Funktioner i set.c. */

/*
 * Funktion: generate_set
 * Användning: Genererar alla delmängder.
 * ---------------------------------------
 *  generate_set genererar alla delmängder.
 *  Med en delmängd menas fyra olika siffror
 *  där summan blir 30.
 */
void generate_set(int **b);

/*
 * Funktion: set_exist
 * Användning: Testar om delmängden existerar.
 * ---------------------------------------------
 *  set_exist kollat om ett visst fält(set) finns i
 *  ett fält med fält(sets).
 *  Om fältet existerar så retuneras 1, om fältet inte
 *  existerar så retuneras 0.
 */
int set_exist(int **sets,int *set,int antalSet,int storlek);

/*
 * Funktion: kombo_set
 * Användning: Kombinerar ihop alla delmängder till kvadrater.
 * -------------------------------------------------------------
 *  kombo_set kombinerar ihop alla delmängder till kvadrater.
 *  Kravet på kvadraterna är att en siffra får inte förekomma mer
 *  än en gång.
 */
void kombo_set(int **a,int **set);

/*
 * Funktion: memory_set
 * Användning: Tilldelar minne till delmängderna.
 * -----------------------------------------------
 *  memory_set tilldelar minne till alla delmängder.
 */
void memory_set (int **set,int rad,int kolumn);

/*
 * Funktion: free_set
 * Användning: Släpper minnet till delmängderna.
 * ----------------------------------------------
 *  free_set släpper allt minne till delmängderna.
 */
void free_set (int **set,int rad);

#endif
