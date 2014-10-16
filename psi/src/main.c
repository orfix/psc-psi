/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009 
 * ---------------------------------------------------------------------
 * Projet 		: PSI (Pascal Subset Interpreter)
 * Module 		: ...
 * Fonction 	: Interpreteur pour un sous-ensemble de PASCAL `PSI'
 * Fichier 		: main.c
 * --------------------------------------------------------------------- */
#include  "err.h"
#include  "al.h"
#include  "as.h"
#include  "psi.h"
#include  <stdio.h>
#include  <stdlib.h>

#define  FILENAME 	"count.out"
#define  ISSET(opt, f) 	( ((opt) & (f))!=0 )

enum opt
{
	OPT_AUCUNE	= 0x00,
	OPT_HELP	= 0x01,
	OPT_SCAN	= 0x02,
	OPT_LIST	= 0x08
};

char compiler(Psi *prog);
void afficherTS(Psi *prog);
void afficherSym(Psi *prog);
void genererCode(Psi *prog, const char *fout) ;
void listerCode(Psi *prog);


int main(int argc, const char *argv[])
{
	int i = 1;
	enum opt options = OPT_AUCUNE;

	/* Lire les options */
	while( i<argc && argv[i][0]=='-') {
		switch ( argv[i++][1] ) {
			case 'h' : options |= OPT_HELP;		break;
			case 's' : options |= OPT_SCAN; 	break;
			case 'l' : options |= OPT_LIST; 	break;
			default  : options |= OPT_HELP; 	break;
		}
	}
	if( ISSET(options, OPT_HELP) || i>=argc) {
		psi_printUsage(argv[0]);
	} else { /* Lire les fichiers */
		Psi *prog = NULL;

		while( i<argc ) {
			if( (prog=psi_init(argv[i]))!=NULL ) { 
				if( ISSET(options, OPT_SCAN) ) { 
					afficherSym(prog);
				} else {
					as_program(prog);
					if( ISSET(options, OPT_LIST) ) {
						listerCode(prog);
					}
					err_afficher(prog);
					/* TODO: Ajout d'une OPTION debug, step by step */
					if(prog->erreur==ERR_AUCUNE) {
						psi_exec(prog);
						/* Time ellapsed 00:00, press any key to continue...  */
					}
					/*
					   char out[TAILLEF];

					   if( ISSET(options, OPT_LIST) ) {
					   listerCode(prog);
					   }
					   if( compiler(prog) ) {
					   sprintf(out, "%s.out", GETPROGID(prog));
					   genererCode(prog, out);
					   }
					 */
				}
				psi_quit(prog);
			} else { 
				fprintf(stderr, "Impossible d'ouvrir le fichier `%s'\n",argv[i]);
				/* ou l'allocation a echouee !! */
			}
			i++;
		}
	}

	return 0;
}

void afficherSym(Psi *prog) 
{
	printf("SYMBOLES RENCONTRES-------------- [%s]\n", prog->fichier);
	while(prog->sym.cl!=CL_FIN && prog->sym.cl!=CL_ERREUR) {
		al_dbg_sym(prog);
		al_symSuivant(prog);
	}
	err_afficher(prog);
}

void listerCode(Psi *prog) 
{
	int i;

	printf("CODE GENERE---------------------- [%s]\n", prog->fichier);
	printf("NUM INST : %d\n",prog->code.pc);
	for( i=0 ; i<prog->code.pc ; i++ ) {
		inst_debug(&prog->code, i);
	}
}

#if 0
char compiler(Psi *prog) 
{
	as_program(prog);
	err_afficher(prog);
	return prog->erreur==0; 
}

void genererCode(Psi *prog, const char *fout) 
{
	/* !!!! P-CODE !!!! */
	FILE *out = fopen(fout, "w");

	if( out!=NULL ) {
		inst_save(&prog->code, out);
		fclose(out);
	} else {
		fprintf(stderr, "Impossible de creer le fichier `%s'\n",fout);
	}
}

void afficherTS(Psi *prog) 
{
	printf("TABLE DES SYMBOLES--------------- [%s]\n", prog->fichier);
	while(prog->sym.cl!=CL_FIN && prog->sym.cl!=CL_ERREUR) {
		al_symSuivant(prog);
	}
	ts_debug(&(prog->ts));
}


#endif
