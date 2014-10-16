/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009 
 * ---------------------------------------------------------------------
 * Projet 		: PSI (Pascal Subset Interpreter)
 * Module 		: AS
 * Fonction 	: Analyseur Syntaxique LL(1)
 * Fichier 		: as.h
 * --------------------------------------------------------------------- */
#ifndef  H_AS_MO
#define  H_AS_MO

#include  "psi.h"

/* PROGRAM	::=	{ INST | INSTOP NUM }
 * PREMIER      ADD, ...
 * SUIVANT      
 * ----------------------------------------------------------------*/
void as_program(Psi *prog);

#endif
