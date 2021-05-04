# Projet Capteur Graphite GRP24

Ce Git contient les ressources nécessaire pour le projet 2021 qui s'inscrit dans l'UF *"Du capteur au banc de Test"* de l'INSA de Toulouse, 4ème année de Génie Physique.

## Sommaire

---

- [Livrables](##Livrables)
- [Description](##Description)
- [Arduino](##Arduino)
  - [Bibliothèques](###Bibliotèques)
  - [Notre code Arduino](###Notre-Code-Arduino)
- [KICAD](##Projet-KICAD)
  - [Placement des composants](###Placement-des-composants)
  - [Sockets KICAD pour les différents composants](###Sockets-KICAD-pour-les-différents-composants)
- [Application Android apk](##Application-Android-apk)
  - [MIT App Inventor](###MIT-App-Inventor)
  - [Notre application](###Notre-Application)
- [Banc de test](##Banc-de-test)
- [Pistes de réflexion](##Pistes-de-réflexion)
- [Information sur les auteurs](##Information-sur-les-auteurs)

## Livrables

---

- Shield PCB
- Code Arduino permettant la mesure de la resistance R et la tension, ainsi que le contrôle des fonctionnalités BT, OLED et capteur rotatoire
- Application android APK réalisé avec MIT APP INVENTOR
- Protocole de mesure et le programme Arduino pour le banc de test
- Datasheet du capteur de déformation/ jauge de contrainte

## Description

---
Ce projet a pour but le développement d'un **capteur de déformation mécanique** à base de matériaux peut onéreux ainsi que écoresponsable. Le principe physique qui fait notre projet possible le transport des électrons entre les nanoparticules de graphite, qui lui même, est régi par l'effet tunnel. Ce capteur exploite le lien entre la conduction électrique des électrons et l'espace moyen entre les particules d'un réseau granuleux. En effet, l'éloignement et le rapprochement du réseau induit par un stress mécanique fait varier la **conductivité électrique** de la piste de graphite, puisque la distance inter-particule a été affectée. La déformation de cette dernière induit une variation de résistance électrique réversible et exploitable pour créer une jauge de contrainte. Le **conditionneur** de notre projet est un shield comportant un circuit électrique d'amplificateur transimpédance, ainsi que des interface pour un module bluetooth, un capteur rotatoire, une écran OLED et bien sur, l'entrée analogique de la jauge de contrainte. Ce shield a été déssiné sur **KICAD** et des simulations du circuit transimpédance ont été faits sur **LT SPICE**. Le code principala été réalisé en C++ sur l'**IDE Arduino UNO**. Finalement une application android a été développé sur **MIT App Inventor** pour communiquer et recevoir des données à distance, via bluetooth. Un banc de test a été réalisé avec un rapporteur et les pistes de graphites dessinées sur des feuilles de papier. Un protocole de mesure sera spécifié pour exposer commment nous avons exploité et étudié la réponse de déformation de différents capteurs.

### Code Arduino

- Mesure la tension de sortie du circuit transimpédance
- Calcule la résistance du capteur de graphite connaissant la fonction de transfert du conditionneur
- Envoie la mesure de la tension et de la resistance via Bluetooth sur 1 octet
- Affiche les mesures de tension, de résistance et possède un menu pour choisir entre un offset et un gain numérique sur un écran OLED
- Gère l'encodeur rotatoire

### KICAD

- PCB sous forme de Shield pour carte Arduino UNO
- Interface du capteur graphite via un circuit transimpédance
- Interface pour un module Bluetooth
- Interface pour un écran oled
- Interface pour un encodeur rotatoire

### Application apk

- Récupère la mesure de tension
- Calcule et affiche la valeur de la résistance du capteur de graphite connaissant la fonction de transfert du conditionneur (en MΩ)
- Trace un graphique qui décrit l'évolution de la mesure de tension au cours du temps
- Mise à l'échelle automatique de l'ordonnée du graphique

## Arduino

---

### Bibliotèques

- Installer la bibliothèque ["Adafruit GFX Library"](XXX)
- Installer la bibliothèque ["Adafruit SSD1306"](XXX)
- Installer la bibliothèque ["Adafruit BusIOa"](XXX)

### Notre code arduino

Notre code Arduino permet de:

- Mesure la tension de sortie du circuit transimpédance
- Calcule la résistance du capteur de graphite connaissant la fonction de transfert du conditionneur
- Envoie la mesure de la tension et de la resistance via Bluetooth sur 1 octet
- Affiche les mesures de tension, de résistance et possède un menu pour choisir entre un offset et un gain numérique sur un écran OLED
- Gère l'encodeur rotatoire

[_Pour télécharger le code_](XXX)

```C++

XXX

 ```

## Projet KICAD

---
Le projet sur le logiciel KICAD permet de:

- Manipuler le PCB sous forme de Shield pour carte Arduino UNO
- Interface du capteur graphite via un circuit transimpédance
- Interface pour un module Bluetooth
- Interface pour un écran oled
- Interface pour un encodeur rotatoire

Projet KICAD avec fichiers formats pdf et format GERBER à télécharger [_ici_](XXX)

_Aperçu du fichier LT SPICE_

![alt text] (XXX "Screenshot du fichier LT SPICE pour la conception et la simulation du circuit électrique sur le PCB")

_Aperçu du Shield PCB (empreinte GERBER)_

![PCB pdf](XXX "Aperçu du shield PCB en pdf")

### Placement des composants

![alt text](XXX "Placement des composants")

### Sockets KICAD pour les différents composants

- Amplificateur transimpédance

![alt text](XXX "Amplificateur transimpédance")

- Modules Blueetooth/OLED/Encodeur

![alt text](XXX "modules")

## Application Android apk

---
L'application android développée sur MIT App Inventor sert à:

- Récupérer la mesure de tension
- Calcule et affiche la valeur de la résistance du capteur de graphite connaissant la fonction de transfert du conditionneur (en MΩ)
- Trace un graphique qui décrit l'évolution de la mesure de tension au cours du temps

### MIT App inventor

Le site internet de création d'application [_MIT App Inventor_](https://appinventor.mit.edu/)

### Notre application

Notre code de l'application (format .aia) est à télécharger [_ici_]()

Notre code de l'application (format .apk) est à télécharger [_ici_]()

_Apperçu de l'application_
![alt text](XXX "apperçu de l'application")

## Banc de test

---
Nous avons réalisé un banc de test très "low cost" avec lequel nous avons fait toutes les mesures pour la caractérisation des différents capteurs. Les résultats sont dans notre [_datasheet_](XXX)

Protocole du banc de test/ utilisation optimale et conseillée du capteur (90º/-90º):
Fixer les deux extrémités de la jauge en papier a des surfaces rigides et de longueur suffisante pour permettre de lire les angles sur les notations du support (rapporteur dans ce cas).
Pour ce faire nous devons conserver un carré d'environ 1cm de côté comme prolongation de la jauge. Sur ce carré il n'y a pas de piste en graphite.
Fixer la base de la jauge perpendiculairement à l'axe des 0º et la fin de la zone d'accroche des pinces en cuivre à 5mm du centre du rapporteur.
Déplacer l'autre extremité par des pas de 10º en balayant de 90º jusqu'à -90º par rapport à l'axe neutre de la base.

_Image du banc de test_
![alt text]( "banc de test")

## Pistes de réflexion

---

- Améliorer le banc de test parcequ'il est susceptibles à  induire plusieurs erreurs aléatoires lors des mesures.

- Implementer la gestion de l'encodeur rotatoire pour le calcule de l'offset et le gain numérique, ains qu'un deboucing (soit analogique ou numérique)

- Tester et caractériser plus de capteurs (plus de pistes en graphites avec des différents types de crayons à papier)

## Information sur les auteurs

---
Valentin MORIN / Fayçal HOUSSAINI / François THULLIER

- 
- 
-

Étudiants à l'INSA de Toulouse en 4ème année Génie Physique
