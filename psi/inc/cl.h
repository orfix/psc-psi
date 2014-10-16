/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009 
 * ---------------------------------------------------------------------
 * Projet 		: PSI (Pascal Subset Interpreter)
 * Module 		: CL
 * Fonction 	: Classes Lexicales
 * Fichier 		: cl.h
 * --------------------------------------------------------------------- */
#ifndef  H_CL_MO
#define  H_CL_MO

/* TODO: Ajout d'un delimiteur pour simplifier cette macro */
#define  WITHOP(cl)		(cl==CL_INT || cl==CL_LDI || cl==CL_LDA || \
						 cl==CL_LDL || cl==CL_BRN || cl==CL_BZE || cl==CL_CAL)

/* ATTENTION: l'ordre de declaration est important */
enum classLex {
	CL_ADD,
	CL_BRN,
	CL_BZE,
	CL_CAL,
	CL_DIV,
	CL_EQL,
	CL_GEQ,
	CL_GTR,
	CL_HLT,
	CL_INN,
	CL_INT,
	CL_LDA,
	CL_LDI,
	CL_LDL,
	CL_LDV,
	CL_LEQ,
	CL_LSS,
	CL_MUL,
	CL_NEQ,
	CL_PRN,
	CL_RET,
	CL_STO,
	CL_SUB,
	CL_INST,

	CL_NUM,

	CL_FIN, 	/* 	<EOF> 		*/
	CL_ERREUR	/* 	<erreur>	*/
};

#endif
