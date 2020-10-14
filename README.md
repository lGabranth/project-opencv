project_opencv_detection_visage
===============================

* L'objectif à terme sera d'ouvrir la caméra. 
* Si le programme reconnaît l'utilisateur on affiche son nom.
* Si le programme ne reconnaît pas l'utilisateur, on prend une photo de celui-ci et on entre son nom.
* On affiche un carré autour des visages que la caméra détecte afin de voir si le programme détecte quelqu'un ou non.

*TODO LIST*
| 			Tâche			 | Statut |
|------------------|--------|
| Ouvrir la caméra | 	 ✔		|
| Prendre x photo  | 	 ✔ 	|
| Reconnaître user |   ✘ 		|

Directive du projet:
**IF** visage non reconnu prise de x photos ✘
	Puis affichage console et saisi utilisateur de son nom. ✘
	Enregistrement de la photo avec : nom_utilisateur_i.png (dans le dossier img) ✔
**ELSE** afficher le nom de la personne dans la console et continuer la caméra ✘

Avancement du projet :
- Quand un visage entre dans le champ de la caméra, visage est détecté. Un carré autour du visage. ✔
