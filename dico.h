#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Définitions des constantes et de macros
#define nil NULL
typedef char * string;
#define cdr(x) (x->cdr)
#define mot(x) (x->mot)
#define cat(x) (x->cat)
#define francais(x) (x->francais)
#define traductions(x) (x->traduc)
#define traduction(x) (x->traduction)

// Déclaration de structures
typedef struct Liste_mots_cat {string mot; string cat;} base;
typedef struct Traductions {base * traduction; struct Traductions * cdr;}* traductions;
typedef struct Entree {base *francais; traductions traduc; struct Entree * cdr;} * entree;

entree dico = nil;

// Prototypes :
traductions cons_traduction(base *, traductions);
entree cons_entree (base *, traductions, entree);
void lire_fichier(string);
void assigner_dico(FILE*, string);
void usage(const string, string);
void saisir_mot(entree);
void affiche_mot_fr(entree, string);
void affiche_traduction(traductions);
void mots_fr_vers_fichier(entree);
void imprimer_mots_fr(entree, FILE *);
void retro_construction(entree);
void retro_ligne(entree, FILE *);
void retro_mot_traduction(traductions, entree, FILE*);
int oui_non();
