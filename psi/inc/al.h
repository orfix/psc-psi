/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009 
 * ---------------------------------------------------------------------
 * Projet 		: PSI (Pascal Subset Interpreter)
 * Module 		: AL
 * Fonction 	: Analyseur Lexicale
 * Fichier 		: al.h
 * --------------------------------------------------------------------- */
#ifndef  H_AL_MO
#define  H_AL_MO

#include  "psi.h"

#define  TAILLESYM 32

#define  al_lireCar(prog) 	(prog->car = fgetc(prog->desc))

void al_symSuivant(Psi *prog);
void al_dbg_sym(Psi *prog);

//extern const char *dbg_cl[];

#endif  
