/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009
 * ---------------------------------------------------------------------
 * Projet 		: PSC (Pascal Subset Compiler)
 * Module 		: AS
 * Fonction 	: Analyseur Syntaxique LL(1)
 * Fichier 		: as.c
 * --------------------------------------------------------------------- */
#include  "inst.h"
#include  "err.h"
#include  "al.h"
#include  "as.h"
#include  <stdio.h>
#include  <stdlib.h>

#define  LDAORLDL(prog)		(ISIDLOCAL(prog)? MN_LDL : MN_LDA)
#define  GETSYMADR(prog) 	(prog)->ts.tab[(prog)->sym.its].adr

static int as_testerSymCls(Psc *prog, enum classLex cl, enum errType errcl, enum classe cls,enum errType errcls)
{
	int ret = 1;

	if( prog->sym.cl==cl ) {
		if( prog->ts.tab[prog->sym.its].cls!=cls ) {
			err_signaler(prog, errcls);
			ret = 0;
		} else {
			al_symSuivant(prog);
		}
	} else if(prog->sym.cl!=CL_ERREUR) {
		err_signaler(prog, errcl);
		ret = 0;
	}
	return ret;
}

static int as_testerSym(Psc *prog, enum classLex cl, enum errType err)
{
	if( prog->sym.cl==cl ) {
		al_symSuivant(prog);
		return 1;
	} else if(prog->sym.cl!=CL_ERREUR) {
		err_signaler(prog, err);
	}
	return 0;
}

void as_program(Psc *prog)
{
	as_testerSym(prog, CL_PROGRAM, ERR_PROGRAM);
	as_testerSym(prog, CL_ID, ERR_ID);
	as_testerSym(prog, CL_PT_VIRG, ERR_PT_VIRG);
	as_block(prog);
	inst_gen(&prog->code, MN_HLT);
	as_testerSym(prog, CL_POINT, ERR_POINT);
	as_testerSym(prog, CL_FIN, ERR_FIN);
}

void as_block(Psc *prog)
{
	int adrINT;
	int adrMain;

	adrINT = prog->code.pc;
	inst_gen(&prog->code, MN_INT);
	as_consts(prog);
	as_vars(prog);
	prog->code.insts[adrINT].op = prog->offset ;
	/* Limite séparant les variables locales des globales */	
	prog->frontiere = prog->offset; 
	adrMain = prog->code.pc;
	inst_gen(&prog->code, MN_BRN);
	as_procs(prog);
	prog->code.insts[adrMain].op = prog->code.pc ;
	as_insts(prog);
}

void as_consts(Psc *prog)
{
	switch ( prog->sym.cl ) {
		case CL_CONST : al_symSuivant(prog);
						as_testerSym(prog, CL_ID, ERR_ID);
						inst_genOp(&prog->code, LDAORLDL(prog), GETSYMADR(prog));
						as_testerSym(prog, CL_EGAL, ERR_EGAL);
						as_testerSym(prog, CL_NUM, ERR_NUM);
						inst_genOp(&prog->code, MN_LDI, prog->sym.val);
						as_testerSym(prog, CL_PT_VIRG, ERR_PT_VIRG);
						inst_gen(&prog->code, MN_STO);
						while( prog->sym.cl==CL_ID ) {
							inst_genOp(&prog->code, LDAORLDL(prog), GETSYMADR(prog));
							al_symSuivant(prog);
							as_testerSym(prog, CL_EGAL, ERR_EGAL);
							as_testerSym(prog, CL_NUM, ERR_NUM);
							inst_genOp(&prog->code, MN_LDI, prog->sym.val);
							as_testerSym(prog, CL_PT_VIRG, ERR_PT_VIRG);
							inst_gen(&prog->code, MN_STO);
						}
						break;
		case CL_VAR	  :
		case CL_BEGIN :
		case CL_PROCEDURE :
		case CL_ERREUR: break;
		default       : err_signaler(prog, ERR_CONSTS_ATT); break;
	}
}

void as_vars(Psc *prog)
{
	switch ( prog->sym.cl ) {
		case CL_VAR   : al_symSuivant(prog);
						as_testerSym(prog, CL_ID, ERR_ID);
						while(prog->sym.cl==CL_VIRG) {
							al_symSuivant(prog);
							as_testerSym(prog, CL_ID, ERR_ID);
						}
						as_testerSym(prog, CL_PT_VIRG, ERR_PT_VIRG);
						break;
		case CL_BEGIN :
		case CL_PROCEDURE :
		case CL_ERREUR: break;
		default : err_signaler(prog, ERR_VARS_ATT); break;
	}
}

void as_insts(Psc *prog)
{
	as_testerSym(prog, CL_BEGIN, ERR_BEGIN);
	as_inst(prog);
	while( prog->sym.cl==CL_PT_VIRG ) {
		al_symSuivant(prog);
		as_inst(prog);
	}
	as_testerSym(prog, CL_END, ERR_END);
}

