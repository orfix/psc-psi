# Pascal Subset Compiler & Pascal Subset Interpreter (PSC/PSI)

## Description
A cross-platform LL(1) compiler and a stack machine interpreter, written in C, for a Pascal language subset.

##PSC
### Context-free grammar in EBNF notation
```
PROGRAM  ::= program ID ; BLOCK .
BLOCK    ::= CONSTS VARS PROCS VARS INSTS
CONSTS   ::= const ID = NUM ; { ID = NUM ; } | ε
VARS     ::= var ID { , ID } ; | ε
INSTS    ::= begin INST { ; INST } end
INST     ::= APPEL | INSTS | AFFEC | SI | TANTQUE | ECRIRE | LIRE | ε
AFFEC    ::= ID := EXPR
SI       ::= if COND then INST
TANTQUE  ::= while COND do INST
ECRIRE   ::= write ( EXPR { , EXPR } )
LIRE     ::= read ( ID { , ID } )
COND     ::= EXPR RELOP EXPR
RELOP    ::= = | <> | < | > | <= | >=
EXPR     ::= TERM { ADDOP TERM }
ADDOP    ::= + | -
TERM     ::= FACT { MULOP FACT }
MULOP    ::= * | /
FACT     ::= ID | NUM | ( EXPR )
PROCS    ::= {procedure ID "(" [var] ID {, [var] ID} ")" ";" INSTS ";"}
APPEL    ::= ID "(" {"," ID} ")"
```
### Recursive Factorial Example
This program takes a small positive or zero integer value and computes the factorial for that number recursively and displays the result.
#### Source code
```
(* Exemple 2: Calcule récursif de la factorielle
 * Note         : Pour quitter le programme taper 0
 *)
program factorielle2;
const   
        max = 13;
var
        res, n;

procedure fact();
var
        i, s;
begin   
        (* Calculer récursif de la factorielle *)
        if n>1 then
        begin   
                res := res * n;
                n := n - 1;
                fact();
        end;
end;

begin   
        n       := 1;
        (* Taper 0 pour quitter *)
        while n<>0 do
        begin   
                (* Entrer un nombre inferieur a max *)
                read(n);
                while n > max do
                        read(n);

                res := 1;
                fact();
                write(res);
        end;
end.
```
#### Generated Assembly Code
```
INT 3
LDL 0
LDI 13
STO
BRN 26
INT 2
LDA 2
LDV
LDI 1
GTR
BZE 25
LDA 1
LDA 1
LDV
LDA 2
LDV
MUL
STO
LDA 2
LDA 2
LDV
LDI 1
SUB
STO
CAL 5
RET
LDA 2
LDI 1
STO
LDA 2
LDV
LDI 0
NEQ
BZE 53
LDA 2
INN
LDA 2
LDV
LDA 0
LDV
GTR
BZE 45
LDA 2
INN
BRN 36
LDA 1
LDI 1
STO
CAL 5
LDA 1
LDV
PRN
BRN 29
HLT
; Fichier genere par PSC version 0.1 - (C) MO 2009
```
### Usage
```
USAGE : ./psc [OPTION]... [FICHIER]...

    -h : Afficher cette aide
    -t : Lister le contenu de la table des symboles
    -s : Stoper la compilation en phase d'analyse lexicale
    -l : Lister le pseudo-code genere

    *Pascal Subset Compiler PSC version 0.1 - (C) MO 2009*
```

## PSI
### Assembler Mnemonics List
```
ADD		additionne le sous-sommet de pile et le sommet, laisse le résultat au
		sommet (idem pour SUB, MUL, DIV)
EQL		laisse 1 au sommet de pile si sous-sommet = sommet, 0 sinon (idem pour
		NEQ, GTR, LSS, GEQ, LEQ)
PRN 	imprime le sommet, dépile INN lit un entier, le stocke à l'adresse
		trouvée au sommet de pile, dépile
INT c 	incrémente de la constante c le pointeur de pile (la constante c peut
		être négative)
LDI v 	empile la valeur v
LDA a 	empile l'adresse a
LDV 	remplace le sommet par la valeur trouvée à l'adresse indiquée par le
		sommet (déréférence)
STO 	stocke la valeur au sommet à l'adresse indiquée par le sous-sommet,
		dépile 2 fois
BRN i 	branchement inconditionnel à l'instruction i
BZE i 	branchement à l'instruction i si le sommet = 0, dépile
HLT 	halte

```
### Recursive Factorial Example: Sample Run
```
$ ./psi factorielle2.out 
exemples/factorielle2.out: ligne 56: Aucune erreur
12
479001600
4
24
9
362880
1
1
3
6
0
1
```
### Usage
```
USAGE : ./psi [OPTION]... [FICHIER]...

     -h : Afficher cette aide
     -s : Stoper l'interpretation en phase d'analyse lexicale
     -l : Lister le pseudo-code lu

    *Pascal Subset Interpreter PSI version 0.1 - (C) MO 2009*
```
