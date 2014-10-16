/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009
 * ---------------------------------------------------------------------
 * Projet 		: PSC (Pascal Subset Compiler)
 * Module 		: ERR
 * Fonction 	: Gestionnaire d'erreur
 * Fichier 		: err.h
 * --------------------------------------------------------------------- */
#ifndef  H_ERR_MO
#define  H_ERR_MO

#include  "psc.h"

#define  err_signaler(prog, err) ((prog)->sym.cl = CL_ERREUR, prog->erreur = (err))


extern const char *errTab[];

void err_afficher(Psc *prog);

#endif