void as_inst(Psc *prog)
{
	switch ( prog->sym.cl ) {
		case CL_BEGIN  : as_insts(prog);	break;
						 /* classe ? proc : ID */
		case CL_ID     : /* TODO: URGENT, Grammaire non LL(1) */
						 if( prog->ts.tab[prog->sym.its].cls == CLS_PROC ) {
							 as_appel(prog);
						 } else {
							 as_affec(prog);
						 }
						 break;
		case CL_IF     : as_si(prog); 		break;
		case CL_WHILE  : as_tantque(prog); 	break;
		case CL_WRITE  : as_ecrire(prog); 	break;
		case CL_READ   : as_lire(prog); 	break;
		case CL_PT_VIRG:
		case CL_END    :
		case CL_POINT  :
		case CL_ERREUR : break;
		default        : err_signaler(prog, ERR_INST_ATT); break;
	}
}

void as_affec(Psc *prog)
{
	if(!as_testerSymCls(prog, CL_ID, ERR_ID, CLS_VAR, ERR_IDNVAR))
		return;
	inst_genOp(&prog->code, LDAORLDL(prog), GETSYMADR(prog));
	as_testerSym(prog, CL_AFFEC, ERR_AFFEC);
	as_expr(prog);
	inst_gen(&prog->code, MN_STO);
}

void as_si(Psc *prog)
{
	/* TODO: modifier le nom BP car inadequat dans ce contexte */
	int bp;

	as_testerSym(prog, CL_IF, ERR_IF);
	as_cond(prog);
	as_testerSym(prog, CL_THEN, ERR_THEN);
	bp = prog->code.pc;
	inst_gen(&prog->code, MN_BZE);
	as_inst(prog);
	INST_ADDBPOFFSET(prog->code, bp);
}

void as_tantque(Psc *prog)
{
	/* TODO: modifier le nom BP car inadequat dans ce contexte */
	int bp, adrCond;

	as_testerSym(prog, CL_WHILE, ERR_WHILE);
	adrCond = prog->code.pc;
	as_cond(prog);
	as_testerSym(prog, CL_DO, ERR_DO);
	bp = prog->code.pc;
	inst_gen(&prog->code, MN_BZE);
	as_inst(prog);
	inst_genOp(&prog->code, MN_BRN, adrCond);
	INST_ADDBPOFFSET(prog->code, bp);
}

void as_ecrire(Psc *prog)
{
	as_testerSym(prog, CL_WRITE, ERR_WRITE);
	as_testerSym(prog, CL_PAR_OUV, ERR_PAR_OUV);
	as_expr(prog);
	inst_gen(&prog->code, MN_PRN);
	while( prog->sym.cl==CL_VIRG ) {
		al_symSuivant(prog);
		as_expr(prog);
		inst_gen(&prog->code, MN_PRN);
	}
	as_testerSym(prog, CL_PAR_FER, ERR_PAR_FER);
}

void as_lire(Psc *prog)
{
	as_testerSym(prog, CL_READ, ERR_READ);
	as_testerSym(prog, CL_PAR_OUV, ERR_PAR_OUV);
	if(!as_testerSymCls(prog, CL_ID, ERR_ID, CLS_VAR, ERR_IDNVAR))
		return;
	inst_genOp(&prog->code, LDAORLDL(prog), GETSYMADR(prog));
	inst_gen(&prog->code, MN_INN);
	while( prog->sym.cl==CL_VIRG ) {
		al_symSuivant(prog);
		if(!as_testerSymCls(prog, CL_ID, ERR_ID, CLS_VAR, ERR_IDNVAR))
			return;
		inst_genOp(&prog->code, LDAORLDL(prog), GETSYMADR(prog));
		inst_gen(&prog->code, MN_INN);
	}
	as_testerSym(prog, CL_PAR_FER, ERR_PAR_FER);
}

void as_cond(Psc *prog)
{
	enum classLex cl;

	as_expr(prog);
	cl = prog->sym.cl;
	as_relop(prog);
	as_expr(prog);
	switch ( cl ) {
		case CL_EGAL 	 : inst_gen(&prog->code, MN_EQL); break;
		case CL_DIFF 	 : inst_gen(&prog->code, MN_NEQ); break;
		case CL_INF 	 : inst_gen(&prog->code, MN_LSS); break;
		case CL_SUP 	 : inst_gen(&prog->code, MN_GTR); break;
		case CL_INF_EGAL : inst_gen(&prog->code, MN_LEQ); break;
		case CL_SUP_EGAL : inst_gen(&prog->code, MN_GEQ); break;
		default : /* erreur geree par l'analyseur lexical */break;
	}
}

