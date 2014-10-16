/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009
 * ---------------------------------------------------------------------
 * Projet 		: PSC (Pascal Subset Compiler)
 * Module 		: CL
 * Fonction 	: Classes Lexicales
 * Fichier 		: cl.h
 * --------------------------------------------------------------------- */
#ifndef  H_CL_MO
#define  H_CL_MO

/* ATTENTION: l'ordre de declaration est important */
enum classLex {
	CL_BEGIN,	/* 	begin 		*/
	CL_END, 	/*  end 		*/
	CL_IF,		/* 	if 			*/
	CL_WHILE, 	/* 	while 		*/
	CL_THEN, 	/* 	then 		*/
	CL_DO, 		/*  do			*/
	CL_WRITE,	/*  write 		*/ 
	CL_READ, 	/*  read 		*/
	CL_CONST, 	/* 	const	 	*/
	CL_VAR, 	/* 	var			*/
	CL_PROGRAM, /* 	program 	*/
	CL_PROCEDURE, /* 	procedure 	*/

	CL_ID,		/* <lettre> { <lettre> | <chiffre> } */
	CL_NUM, 	/* <chiffre> { <chiffre> } */

	CL_PLUS, 	/* 	+ 		*/
	CL_MOINS,	/* 	- 		*/
	CL_MUL,		/* 	* 		*/
	CL_DIV,		/* 	/ 		*/
	CL_INF,		/* 	< 		*/
	CL_SUP,		/* 	> 		*/
	CL_PAR_FER,	/* 	) 		*/
	CL_VIRG, 	/* 	, 		*/
	CL_PT_VIRG, /* 	; 		*/
	CL_POINT,	/* 	. 		*/
	CL_PAR_OUV,	/* 	( 		*/

	CL_EGAL,	/* 	= 		*/
	CL_DIFF, 	/* 	<> 		*/
	CL_INF_EGAL,/* 	<= 		*/ 
	CL_SUP_EGAL,/* 	>= 		*/ 
	CL_AFFEC, 	/* 	:= 		*/

	CL_FIN, 	/* 	<EOF> 		*/
	CL_ERREUR	/* 	<erreur>	*/
};

#endif
