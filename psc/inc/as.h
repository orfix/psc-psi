/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009
 * ---------------------------------------------------------------------
 * Projet 		: PSC (Pascal Subset Compiler)
 * Module 		: AS
 * Fonction 	: Analyseur Syntaxique LL(1)
 * Fichier 		: as.h
 * --------------------------------------------------------------------- */
#ifndef  H_AS_MO
#define  H_AS_MO

#include  "psc.h"

/* PROGRAM	::=	program ID ; BLOCK . 
 * PREMIER      program 
 * SUIVANT      
 * ----------------------------------------------------------------*/
void as_program(Psc *prog);

/* BLOCK	::= CONSTS VARS PROCS VARS INSTS */
/* BLOCK	::=	CONSTS VARS PROCS INSTS 
 * PREMIER 		const, var, begin
 * SUIVANT       
 * ----------------------------------------------------------------*/
void as_block(Psc *prog);

/* CONSTS	::=	const ID = NUM ; { ID = NUM ; } | epsilon 
 * PREMIER 		const 
 * SUIVANT      var, begin 
 * ----------------------------------------------------------------*/
void as_consts(Psc *prog);

/* VARS		::=	var ID { , ID } ; | epsilon
 * PREMIER 		var
 * SUIVANT      begin 
 * ----------------------------------------------------------------*/
void as_vars(Psc *prog);

/* INSTS	::=	begin INST { ; INST } end 
 * PREMIER 		begin
 * SUIVANT       
 * ----------------------------------------------------------------*/
void as_insts(Psc *prog);

/* INST		::=	APPEL | INSTS | AFFEC | SI | TANTQUE | ECRIRE | LIRE | epsilon 
 * PREMIER 		ID, begin, ID, if, while, write, read
 * SUIVANT      ;, end, .
 * ----------------------------------------------------------------*/
void as_inst(Psc *prog);

/* AFFEC	::=	ID := EXPR 
 * PREMIER 		ID
 * SUIVANT       
 * ----------------------------------------------------------------*/
void as_affec(Psc *prog);

/* SI		::=	if COND then INST 
 * PREMIER		if
 * SUIVANT       
 * ----------------------------------------------------------------*/
void as_si(Psc *prog);

/* TANTQUE	::=	while COND do INST 
 * PREMIER		while
 * SUIVANT       
 * ----------------------------------------------------------------*/
void as_tantque(Psc *prog);

/* ECRIRE	::=	write ( EXPR { , EXPR } ) 
 * PREMIER		write
 * SUIVANT       
 * ----------------------------------------------------------------*/
void as_ecrire(Psc *prog);

/* LIRE		::=	read ( ID { , ID } ) 
 * PREMIER		read
 * SUIVANT       
 * ----------------------------------------------------------------*/
void as_lire(Psc *prog);

/* COND		::=	EXPR RELOP EXPR 
 * PREMIER		ID, NUM, (
 * SUIVANT       
 * ----------------------------------------------------------------*/
void as_cond(Psc *prog);

/* RELOP	::=	= | <> | < | > | <= | >= 
 * PREMIER		=, <>, <, >, <=, >=
 * SUIVANT       
 * ----------------------------------------------------------------*/
void as_relop(Psc *prog);

/* EXPR		::=	TERM { ADDOP TERM } 
 * PREMIER		ID, NUM, (
 * SUIVANT       
 * ----------------------------------------------------------------*/
void as_expr(Psc *prog);

/* ADDOP	::=	+ | - 
 * PREMIER		+, -
 * SUIVANT       
 * ----------------------------------------------------------------*/
void as_addop(Psc *prog);

/* TERM		::=	FACT { MULOP FACT } 
 * PREMIER		ID, NUM, (
 * SUIVANT       
 * ----------------------------------------------------------------*/
void as_term(Psc *prog);

/* MULOP	::=	* | / 
 * PREMIER		*, /
 * SUIVANT       
 * ----------------------------------------------------------------*/
void as_mulop(Psc *prog);

/* FACT		::=	ID | NUM | ( EXPR ) 
 * PREMIER		ID, NUM, (
 * SUIVANT       
 * ----------------------------------------------------------------*/
void as_fact(Psc *prog);

/* PROCS 	::= {procedure ID "(" [var] ID {, [var] ID} ")" ";" INSTS ";"}*/
/* PROCS 	::= {procedure ID "(" ")" ";" CONSTS VARS INSTS ";"}
 * PREMIER		procedure	
 * SUIVANT       
 * ----------------------------------------------------------------*/
void as_procs(Psc *prog);

/* APPEL	::= ID "(" {"," ID} ")"
 * PREMIER		ID
 * SUIVANT       
 * ----------------------------------------------------------------*/
void as_appel(Psc *prog);

#endif
