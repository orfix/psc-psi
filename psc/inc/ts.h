/* ---------------------------------------------------------------------
 * (C) MO - Mounir Orfi - 2009
 * ---------------------------------------------------------------------
 * Projet 		: PSC (Pascal Subset Compiler)
 * Module 		: TS
 * Fonction 	: Table des Symboles
 * Fichier 		: ts.h
 * --------------------------------------------------------------------- */
#ifndef  H_TS_MO
#define  H_TS_MO

#include  "cl.h"

#define  TAILLESYM	32
#define  TAILLETS 	4096

#define  ts_chercherSym(prog) ts_chercher(&(prog)->ts, (prog)->sym.ch)
#define  ts_supprimervl(prog)  ts_supprimervlF(&(prog)->ts, prog->offset)
#define  ts_ajouterSym(prog, cls)  ts_ajouter(&(prog)->ts, 		\
										cls, \
										(prog)->sym.ch, \
										(prog)->offset)
//#define  ts_getclasse(prog ,i) (prog)->ts[(i)]
#define  GETPROGID(prog) 	(prog)->ts.tab[0].ch
/* CLS_CODE == CLS_NONE */
enum classe { CLS_PROG, CLS_CONST, CLS_VAR, CLS_PROC, CLS_CODE };

struct ts_elem
{
	/*enum classeLex cl;*/
	char ch[TAILLESYM];
	enum classe cls;
	unsigned int adr;
};

typedef struct tabSym
{
	struct ts_elem tab[TAILLETS];
	unsigned int i;
}TabSym;

int ts_dansUneProcedureF(TabSym *ts);
void ts_init(TabSym *ts);
int	ts_ajouter(TabSym *ts, const enum classe cl,const char *ch, unsigned int adr);
int ts_supprimervlF(TabSym *ts, unsigned int n);
unsigned int ts_chercher(TabSym *ts, const char *ch);
void ts_debug(TabSym *ts);


#endif
