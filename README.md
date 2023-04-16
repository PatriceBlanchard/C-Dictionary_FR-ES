C-Dictionnaire_FR-ES  
-------------------------------
  
__Compilation et exécution :__  
<br>
  
gcc -Wall dico.c
a.out echantillon-test  

<br>
Exemple d'utilisation :
<br>
<br>
Dictionnaire Français-Espagnol  
<br>
<br>
Saisir un mot à traduire :
absolutisme
<br>
<br>
Mot Français : absolutisme - Catégorie : [n]
Mot Espagnol : absolutismo - Catégorie : [n]
<br>
<br>
(Continuer : O/N):
n

-------------------------------
__Exécution de deux tests :__
<br>

gcc -Wall -DTEST dico.c
<br>
La commande ci-dessus affichera :
<br>
Test1 : Imprimer les mots français dans un fichier
Impression des mots en français dans le fichier mot_fr.txt terminée.
<br>
Test2 : Rétroconstruction du fichier initial
Rétro-construction dans le fichier retro_construction.txt terminée.
