/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009
 * ---------------------------------------------------------------------
 * Projet 		: PSC (Pascal Subset Compiler)
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
	ERR_EGAL,

	ERR_PROGRAM,
	ERR_BEGIN,
	ERR_IF,
	ERR_THEN,
	ERR_WHILE,
	ERR_DO,
	ERR_WRITE,
	ERR_READ,
	ERR_END,

	ERR_ID,
	ERR_PT_VIRG,
	ERR_POINT,
	ERR_NUM,
	ERR_AFFEC,
	ERR_PAR_OUV,
	ERR_PAR_FER,

	ERR_PROCS_ATT,
	ERR_INST_ATT,
	ERR_CONSTS_ATT,
	ERR_VARS_ATT,
	ERR_RELOP_ATT,
	ERR_ADDOP_ATT,
	ERR_MULOP_ATT,
	ERR_FACT_ATT,

	ERR_TSPLEAINE,
	ERR_PARAMAUCUN,
	ERR_CARINC,
	ERR_PARAMCAR,
	ERR_IDINVALID,
	ERR_GRANDNUM,
	ERR_LONGID,
	ERR_IDREDCL,
	ERR_IDNONDCL,

	ERR_IDNVAR,
	ERR_IDNVARNCONST,
	ERR_IDNPROC,
	ER_PARAMSYM
};

#endif
