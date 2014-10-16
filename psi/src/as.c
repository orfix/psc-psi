/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009 
 * ---------------------------------------------------------------------
 * Projet 		: PSI (Pascal Subset Interpreter)
 * Module 		: AS
 * Fonction 	: Analyseur Syntaxique LL(1)
 * Fichier 		: as.c
 * --------------------------------------------------------------------- */
#include  "err.h"
#include  "inst.h"
#include  "al.h"
#include  "cl.h"
#include  "as.h"
#include  <stdio.h>
#include  <stdlib.h>


void as_program(Psi *prog)
{
	while(prog->sym.cl!=CL_FIN && prog->sym.cl!=CL_ERREUR ) {
		if( prog->sym.cl<CL_INST ) { /* Si c'est une instruction */
			if( WITHOP(prog->sym.cl) ) {
				enum classLex cl = prog->sym.cl;

				al_symSuivant(prog);
				if( prog->sym.cl==CL_NUM ) {
					inst_genOp(&prog->code, cl, prog->sym.val);
					al_symSuivant(prog);
				} else {
					err_signaler(prog, ERR_NUM);
				}
			} else {
				inst_gen(&prog->code, prog->sym.cl);
				al_symSuivant(prog);
			}
		} else {
			err_signaler(prog, ERR_MOTCLE);
		}
	}
}
