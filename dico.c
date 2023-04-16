#include "dico.h"

//Programme principal :
int main (int argc, string argv[]){
  if (argc != 2)
    usage(argv[1], "Usage : <nom_du_programme><nom_du_fichier>");

  #ifdef TEST
    lire_fichier(argv[1]);
    puts("Test1 : Imprimer les mots français dans un fichier");
    mots_fr_vers_fichier(dico);
    puts("\nTest2 : Retro-construction du fichier initial");
    retro_construction(dico);
  #else
    lire_fichier(argv[1]);
    while(1){
    saisir_mot(dico);
    if (!oui_non())
      exit(0);
    }
  #endif
 return 0;
}

traductions cons_traduction(base *mot_base, traductions liste_traduction){
  // assigne une traduction dans la structure Traductions
  traductions new = malloc(sizeof(struct Traductions));
  if (!new)
  usage("new","Erreur lors de l'allocation dans cons_traduction\n");
  traduction(new) = malloc(sizeof(base));
  if (!traduction(new))
  usage("traduction(new)","Erreur lors de l'allocation dans cons_traduction\n");

  mot(traduction(new)) = mot(mot_base);
  cat(traduction(new)) = cat(mot_base);
  cdr(new) = liste_traduction;

  return new;
}

entree cons_entree (base *mot_base, traductions liste_traduction, entree dico){
  // Affecte une entrée dans le dictionnaire dico
  entree entree = malloc(sizeof(struct Entree));
  if(!entree)
    usage("entree","Erreur lors de l'allocation dans cons_entree");
  francais(entree) = malloc(sizeof(base));
  if(!francais(entree))
    usage("francais(entree)", "Erreur lors de l'allocation dans cons_entree\n");

  mot(francais(entree)) = mot(mot_base);
  cat(francais(entree)) = cat(mot_base);
  traductions(entree) = liste_traduction;
  cdr(entree) = dico;

  return entree;
}

void lire_fichier(string nom_fichier){
	FILE * flux = fopen(nom_fichier, "r");
	// Ouverture du fichier texte en mode lecture
	if (!flux)
		usage(nom_fichier,"Echec lors de l'ouverture du fichier\n");
	// Gestion d'erreur
	while (!feof (flux))
	// Récupère les lignes une par une
		assigner_dico(flux, nom_fichier);
	if (fclose(flux))
    usage(nom_fichier, "Echec lors de la fermeture du fichier\n");
  // Fermeture du flux de fichier
}


void assigner_dico(FILE* flux, string nom_fichier){
 // Une fonction qui assigne dans une structure de type arbre
 // l'ensemble des mots présents dans un fichier de type dictionnaire

  traductions liste_traduction = nil;

  base *base_fr = malloc(sizeof(base));
  if(!base_fr)
    usage("base_fr", "Erreur lors de l'allocation dans traitement_ligne\n");
  base *base_esp = malloc(sizeof(base));
  if (!base_esp)
    usage("base_esp", "Erreur lors de l'allocation dans traitement_ligne\n");

  string mot_fr, mot_esp, cat_fr, cat_esp;

  mot_fr = malloc(sizeof(char) *100);
  if(!mot_fr)
    usage("mot_fr", "Erreur lors de l'allocation dans traitement_ligne\n");
  mot_esp = malloc(sizeof(char) *100);
  if(!mot_esp)
    usage("mot_esp", "Erreur lors de l'allocation dans traitement_ligne\n");
  cat_fr = malloc(sizeof(char) * 30);
  if(!cat_fr)
    usage("cat_fr", "Erreur lors de l'allocation dans traitement_ligne\n");
  cat_esp = malloc(sizeof(char) * 30);
  if(!cat_esp)
    usage("cat_esp", "Erreur lors de l'allocation dans traitement_ligne\n");

  // Récupération des différents mots et catégories présents dans le fichier :
  if(fscanf(flux, "%[^\t]%s%*s %[^\[]%[^\n]\n",
  mot_fr, cat_fr, mot_esp, cat_esp) == 4){
    mot(base_fr) = strdup(mot_fr);
    cat(base_fr) = strdup(cat_fr);
    mot(base_esp) = strdup(mot_esp);
    cat(base_esp) = strdup(cat_esp) ;
    // Assigner les mots et catégories dans le dictionnaire
    // suivant la présence de doublons ou non :

    if(dico && !strcmp(mot(base_fr), mot(francais(dico)))
    && !strcmp(cat(base_fr), cat(francais(dico)))){

      liste_traduction = cons_traduction(base_esp, cdr(traductions(dico)));
      (cdr(liste_traduction)) = traductions(dico);
      traductions(dico) = liste_traduction;
    }
    else {
      liste_traduction = nil;
      liste_traduction = cons_traduction(base_esp, liste_traduction);
      dico = cons_entree(base_fr, liste_traduction, dico);
    }
  }
  else{
  // Gestion d'erreur en cas de problème de format rencontré dans le fichier
  // intégrant les mots et catégories des deux langues
  usage(nom_fichier,
    "Erreur : le format doit être <mot_fr><tab><cat_fr>-<mot_es><cat_es><BR>");
  }

free(base_fr);
free(base_esp);
free(mot_fr);
free(mot_esp);
free(cat_esp);
free(cat_fr);
}

