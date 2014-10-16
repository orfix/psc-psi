/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009 
 * ---------------------------------------------------------------------
 * Projet 		: PSI (Pascal Subset Interpreter)
 * Module 		: AL
 * Fonction 	: Analyseur Lexicale
 * Fichier 		: al.c
 * --------------------------------------------------------------------- */
#include  "cl.h"
#include  "al.h"
#include  "psi.h"
#include  "err.h"
#include  <limits.h> /* INT_MAX */
#include  <ctype.h>
#include  <string.h>
#include  <stdio.h>
#include  <stdlib.h>

#define  NELEM(tab)             (sizeof(tab) / sizeof(*tab))

static void al_sauterBlanc(Psi *prog) 
{
	while(isspace(prog->car)) {
		if( prog->car=='\n' ) prog->ligne++;
		al_lireCar(prog);
	}
}

static void al_sauterCom(Psi *prog) 
{
	do {
		al_lireCar(prog);
	}while( prog->car!='\n' && prog->car!=EOF);
}


static void al_lireNum(Psi *prog)
{
	unsigned int i = 0;

	prog->sym.val = 0;
	do {
		prog->sym.val = prog->sym.val * 10 + prog->car - '0';
		prog->sym.ch[i++] = prog->car;
		al_lireCar(prog);
	}while( isdigit(prog->car) && prog->car!=EOF && prog->sym.val<INT_MAX);
	//prog->sym.ch[i] = '\0';	
	if( isalpha(prog->car) ) { /* Identifiant commencant par des chiffres */
		err_signaler(prog, ERR_NUMINVALIDE);
	} else if(prog->sym.val>INT_MAX) { /* Numéro trop Grand */
		err_signaler(prog, ERR_GRANDNUM);
	} else {
		prog->sym.cl = CL_NUM;
	}
}

int bsStrcmp(const void *s1, const void *s2) 
{
	const char *s1_ = *(const char**) s1;
	const char *s2_ = *(const char**) s2;


	//printf("%s - %s\n", s1, s2);
	//printf(">>%s - %s\n", s1_, s2_);
	return strcmp(s1_, s2_);
}


static void al_lireInst(Psi *prog) 
{
	unsigned int i = 0;
	char *key = prog->sym.ch;

	do {
		prog->sym.ch[i++] = prog->car;
		al_lireCar(prog);
	}while( isalnum(prog->car) && prog->car!=EOF && i<TAILLESYM-1);
	prog->sym.ch[i] = '\0';

	if( i>3 ) { /* Petite optimisation, tout les mots cles sont sur 3 chars */
		err_signaler(prog, ERR_MOTCLE);
	} else {
		static const char *motscles[] = { "ADD", "BRN", "BZE", "CAL", "DIV", 
										  "EQL", "GEQ", "GTR", "HLT", "INN",
										  "INT", "LDA", "LDI", "LDL", "LDV",
										  "LEQ", "LSS", "MUL", "NEQ", "PRN",
										  "RET", "STO", "SUB" };
		char **match = bsearch(&key,motscles, NELEM(motscles), sizeof(char*), bsStrcmp);

		if( match!=NULL ) {
			prog->sym.cl = (*match - *motscles) / 4; /* 4 == strlen(motscles[0]+1 */
		} else {
			err_signaler(prog, ERR_MOTCLE);
		}
	}
}

void al_symSuivant(Psi *prog) 
{
	memset(prog->sym.ch, '\0', TAILLESYM);
	/* Sauter les caractères blancs */
	al_sauterBlanc(prog);
	/* Récupération du symbole */   
	if( isalpha(prog->car) ) {
		al_lireInst(prog);
	} else if( isdigit(prog->car)) {
		al_lireNum(prog);
	} else if( prog->car==';') {
		al_sauterCom(prog);
		al_symSuivant(prog);
	} else if( prog->car==EOF ){
		prog->sym.cl = CL_FIN;
	} else {
		prog->sym.ch[0] = prog->car;
		err_signaler(prog, ERR_CARINC);
	}
}

void al_dbg_sym(Psi *prog) 
{
	static const char *dbg_cl[] = {
		"Instruction ADD", "Instruction BRN", "Instruction BZE",
		"Instruction CAL", "Instruction DIV", "Instruction EQL",
		"Instruction GEQ", "Instruction GTR", "Instruction HLT",
		"Instruction INN", "Instruction INT", "Instruction LDA",
		"Instruction LDI", "Instruction LDL", "Instruction LDV",
		"Instruction LEQ", "Instruction LSS", "Instruction MUL",
		"Instruction NEQ", "Instruction PRN", "Instruction RET",
		"Instruction STO", "Instruction SUB",

		"","Numero", "Fin de fichier", "erreur"
	};
	char val[64] = "-";

	if( prog->sym.cl==CL_NUM ) {
		sprintf(val, "%d", prog->sym.val);
	}
	printf("%-10s\t%-15s\t%s\n",prog->sym.ch, dbg_cl[prog->sym.cl], val);
}

