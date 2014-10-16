/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009
 * ---------------------------------------------------------------------
 * Projet 		: PSC (Pascal Subset Compiler)
 * Module 		: INST
 * Fonction 	: Generateur de code intermediaire
 * Fichier 		: inst.h
 * --------------------------------------------------------------------- */
#ifndef  H_INST_MO
#define  H_INST_MO

#include  <stdio.h>

#define  TAILLECODE 8192

enum mnemonics 
{
	MN_CAL, MN_INT, MN_LDI, MN_LDA, MN_LDL, MN_BRN, MN_BZE,
	MN_WITHOP, 
	MN_ADD, MN_SUB, MN_MUL, MN_DIV, MN_EQL, MN_NEQ, MN_GTR,
	MN_LSS, MN_GEQ, MN_LEQ, MN_PRN, MN_INN, MN_LDV, MN_STO,
	MN_HLT, MN_RET
};

typedef struct inst
{
	enum mnemonics m;
	int op;
}Inst;

typedef struct code
{
	Inst insts[TAILLECODE];
	int pc;
}Code;

#define  INST_ADDBPOFFSET(code, bp)	(code).insts[bp].op = (code).pc
#define  INST_WITHOP(inst)		(inst<MN_WITHOP)

void inst_init(Code *c);
char inst_gen(Code *c, enum mnemonics m);
char inst_genOp(Code *c, enum mnemonics m, int op);
void inst_debug(Code *c);
void inst_save(Code *c, FILE *out);

#endif
