project_opencv_detection_visage
===============================

* L'objectif, à terme, sera d'ouvrir la caméra. 
* Si le programme détecte que l'utilisateur porte un masque, on affiche un rond vert autour de sa tête avec le texte "Masque !".
* Si le programme détecte que l'utilisateur ne porte pas de masque, on affiche un rond rouge autour de sa tête avec le texte "Pas de masque !".

*TODO LIST*
| 			 Tâche			 | Statut |
|--------------------|--------|
|  Ouvrir la caméra  | 	 ✔		|
|  Détecter le nez   | 	 ✔ 	|
| Détecter la bouche |   ✔ 	|
|  Afficher le rond  |   ✔ 	|
|  Afficher le text  |   ✔ 	|
|  Modifier couleur  |   ✔ 	|

Avancement du projet :
- Quand un visage entre dans le champ de la caméra, visage est détecté. Un carré autour du visage. ✔
- On détecte le nez et la bouche. ✔
- Si le programme ne détecte ni le nez, ni la bouche, on part du postulat que l'utilisateur porte un masque : 
	* Si masque : On affiche un rond vert avec le texte prévu. ✔
	* Sinon : On affiche un rond rouge avec le texte prévu. ✔