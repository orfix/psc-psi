/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009
 * ---------------------------------------------------------------------
 * Projet 		: PSC (Pascal Subset Compiler)
 * Module 		: INST
 * Fonction 	: Generateur de code intermediaire
 * Fichier 		: inst.c
 * --------------------------------------------------------------------- */
#include  "psc.h"
#include  "inst.h"
#include  <stdio.h>
#include  <stdlib.h>

/* TODO: Inclure les symboles au lieu des adresses 
 * 		 LDA name ; et non LDA 1
 */

void inst_init(Code *c) 
{
	c->pc = 0;
}

char inst_gen(Code *c, enum mnemonics m) 
{
	if( c->pc<TAILLECODE ) {
		c->insts[c->pc].m = m;
		c->pc++;
		return 1;
	}
	return 0;
}

char inst_genOp(Code *c, enum mnemonics m, int op)
{
	if( c->pc<TAILLECODE ) {
		c->insts[c->pc].m = m;
		c->insts[c->pc].op = op;
		c->pc++;
		return 1;
	}
	return 0;
}

void inst_debug(Code *c) 
{	/* ATTENTION : JUSTE POUR LE DEBOGAGE */
	int i;
	char *mnms[] = {
		"CAL", "INT", "LDI", "LDA", "LDL", "BRN", "BZE", "", "ADD", "SUB",
		"MUL", "DIV", "EQL", "NEQ", "GTR", "LSS", "GEQ",
		"LEQ", "PRN", "INN", "LDV", "STO", "HLT", "RET"
	};

	for( i=0 ; i<c->pc ; i++ ) {
		printf("%-5d %s",i, mnms[c->insts[i].m]);
		if( INST_WITHOP(c->insts[i].m) ) {
			printf(" %d\n", c->insts[i].op);
		} else {
			printf("\n");
		}
	}
}

void inst_save(Code *c, FILE *out) 
{
	int i;
	char *mnms[] = {
		"CAL", "INT", "LDI", "LDA", "LDL", "BRN", "BZE", "", "ADD", "SUB",
		"MUL", "DIV", "EQL", "NEQ", "GTR", "LSS", "GEQ",
		"LEQ", "PRN", "INN", "LDV", "STO", "HLT", "RET"
	};

	for( i=0 ; i<c->pc ; i++ ) {
		fprintf(out, "%s", mnms[c->insts[i].m]);
		if( INST_WITHOP(c->insts[i].m) ) {
			fprintf(out, " %d\n", c->insts[i].op);
		} else {
			fprintf(out, "\n");
		}
	}
	fputs("; Fichier genere par PSC version " PSC_VER " - (C) MO 2009\n", out);
}
