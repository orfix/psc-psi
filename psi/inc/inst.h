/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009 
 * ---------------------------------------------------------------------
 * Projet 		: PSI (Pascal Subset Interpreter)
 * Module 		: INST
 * Fonction 	: Chargement du code en mémoire
 * Fichier 		: inst.h
 * --------------------------------------------------------------------- */
#ifndef  H_INST_MO
#define  H_INST_MO

#include  "cl.h"
#include  <stdio.h>

#define  TAILLECODE 8192

typedef struct inst
{
	enum classLex m;
	int op;
}Inst;

typedef struct code
{
	Inst insts[TAILLECODE];
	int pc;
	int bp;
}Code;

#define  INST_ADDBPOFFSET(code, bp)	(code).insts[bp].op = (code).pc
#define  INST_WITHOP(inst)		(inst<MN_WITHOP)

void inst_init(Code *c);
char inst_gen(Code *c, enum classLex m);
char inst_genOp(Code *c, enum classLex m, int op);
void inst_debug(Code *c, int i);

#endif
