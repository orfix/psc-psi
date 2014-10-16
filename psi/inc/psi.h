/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009 
 * ---------------------------------------------------------------------
 * Projet 		: PSI (Pascal Subset Interpreter)
 * Module 		: PSI
 * Fonction 	: Interpréter le code
 * Fichier 		: psi.h
 * --------------------------------------------------------------------- */
#ifndef  H_PSI_MO
#define  H_PSI_MO

#include  "cl.h"
#include  "inst.h"
#include  "pile.h"
#include  "errt.h"
#include  "stdio.h"

#define  TAILLEF        64
#define  PSI_VER        "0.1"
#define  TAILLESYM 32 


typedef struct symbole
{
	enum classLex cl;       /* classe lexicale du symbole */
	char ch[TAILLESYM];     /* symbole en toute lettre */
	unsigned int val;       /* valeur si numerique */
}Symbole;

typedef struct psi
{
	char fichier[TAILLEF];  /* Nom du fichier source */
	unsigned int ligne;     /* Numero de la ligne courante */
	FILE *desc;             /* Descripteur du fichier source */
	Symbole sym;            /* Symbole courant */
	int car;                /* Caractere courant */
	enum errType erreur;    /* Indice du message d'erreur */
	//unsigned int offset;    /* Offset : adresses des variables */
	Code code;
	Pile pile;
}Psi;



Psi* psi_init(const char *nomFichier);
char psi_exec(Psi *prog); /* Time elapsed... press any key..FAIL */
/* DEBUG STEP BY STEP, hit enter == purge buffer */
void psi_quit(Psi *prog);
void psi_printUsage(const char *nomProg);

#endif
