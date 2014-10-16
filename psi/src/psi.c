/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009 
 * ---------------------------------------------------------------------
 * Projet 		: PSI (Pascal Subset Interpreter)
 * Module 		: PSI
 * Fonction 	: Interpréter le code
 * Fichier 		: psi.c
 * --------------------------------------------------------------------- */
#include  "err.h"
#include  "pile.h"
#include  "al.h"
#include  "psi.h"
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>

#define  ISMNEM(prog, cl) 	((prog)->code.insts[(prog)->code.pc].m == cl)

Psi* psi_init(const char *nomFichier) 
{
	Psi *prog = malloc( sizeof *prog);

	if( prog!=NULL && nomFichier!=NULL ) {
		prog->fichier[0] = '\0';
		strncat(prog->fichier, nomFichier, TAILLEF);
		if( (prog->desc = fopen(prog->fichier, "r"))!=NULL) {
			err_signaler(prog, ERR_AUCUNE);
			inst_init(&prog->code);
			//pile_init(&prog->pile);
			prog->ligne = 1;
			al_lireCar(prog);
			//ts_init(&prog->ts);
			al_symSuivant(prog);
		} else {
			free(prog);
			prog = NULL;
		}
		/*inst_init(&prog->code);
		  if(!inst_charger(&prog->code, nomFichier)) {
		  free(prog);
		  prog = NULL;
		  }
		 */
	}
	return prog;
}

static void psi_nextInst(Psi *prog)
{
	prog->code.pc++;
}
static void psi_execInst(Psi *prog)
{
	int tmp;
	enum classLex m = prog->code.insts[prog->code.pc].m;
	int op = prog->code.insts[prog->code.pc].op;

	switch ( m ) {
		/* TODO: Gestion des erreurs d'execution (division par 0 etc...) */
		case CL_ADD : tmp = pile_pop(&prog->pile);
					  pile_push(&prog->pile,pile_pop(&prog->pile) + tmp); break;
		case CL_MUL : tmp = pile_pop(&prog->pile);
					  pile_push(&prog->pile,pile_pop(&prog->pile) * tmp); break;
		case CL_SUB : tmp = pile_pop(&prog->pile);
					  pile_push(&prog->pile,pile_pop(&prog->pile) - tmp); break;
		case CL_DIV : tmp =pile_pop(&prog->pile);
					  pile_push(&prog->pile,pile_pop(&prog->pile) / tmp); break;
		case CL_EQL : tmp =pile_pop(&prog->pile);
					  pile_push(&prog->pile,pile_pop(&prog->pile) == tmp); break;
		case CL_NEQ : tmp =pile_pop(&prog->pile);
					  pile_push(&prog->pile,pile_pop(&prog->pile) != tmp); break;
		case CL_GTR : tmp =pile_pop(&prog->pile);
					  pile_push(&prog->pile,pile_pop(&prog->pile) > tmp); break;
		case CL_LSS : tmp =pile_pop(&prog->pile);
					  pile_push(&prog->pile,pile_pop(&prog->pile) < tmp); break;
		case CL_GEQ : tmp =pile_pop(&prog->pile);
					  pile_push(&prog->pile,pile_pop(&prog->pile) >= tmp); break;
		case CL_LEQ : tmp =pile_pop(&prog->pile);
					  pile_push(&prog->pile,pile_pop(&prog->pile) <= tmp); break;
		case CL_PRN : printf("%d\n",pile_pop(&prog->pile)); break;
		case CL_INN : /* TODO: remplacer scanf par fgets+strtol */
					  scanf("%d",&(prog->pile.tab[pile_pop(&prog->pile)])); break;
		case CL_INT : prog->pile.sp += op; break;
		case CL_LDI : pile_push(&prog->pile, op); break;
		case CL_LDA : pile_push(&prog->pile, op); break;
		case CL_LDL : pile_push(&prog->pile, op + prog->code.bp); break;
		case CL_LDV : pile_push(&prog->pile, prog->pile.tab[pile_pop(&prog->pile)] );
					  break;
		case CL_STO : tmp = pile_pop(&prog->pile);
					  prog->pile.tab[pile_pop(&prog->pile)] = tmp;
					  break;
		case CL_BRN : prog->code.pc = op -1; break; /* FIXIT: -1 annule psi_nextInst */ 
		case CL_BZE : if(pile_pop(&prog->pile)==0) {
						  prog->code.pc = op -1; /* FIXIT: -1 annule psi_nextInst */
					  }
					  break;
		case CL_CAL : pile_push(&prog->pile, prog->code.pc +1);
					  prog->code.pc = op -1; /* FIXIT: -1 annule psi_nextInst */ 
					  pile_push(&prog->pile, prog->code.bp);
					  prog->code.bp = prog->pile.sp; break; /* FIXIT: -1 annule psi_nextInst */ 
		case CL_RET : prog->pile.sp = prog->code.bp;
					  tmp = pile_pop(&prog->pile);
					  prog->code.bp = tmp;
					  tmp = pile_pop(&prog->pile);
					  prog->code.pc = tmp -1; break; /* FIXIT: -1 annule psi_nextInst */ 
		default : /* Erreur geree par l'AS */ break;
	}
}

char psi_exec(Psi *prog) 
{
	inst_init(&prog->code);
	pile_init(&prog->pile);
	/* TODO: en absence de HLT boucle infinis !! */
	while( !ISMNEM(prog, CL_HLT) && prog->code.pc<TAILLECODE ) {
		/*inst_debug(&prog->code, prog->code.pc);*/
		psi_execInst(prog);	
		/*
		getchar();
		puts("--------------------------");
		pile_debug(&prog->pile);
		puts("--------------------------");
		*/
		psi_nextInst(prog);
	}

	return 0;
}

void psi_quit(Psi *prog) 
{
	if( prog!=NULL ) {
		if( prog->desc!=NULL ) {
			fclose(prog->desc);
		}
		free(prog);
	}
}
void psi_printUsage(const char *nomProg) 
{
	printf("USAGE : %s [OPTION]... [FICHIER]...\n",nomProg);
	puts  ("");
	puts  ("   -h : Afficher cette aide");
	puts  ("   -s : Stoper l'interpretation en phase d'analyse lexicale");
	puts  ("   -l : Lister le pseudo-code lu");
	//puts  ("   -o : Fichier de sortie pour le P-Code");
	puts  ("");
	puts  ("Pascal Subset Interpreter PSI version " PSI_VER " - (C) MO 2009");
}

