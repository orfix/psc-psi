/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009 
 * ---------------------------------------------------------------------
 * Projet 		: PSI (Pascal Subset Interpreter)
 * Module 		: PILE
 * Fonction 	: Gestionnaire de pile
 * Fichier 		: pile.c
 * --------------------------------------------------------------------- */
#include  "pile.h"
#include  <stdio.h>
#include  <stdlib.h>

void pile_init(Pile *pile)
{
	pile->sp = 0;
}

void pile_push(Pile *pile, int val)
{
	if( !PILE_PLEINE(pile) ) {
		pile->tab[pile->sp++] = val;
	} else {
		puts("PILE PLEINE");
	}
}

int pile_pop(Pile *pile)
{
	if( !PILE_VIDE(pile) ) {
		return pile->tab[--pile->sp];
	}
	puts("PILE VIDE");
	return 0; /* ATTENTION */
}

void pile_debug(Pile *pile)
{
	unsigned int i;

	for( i=0 ; i<pile->sp ; i++ ) {
		printf("%d\n",pile->tab[i]);
	}
}
