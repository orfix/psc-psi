/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009 
 * ---------------------------------------------------------------------
 * Projet 		: PSC (Pascal Subset Compiler)
 * Module 		: ...
 * Fonction 	: Compilateur pour un sous-ensemble de PASCAL `PSC'
 * Fichier 		: main.c
 * --------------------------------------------------------------------- */
#include  "inst.h"
#include  "err.h"
#include  "as.h"
#include  "ts.h"
#include  "al.h"
#include  "psc.h"
#include  <stdio.h>
#include  <stdlib.h>

#define  ISSET(opt, f) 	( ((opt) & (f))!=0 )

enum opt
{
	OPT_AUCUNE	= 0x00,
	OPT_HELP	= 0x01,
	OPT_SCAN	= 0x02,
	OPT_TS		= 0x04,
	OPT_LIST	= 0x08
	//OPT_OUTPUT	= 0x10
};

/* TODO: Allouer la memoire dynamiquement un peu partout (TAILLECODE)*/

char compiler(Psc *prog);
void afficherTS(Psc *prog);
void afficherSym(Psc *prog);
void genererCode(Psc *prog, const char *fout) ;
void listerCode(Psc *prog);

int main(int argc, const char *argv[])
{
	int i = 1;
	enum opt options = OPT_AUCUNE;

	/* Lire les options */
	while( i<argc && argv[i][0]=='-') {
		switch ( argv[i++][1] ) {
			case 'h' : options |= OPT_HELP;		break;
			case 's' : options |= OPT_SCAN; 	break;
			case 't' : options |= OPT_TS; 		break;
			case 'l' : options |= OPT_LIST; 	break;
			default  : options |= OPT_HELP; 	break;
		}
	}
	if( ISSET(options, OPT_HELP) || i>=argc) {
		psc_printUsage(argv[0]);
	} else { /* Lire les fichiers */
		Psc *prog = NULL;

		while( i<argc ) {
			if( (prog=psc_init(argv[i]))!=NULL ) { 
				if( ISSET(options, OPT_SCAN) ) { 
					afficherSym(prog);
				} else {
					char out[TAILLEF];

					if( compiler(prog) ) {
						if( ISSET(options, OPT_TS) ) {
							afficherTS(prog);
						}
						if( ISSET(options, OPT_LIST) ) {
							listerCode(prog);
						}
						sprintf(out, "%s.out", GETPROGID(prog));
						genererCode(prog, out);
					}
				}
				psc_quit(prog);
			} else { 
				fprintf(stderr, "Impossible d'ouvrir le fichier `%s'\n",argv[i]);
				/* ou l'allocation a echouee !! */
			}
			i++;
		}
	}
	return 0;
}

char compiler(Psc *prog) 
{
	as_program(prog);
	err_afficher(prog);
	return prog->erreur==0; 
}

void genererCode(Psc *prog, const char *fout) 
{
	FILE *out = fopen(fout, "w");

	if( out!=NULL ) {
		inst_save(&prog->code, out);
		fclose(out);
	} else {
		fprintf(stderr, "Impossible de creer le fichier `%s'\n",fout);
	}
}

void afficherTS(Psc *prog) 
{
	printf("TABLE DES SYMBOLES--------------- [%s]\n", prog->fichier);
	ts_debug(&(prog->ts));
}

void afficherSym(Psc *prog) 
{
	printf("SYMBOLES RENCONTRES-------------- [%s]\n", prog->fichier);
	while(prog->sym.cl!=CL_FIN && prog->sym.cl!=CL_ERREUR) {
		al_dbg_sym(prog);
		al_symSuivant(prog);
	}
	err_afficher(prog);
}

void listerCode(Psc *prog) 
{
	printf("CODE GENERE---------------------- [%s]\n", prog->fichier);
	inst_debug(&prog->code);
}

