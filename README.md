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
Mot Français : absolutisme - Catégorie : [n] 
<br>
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
<br>
La commande ci-dessus affichera :
<br>
<br>
Test1 : Imprimer les mots français dans un fichier
Impression des mots en français dans le fichier mot_fr.txt terminée.
<br>
<br>
Test2 : Rétroconstruction du fichier initial
Rétro-construction dans le fichier retro_construction.txt terminée.
