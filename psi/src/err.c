/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009 
 * ---------------------------------------------------------------------
 * Projet 		: PSI (Pascal Subset Interpreter)
 * Module 		: ERR
 * Fonction 	: Gestionnaire d'erreur
 * Fichier 		: err.c
 * --------------------------------------------------------------------- */
#include  "errt.h"
#include  "err.h"
#include  <stdio.h>
#include  <stdlib.h>

const char *errTab[] = {
	"Aucune erreur",
	"Marque `*)' de fin de commentaire introuvable",
	"Fin de fichier attendus",

	"Numero attendu",

	"Instruction attendue",

	"", /* ERR_PARAMAUCUN */
	"`%c' Caractere inconnu",
	"", /* ERR_PARAMCAR */
	"`%s' Nombre trop grand",
	"`%s' n'est pas un nombre valide",
	"", /* ERR_PARAMSYM */
};

/* TODO: Definition d'une fonction err_symAttendus(...) */

void err_afficher(Psi *prog) 
{
	fprintf(stderr, "%s: ligne %d: ",(prog)->fichier, (prog)->ligne);
	if( prog->erreur<ERR_PARAMAUCUN) { /* Aucun parametre */
		fprintf(stderr, "%s\n", errTab[(prog)->erreur]);
	} else if( prog->erreur<ERR_PARAMCAR ) { /* caractere courant  */
		fprintf(stderr, errTab[(prog)->erreur], prog->car);
		fprintf(stderr,"\n");
	} else /*if( prog->err<ERR_PARAMSYM )*/ { /* symbole courant */
		fprintf(stderr, errTab[(prog)->erreur], prog->sym.ch);
		fprintf(stderr,"\n");
	}
}
