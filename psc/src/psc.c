/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009
 * ---------------------------------------------------------------------
 * Projet 		: PSC (Pascal Subset Compiler)
 * Module 		: PSC
 * Fonction 	: Principales structures de données
 * Fichier 		: al.c
 * --------------------------------------------------------------------- */
#include  "inst.h"
#include  "psc.h"
#include  "err.h"
#include  "al.h"
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>

Psc* psc_init(const char *nomFichier) 
{
	Psc *prog = malloc(sizeof *prog);

	if( prog!=NULL && nomFichier!=NULL  ) {
		prog->fichier[0] = '\0';
		strncat(prog->fichier, nomFichier, TAILLEF);
		if( (prog->desc = fopen(prog->fichier, "r"))!=NULL) {
			err_signaler(prog, ERR_AUCUNE);
			inst_init(&prog->code);
			prog->ligne = 1;
			prog->offset = 0;
			prog->frontiere = 0;
			al_lireCar(prog);
			ts_init(&prog->ts);
			al_symSuivant(prog);
		} else {
			free(prog);
			prog = NULL;
		}
	}
	return prog;
}

void psc_quit(Psc *prog) 
{
	if( prog!=NULL ) {
		if( prog->desc!=NULL ) {
			fclose(prog->desc);
		}
		free(prog);
	}
}

void psc_printUsage(const char *nomProg) 
{
	printf("USAGE : %s [OPTION]... [FICHIER]...\n",nomProg);
	puts  ("");
	puts  ("   -h : Afficher cette aide");
	puts  ("   -t : Lister le contenu de la table des symboles");
	puts  ("   -s : Stoper la compilation en phase d'analyse lexicale");
	puts  ("   -l : Lister le pseudo-code genere");
	//puts  ("   -o : Fichier de sortie pour le P-Code");
	puts  ("");
	puts  ("Pascal Subset Compiler PSC version " PSC_VER " - (C) MO 2009");
}

