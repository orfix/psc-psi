/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009
 * ---------------------------------------------------------------------
 * Projet 		: PSC (Pascal Subset Compiler)
 * Module 		: PSC
 * Fonction 	: Principales structures de données
 * Fichier 		: al.h
 * --------------------------------------------------------------------- */
#ifndef  H_PSC_MO
#define  H_PSC_MO

#include  "inst.h"
#include  "errt.h"
#include  "cl.h"
#include  "ts.h"
#include  <stdio.h>

#define  TAILLEF 	64
#define  PSC_VER	"0.1"

typedef struct symbole
{
	enum classLex cl;	/* classe lexicale du symbole */
	char ch[TAILLESYM];	/* symbole en toute lettre */
	unsigned int val;	/* valeur si numerique */
	unsigned int its;	/* indice du symbole dans la TS */
}Symbole;

typedef struct psc
{
	char fichier[TAILLEF];	/* Nom du fichier source */
	unsigned int ligne;		/* Numero de la ligne courante */
	FILE *desc;				/* Descripteur du fichier source */
	Symbole sym;			/* Symbole courant */
	int car;				/* Caractere courant */
	enum errType erreur;	/* Indice du message d'erreur */
	TabSym ts;				/* Table des symboles */
	unsigned int offset;	/* Offset : adresses des variables */
	unsigned int frontiere;	/* Frontiere entre domaine globale et locale */
	Code code;
}Psc;

Psc* 	psc_init(const char *nomFichier);
void 	psc_quit(Psc *prog);
void 	psc_printUsage(const char *nomProg);

#endif 
