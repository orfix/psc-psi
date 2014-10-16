/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009 
 * ---------------------------------------------------------------------
 * Projet 		: PSI (Pascal Subset Interpreter)
 * Module 		: ERR
 * Fonction 	: Gestionnaire d'erreur
 * Fichier 		: err.h
 * --------------------------------------------------------------------- */
#ifndef  H_ERR_MO
#define  H_ERR_MO

#include  "psi.h"

#define  err_signaler(prog, err) ((prog)->sym.cl = CL_ERREUR, prog->erreur = (err))

extern const char *errTab[];

void err_afficher(Psi *prog);

#endif
