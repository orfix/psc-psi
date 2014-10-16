/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009
 * ---------------------------------------------------------------------
 * Projet 		: PSC (Pascal Subset Compiler)
 * Module 		: TS
 * Fonction 	: Table des Symboles
 * Fichier 		: ts.c
 * --------------------------------------------------------------------- */
#include  "ts.h"
#include  <string.h>
#include  <stdio.h>
#include  <stdlib.h>

extern const char *dbg_cl[];

void ts_init(TabSym *ts) 
{
	ts->i = 0;
}

int ts_supprimervlF(TabSym *ts, unsigned int n)
{	/* Vider la TS des variables locales */
	if( n<= ts->i ) {
		ts->i -= n;
		return 1;
	}
	return 0; /* n > taille de la TS */
}

int	ts_ajouter(TabSym *ts, const enum classe cls,const char *ch,unsigned int adr)
{
	if( ts->i<TAILLETS ) {
		ts->tab[ts->i].cls = cls;
		ts->tab[ts->i].adr = adr; /* TODO: tester si ID_PROG */
		strcpy(ts->tab[ts->i].ch, ch);

		return ts->i++;
	}
	return TAILLETS; /* Table pleine */
}

unsigned int ts_chercher(TabSym *ts, const char *ch)
{
	int i; /* TODO: doit être unsigned ! */

	for( i=ts->i -1 ; i>=0 ; i-- ) {
		if( strcmp(ts->tab[i].ch, ch)==0 ) {
			return i; /* indice */
		}
	}
	return TAILLETS; /* Aucune occurrence trouvée */
}

void ts_debug(TabSym *ts)
{
	unsigned int i;
	const char *type[] = {"id programme", "constante", "variable", "procedure"};

	for( i=0 ; i<ts->i ; i++ ) {
		char val[64] = "-";

		if( ts->tab[i].cls!=CLS_PROG ) {
			sprintf(val, "%d", ts->tab[i].adr);
		}
		printf("%-10s\t%s\t%s\n", ts->tab[i].ch, type[ts->tab[i].cls], val);
	}
}