void as_relop(Psc *prog)
{
	switch ( prog->sym.cl ) {
		case CL_EGAL    : 
		case CL_DIFF    :
		case CL_INF     :
		case CL_SUP     :
		case CL_INF_EGAL:
		case CL_SUP_EGAL: al_symSuivant(prog); break;
		case CL_ERREUR  : break;
		default         : err_signaler(prog, ERR_RELOP_ATT); break;
	}
}

void as_expr(Psc *prog)
{
	as_term(prog);
	while( prog->sym.cl==CL_PLUS || prog->sym.cl==CL_MOINS ) {
		enum classLex cl = prog->sym.cl;

		al_symSuivant(prog); /* equivaut a : as_addop(prog) */
		as_term(prog);
		inst_gen(&prog->code, (cl==CL_PLUS) ? MN_ADD : MN_SUB);
	}
}

void as_addop(Psc *prog)
{
	switch ( prog->sym.cl ) {
		case CL_PLUS  :
		case CL_MOINS : al_symSuivant(prog);
		case CL_ERREUR: break;
		default       : err_signaler(prog, ERR_ADDOP_ATT); break;
	}
}

void as_term(Psc *prog)
{
	as_fact(prog);
	while( prog->sym.cl==CL_MUL || prog->sym.cl==CL_DIV ) {
		enum classLex cl = prog->sym.cl;

		al_symSuivant(prog); /* equivaut a : as_mulop(prog) */
		as_fact(prog);
		inst_gen(&prog->code, (cl==CL_MUL) ? MN_MUL : MN_DIV);
	}
}

void as_mulop(Psc *prog)
{
	switch ( prog->sym.cl ) {
		case CL_MUL   :
		case CL_DIV   : al_symSuivant(prog); 
		case CL_ERREUR: break;
		default       : err_signaler(prog, ERR_MULOP_ATT); break;
	}
}

void as_fact(Psc *prog)
{
	switch ( prog->sym.cl ) {
		case CL_PAR_OUV: al_symSuivant(prog);
						 as_expr(prog);
						 as_testerSym(prog, CL_PAR_FER, ERR_PAR_FER);
						 break;

		case CL_ID     : /* TODO: reecrire as_testerSymCls de tel sorte a 
						  	pouvoir traiter les deux cas CLS_VAR et CLS_CONST*/
						 if( prog->ts.tab[prog->sym.its].cls!=CLS_VAR &&
							 prog->ts.tab[prog->sym.its].cls!=CLS_CONST ) 
						 {
							 err_signaler(prog, ERR_IDNVARNCONST);
						 } else {
							 al_symSuivant(prog);
						 }
						 inst_genOp(&prog->code, LDAORLDL(prog), GETSYMADR(prog));
						 inst_gen(&prog->code, MN_LDV);
						 break;
		case CL_NUM    : al_symSuivant(prog); 
						 inst_genOp(&prog->code, MN_LDI, prog->sym.val);
						 break;
		case CL_ERREUR : break;
		default       : err_signaler(prog, ERR_FACT_ATT); break;
	}
}

void as_procs(Psc *prog)
{
	switch ( prog->sym.cl ) {
		case CL_PROCEDURE : while( prog->sym.cl==CL_PROCEDURE ) {
								int adrINT;

								/* Allocation de l'espace pour les variables locales */
								adrINT = prog->code.pc;
								al_symSuivant(prog);
								/* MAJ adresse de la procedure */
								GETSYMADR(prog) = prog->code.pc;
								inst_gen(&prog->code, MN_INT);

								as_testerSym(prog, CL_ID, ERR_ID);
								as_testerSym(prog, CL_PAR_OUV, ERR_PAR_OUV);

								/* SANS PARAMETRES */

								as_testerSym(prog, CL_PAR_FER, ERR_PAR_FER);
								as_testerSym(prog, CL_PT_VIRG, ERR_PT_VIRG);
								/* Remise à zéro de l'offset pour d'éventuelles variables locales */
								prog->offset = 0;
								as_consts(prog);
								as_vars(prog);
								prog->code.insts[adrINT].op = prog->offset ;
								as_insts(prog);
								as_testerSym(prog, CL_PT_VIRG, ERR_PT_VIRG);
								inst_gen(&prog->code, MN_RET);
								ts_supprimervl(prog);
							}
		case CL_BEGIN 	  :
		case CL_ERREUR	  : break;
		default 		  : err_signaler(prog, ERR_PROCS_ATT); break;
	}
}

void as_appel(Psc *prog)
{
	/* ERR_IDNPROC ne seras jamais déclenchée! masquée par ERR_AFFEC */
	if(!as_testerSymCls(prog, CL_ID, ERR_ID, CLS_PROC, ERR_IDNPROC))
		return;
	as_testerSym(prog, CL_PAR_OUV, ERR_PAR_OUV);
	/* SANS PARAMETRES */
	as_testerSym(prog, CL_PAR_FER, ERR_PAR_FER);
	inst_genOp(&prog->code, MN_CAL, GETSYMADR(prog));
}

