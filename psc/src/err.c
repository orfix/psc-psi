/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009
 * ---------------------------------------------------------------------
 * Projet 		: PSC (Pascal Subset Compiler)
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
	"`=' attendu",

	"`PROGRAM' attendu",
	"`BEGIN' attendu",
	"`IF' attendu",
	"`THEN' attendu",
	"`WHILE' attendu",
	"`DO' attendu",
	"`WRITE' attendu",
	"`READ' attendu",
	"`END' attendu",

	"Identifiant attendu",
	"`;' attendu",
	"`.' attendu",
	"Numero attendu",
	"`:=' attendu",
	"`(' attendu",
	"`)' attendu",

	"`PROCEDURE', `BEGIN' attendus",
	"`BEGIN', `IF', `WHILE', `WRITE', `READ', `END', `;', `.', Identifiant,  attendus",
	"`CONST', `VAR', `PROCEDURE', `BEGIN' attendus",
	"`VAR', `PROCEDURE', `BEGIN' attendus",
	"`=', `<>', `<', `>', `<=', `>=' attendus",
	"`+', `-' attendus",
	"`*', `/' attendus",
	"`(', Identifiant, numero attendus",
	"Table des symboles pleine",
	"", /* ERR_PARAMAUCUN */
	"`%c' Caractere inconnu",
	"", /* ERR_PARAMCAR */
	"`%s' Identifiant invalide",	
	"`%s' Numero trop grand",
	"`%s' Identifiant trop long",
	"`%s' Identifiant redeclare",
	"`%s' Identifiant non declare",

	"`%s' n'est pas une variable",
	"`%s' n'est ni une variable ni une constante",
	"`%s' n'est pas une procédure",
	"", /* ERR_PARAMSYM */
};

/* TODO: Definition d'une fonction err_symAttendus(...) */

void err_afficher(Psc *prog) 
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
