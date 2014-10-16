/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009
 * ---------------------------------------------------------------------
 * Projet 		: PSC (Pascal Subset Compiler)
 * Module 		: AL
 * Fonction 	: Analyseur Lexicale
 * Fichier 		: al.c
 * --------------------------------------------------------------------- */
#include  "err.h"
#include  "ts.h"
#include  "al.h"
#include  <limits.h> /* INT_MAX */
#include  <ctype.h>
#include  <string.h>
#include  <stdio.h>
#include  <stdlib.h>

static void al_sauterBlanc(Psc *prog) 
{
	while(isspace(prog->car)) {
		if( prog->car=='\n' ) prog->ligne++;
		al_lireCar(prog);
	}
}

static int al_sauterCom(Psc *prog) 
{
	do{
		do {
			if( prog->car=='\n' ) prog->ligne++;
			al_lireCar(prog);
		}while( prog->car!='*' && prog->car!=EOF );
		if( prog->car=='*' ) {
			al_lireCar(prog);
		}
	}while(prog->car!=')' && prog->car!=EOF);	
	if( prog->car==')' ) {
		al_lireCar(prog);
		return 1;
	}
	/* marque "*)" introuvable */
	err_signaler(prog, ERR_COMM);
	return 0; 
}

static void codage_lex(Psc *prog) 
{
	static const char *motscles[] = { "begin", "end", "if", "while", "then",
		"do", "write", "read", "const", "var", "program", "procedure" };
	enum classLex cl = 0;
	static enum classe cls = CLS_PROG;

	/* Tester si c'est un mot cle */
	while(cl<NELEM(motscles) && strcmp(prog->sym.ch, motscles[cl])!=0) cl++;
	/* Determiner le contexte */
	switch ( cl ) {
		case CL_PROGRAM 	: cls = CLS_PROG;	break;
		case CL_CONST 		: cls = CLS_CONST;	break;
		case CL_VAR 		: cls = CLS_VAR;	break;
		case CL_BEGIN 		: cls = CLS_CODE;	break;
		case CL_PROCEDURE	: cls = CLS_PROC;	break;
		default				: break;
	}

	if( cl<NELEM(motscles) ) prog->sym.cl = cl; /* mot cle */
	else {
		prog->sym.cl = CL_ID;
		cl = ts_chercherSym(prog);	
		if( cl!=TAILLETS ) { /* identifiant declare */
			prog->sym.its = cl;
			if( cls!=CLS_CODE ) { /* identifiant redeclaree */
				if(!ISIDLOCAL(prog)) { /* peut être masqué */
				   if((prog->sym.its=ts_ajouterSym(prog, cls))==TAILLETS) {
					   err_signaler(prog, ERR_TSPLEAINE);
				   }
				   prog->offset ++;
				} else {
					err_signaler(prog, ERR_IDREDCL);	
				}
			}
		} else { /* identifiant non declare */
			if( cls==CLS_CODE ) { /* usage d'un identifiant non declarer */
				err_signaler(prog, ERR_IDNONDCL);
			} else {
				if( (prog->sym.its=ts_ajouterSym(prog, cls))==TAILLETS) {
					err_signaler(prog, ERR_TSPLEAINE);
				} else if( cls!=CLS_PROG && cls!=CLS_PROC ) {
					prog->offset ++;
				}
			}	
		}
	}
}

static void al_lireNum(Psc *prog)
{
	unsigned int i = 0;

	prog->sym.val = 0;
	do {
		prog->sym.val = prog->sym.val * 10 + prog->car - '0';
		prog->sym.ch[i++] = prog->car;
		al_lireCar(prog);
	}while( isdigit(prog->car) && prog->car!=EOF && prog->sym.val<INT_MAX);

	if( isalpha(prog->car) ) { /* Identifiant commencant par des chiffres */
		err_signaler(prog, ERR_IDINVALID);
	} else if(prog->sym.val>INT_MAX) { /* Numéro trop Grand */
		err_signaler(prog, ERR_GRANDNUM);
	} else {
		prog->sym.cl = CL_NUM;
	}
}

