/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009
 * ---------------------------------------------------------------------
 * Projet 		: PSC (Pascal Subset Compiler)
 * Module 		: AL
 * Fonction 	: Analyseur Lexicale
 * Fichier 		: al.h
 * --------------------------------------------------------------------- */
#ifndef  H_AL_MO
#define  H_AL_MO

#include  "psc.h"

#define  NELEM(t)   (sizeof(t)/sizeof(*t))
#define  ISIDLOCAL(prog) 	(prog->sym.its > prog->frontiere)
#define  al_lireCar(prog) 	(prog->car = fgetc(prog->desc))

void al_symSuivant(Psc *prog);
void al_dbg_sym(Psc *prog);

#endif  
