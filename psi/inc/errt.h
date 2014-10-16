/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009 
 * ---------------------------------------------------------------------
 * Projet 		: PSI (Pascal Subset Interpreter)
 * Module 		: ERR
 * Fonction 	: Gestionnaire d'erreur
 * Fichier 		: errt.c
 * --------------------------------------------------------------------- */
#ifndef  H_ERRT_MO
#define  H_ERRT_MO

enum errType {
	ERR_AUCUNE,
	ERR_COMM,
	ERR_FIN,

	ERR_NUM,

	ERR_MOTCLE,


	ERR_PARAMAUCUN,
	ERR_CARINC,
	ERR_PARAMCAR,
	ERR_GRANDNUM,
	ERR_NUMINVALIDE,

	ER_PARAMSYM
};

#endif