static void al_lireMot(Psc *prog) 
{
	unsigned int i = 0;

	do {
		prog->sym.ch[i++] = prog->car;
		al_lireCar(prog);
	}while( isalnum(prog->car) && prog->car!=EOF && i<TAILLESYM-1);

	if(isalnum(prog->car)) { /* Identifiant trop long */
		err_signaler(prog, ERR_LONGID);
	} else {
		codage_lex(prog);
	}
}

void al_symSuivant(Psc *prog) 
{
	memset(prog->sym.ch, '\0', TAILLESYM);
	/* Sauter les caractères blancs et les commentaires */
	al_sauterBlanc(prog);
	/* Récupération du symbole */   
	if( isalpha(prog->car) ) {
		al_lireMot(prog);
	} else if( isdigit(prog->car)) {
		al_lireNum(prog);
	} else {
		prog->sym.ch[0] = prog->car;
		switch ( prog->car ) {
			case '+' : prog->sym.cl = CL_PLUS; 		al_lireCar(prog); break;
			case '-' : prog->sym.cl = CL_MOINS; 	al_lireCar(prog); break;
			case '*' : prog->sym.cl = CL_MUL; 		al_lireCar(prog); break;
			case '/' : prog->sym.cl = CL_DIV; 		al_lireCar(prog); break;
			case ')' : prog->sym.cl = CL_PAR_FER; 	al_lireCar(prog); break;
			case ',' : prog->sym.cl = CL_VIRG; 		al_lireCar(prog); break;
			case ';' : prog->sym.cl = CL_PT_VIRG;	al_lireCar(prog); break;
			case '.' : prog->sym.cl = CL_POINT; 	al_lireCar(prog); break;
			case '=' : prog->sym.cl = CL_EGAL; 		al_lireCar(prog); break;

			case '(' : prog->sym.cl = CL_PAR_OUV;
					   al_lireCar(prog);
					   if( prog->car=='*' ) {
						   if(!al_sauterCom(prog))
							   return; /* sortie en erreur */
						   al_symSuivant(prog);
					   }
					   break;
			case ':' : al_lireCar(prog); 
					   if(prog->car=='=') {
						   prog->sym.ch[1] = prog->car;
						   prog->sym.cl = CL_AFFEC;
						   al_lireCar(prog);
					   } else {
						   err_signaler(prog, ERR_EGAL);
					   }
					   break;
			case '>' : al_lireCar(prog); 
					   if(prog->car=='=') {
						   prog->sym.ch[1] = prog->car;
						   prog->sym.cl = CL_SUP_EGAL;
						   al_lireCar(prog);
					   } else {
						   prog->sym.cl = CL_SUP;
					   }
					   break;
			case '<' : al_lireCar(prog); 
					   if(prog->car=='>') {
						   prog->sym.ch[1] = prog->car;
						   prog->sym.cl = CL_DIFF;
						   al_lireCar(prog);
					   } else if(prog->car=='=') {
						   prog->sym.ch[1] = prog->car;
						   prog->sym.cl = CL_INF_EGAL;
						   al_lireCar(prog);
					   } else {
						   prog->sym.cl = CL_INF;
					   }
					   break;
			case EOF : /*ts_debug(&ts);*/ prog->sym.cl = CL_FIN; break;
			default : err_signaler(prog, ERR_CARINC); break;
		}
	}
}

void al_dbg_sym(Psc *prog) 
{
	static const char *dbg_cl[] = {
		"mot cle BEGIN", "mot cle END", "mot cle IF", "mot cle WHILE", 
		"mot cle THEN", "mot cle DO", "mot cle WRITE", "mot cle READ", 
		"mot cle CONST", "mot cle VAR", "mot cle PROGRAM", "mot cle PROCEDURE",

		"Identifiant", "Numero", "signe +", "signe -", "signe *", "signe /",
		"signe <", "signe >", "signe )", "signe ,", "signe ;", "signe .",
		"signe (", "signe =", "signe <>", "signe <=", "signe >=", "signe :=", 
		"Fin de fichier",
		"erreur"
	};
	char val[64] = "-";

	if( prog->sym.cl==CL_NUM ) {
		sprintf(val, "%d", prog->sym.val);
	}
	printf("%-10s\t%-15s \t%s\n",prog->sym.ch, dbg_cl[prog->sym.cl], val);
}

