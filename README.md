						#####################
						# Projet-GRP24-MOSH #
						#####################

Avant d'entamer le projet, nous avons commencé par effectuer une série d'exercices sur la conception de code Arduino 
(par exemple comment gérer un écran OLED). Cela nous a été  très utile pour comprendre les bases d'Arduino 
et de comment manipuler une carte. En effet, durant ces séances nous avions une carte à matrice pour effectuer 
nos tests et notamment pour construire un premier exemplaire de notre montage en cours. 

Cependant, cette carte a été un vrai problème pour nous vu qu'elle comportait un certain nombre de court-circuits,
nous accumulions du retard par rapport au reste du groupe car nous devions en permanence tester si c'était notre PCB 
ou le montage qui n'allait pas.

Nous avons ensuite appris comment utiliser le logiciel KiCad afin de savoir comment designer des circuits électroniques. 
Le but était de pouvoir reproduire une carte PCB pour y implémenter notre propre montage. 
Pour ce faire, nous avons d'abord effectuer un schéma de montage électrique sur LTSpice pour savoir comment rajouter 
un montage transimpédance à notre capteur afin d'amplifier sa sortie de courant et de la convertir en tension proportionnelle 
pour ensuite faire des traitements de celle-ci.
Puis, sur KiCad nous avons eu un problème de librairies car certaines empreintes de composants communs étaient cachées dans 
les fichiers d'installation du logiciel. Nous sommes parvenus à les localiser mais en perdant du temps.

Lors de l'impression de notre carte PCB nous avons eu des soucis liés aux soudures que nous avons par la suite réglés. 
Une fois le montage fait et la carte PCB connectée à la carte Arduino, nous avons donc développé un code Arduino en 
important de GitHub les librairies nécessaires pour faire fonctionner l'écran Oled. Nous avons comme ça testé chaque fonction 
Arduino liée avec les composants (Oled, Module BT,...) afin de s'assurer que les bases du code étaient bonnes. 
Pour le module Bluetooth nous nous sommes inspirés des fichiers de cours présents sur Moodle.
Une fois l'APK développée dans trop de soucis nous avons fait des tests de communication avec le module dans une autre version
 que le code principal pour être sûrs que chaque étape fonctionnait correctement.


Enfin, la technique de mesure utilisée pour le banc de test n'était pas optimale, en effet, on devait changer chaque 5 mesures de capteur, 
sinon les mesures commençaient çà devenir défaillantes en raison de la fragilité du papier.