void usage(const string mot, string message){
  // Afficher un message d'erreur
  perror(mot);
  fprintf(stderr, message);
  exit(1);
}

// Fonctions de recherche de traduction
void saisir_mot(entree dico) {
  // Fonction qui récupère un mot saisi par l'utilisateur
  // et parcourt le dictionnaire à la recherche de la traduction
  char *mot;
  mot = malloc(sizeof(char) *100);
  if (!mot)
    usage("mot","Erreur lors de l'allocation dans cons_traduction\n");
  puts("------------------------------");
  puts("Dictionnaire Français-Espagnol");
  puts("------------------------------");
  puts("Saisir un mot à traduire :");
  if (scanf("%s", mot) == EOF)
    usage("","Une erreur s'est produite lors de la lecture de l'option\n");
  (affiche_mot_fr(dico, mot));
  free(mot);
}

void affiche_mot_fr(entree dico, char *saisie) {
  // Une fonction de recherche de la présence
  // du mot saisie dans le dictionnaire
  if(!dico) return;
  affiche_mot_fr(cdr(dico), saisie);
  if (dico &&!strcmp(mot(francais(dico)), saisie)) {
    printf("\nMot Français : %s - Catégorie : %s \n",
    mot(francais(dico)), cat(francais(dico)));
    affiche_traduction(traductions(dico));
  }
}

void affiche_traduction(traductions pointeur){
  // Une fonction d'affichage des traductions
  if (!pointeur) return;
  affiche_traduction(cdr(pointeur));
  printf("\nMot_espagnol : %s - Catégorie : %s\n",
    mot(traduction(pointeur)),
    cat(traduction(pointeur)));
}

// Test 1 : Fonctions d'impression de tous les mots anglais
// dans le fichier mots_fr.txt

void mots_fr_vers_fichier(entree dico) {
  // Cette fonction ouvre le fichier mots_fr.txt en écriture
  // et y imprime les mots français ainsi la catégorie de chaque mot
  // présents dans le dictionnaire
  FILE *sortie = fopen("mots_fr.txt", "w");
  if (!sortie)
    usage("mots_fr.txt", "Erreur lors de la création du fichier\n");
  imprimer_mots_fr(dico, sortie);
  puts("Impression des mots en français dans le fichier mot_fr.txt terminée.");
  if (fclose(sortie))
    usage("mots_fr.txt", "Echec lors de la fermeture du fichier\n");
}

void imprimer_mots_fr(entree dico, FILE * fichier){
  // Cette fonction affiche le ou les mots français présents dans une ligne
  // ainsi que sa catégorie
  if (!dico) return;
    imprimer_mots_fr(cdr(dico), fichier);
    fprintf(fichier,"%s %s\n", mot(francais(dico)), cat(francais(dico)));
}

// Test 2 : Fonctions de rétro-construction des données

void retro_construction(entree dico) {
  // Cette fonction ouvre le fichier retro_construction.txt en écrire
  // et reconstruit le dictionnaire dans son format d'origine
  FILE *sortie = fopen("retro-construction.txt", "w");
  if (!sortie)
    usage("retro-construction.txt", "Erreur lors de la création du fichier\n");
  retro_ligne(dico, sortie);
  puts("Retro-construction dans le fichier retro_construction.txt terminée.");
  if (fclose(sortie))
    usage("retro-construction.txt", "Echec lors de la fermeture du fichier\n");
}

void retro_ligne(entree dico, FILE * fichier){
  // Cette fonction permet d'écrire l'ensemble des lignes du dictionnaire
  // dans un fichier
  if (!dico) return;
      retro_ligne(cdr(dico), fichier);
  retro_mot_traduction(traductions(dico), dico, fichier);
}

void retro_mot_traduction(traductions pointeur, entree dico, FILE * fichier){
  // Cette fonction imprime une ligne dans un fichier
  if (!pointeur) return;
  retro_mot_traduction(cdr(pointeur), dico, fichier);
  fprintf(fichier, "%s\t%s - %s %s\n",
    mot(francais(dico)),
    cat(francais(dico)),
    mot(traduction(pointeur)),
    cat(traduction(pointeur)));
}

int oui_non(){
  // Cette fonction permet d'arrêter ou de continuer le programme,
  // ou d'autoriser une option
  char option;
  while(1){
    printf("\n(Continuer : O/N):\n");
    if (scanf(" %c", &option) != 1)
      usage("","Une erreur s'est produite lors de la lecture de l'option\n");
    else if
      (option == 'o' || option == 'O') return 1;
    else if
      (option == 'n' || option == 'N') return 0;
    else
      printf("Seulement O ou N sont acceptables.\n");
    }
}
