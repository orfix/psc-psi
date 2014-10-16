/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009 
 * ---------------------------------------------------------------------
 * Projet 		: PSI (Pascal Subset Interpreter)
 * Module 		: INST
 * Fonction 	: Chargement du code en mémoire
 * Fichier 		: inst.c
 * --------------------------------------------------------------------- */
#include  "psi.h"
#include  "inst.h"
#include  <stdio.h>
#include  <stdlib.h>

/* TODO: Inclure les symboles au lieu des adresses 
 * 		 LDA name ; et non LDA 1
 */

void inst_init(Code *c) 
{
	c->pc = 0;
	c->bp = 0;
}

char inst_gen(Code *c, enum classLex m) 
{
	if( c->pc<TAILLECODE ) {
		c->insts[c->pc].m = m;
		c->pc++;
		return 1;
	}
	return 0;
}

char inst_genOp(Code *c, enum classLex m, int op)
{
	if( c->pc<TAILLECODE ) {
		c->insts[c->pc].m = m;
		c->insts[c->pc].op = op;
		c->pc++;
		return 1;
	}
	return 0;
}

void inst_debug(Code *c, int i) 
{	/* ATTENTION : JUSTE POUR LE DEBOGAGE */
	static const char *mnms[] = { "ADD", "BRN", "BZE", "CAL", "DIV", 
								  "EQL", "GEQ", "GTR", "HLT", "INN",
								  "INT", "LDA", "LDI", "LDL", "LDV",
								  "LEQ", "LSS", "MUL", "NEQ", "PRN",
								  "RET", "STO", "SUB" };

	printf("%-5d %s",i, mnms[c->insts[i].m]);
	if( WITHOP(c->insts[i].m) ) {
		printf(" %d\n", c->insts[i].op);
	} else {
		printf("\n");
	}
}
