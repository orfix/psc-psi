/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009 
 * ---------------------------------------------------------------------
 * Projet 		: PSI (Pascal Subset Interpreter)
 * Module 		: PILE
 * Fonction 	: Gestionnaire de pile
 * Fichier 		: pile.h
 * --------------------------------------------------------------------- */
#ifndef  H_PILE_MO
#define  H_PILE_MO

#define  TAILLEPILE 	1024

#define  PILE_PLEINE(pile) 	((pile)->sp>=TAILLEPILE)
#define  PILE_VIDE(pile) 	((pile)->sp==0)

typedef struct pile
{
	int tab[TAILLEPILE];
	unsigned int sp;
}Pile;

/* TODO: Gestion des erreures volantairement omise pour des raisons
 * de simplicité !! */

void pile_init(Pile *pile);
void pile_push(Pile *pile, int val);
int pile_pop(Pile *pile);
void pile_debug(Pile *pile);

#endif
