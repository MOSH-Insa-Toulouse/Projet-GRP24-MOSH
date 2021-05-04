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
- Application android APK réalisée avec MIT APP INVENTOR
- Datasheet du capteur de déformation

## Description

---
Dans le cadre de l'UF MOSH, nous avons conçu un capteur résistif composé de matériaux peu chers, en effet, un simple papier et un crayon nous permettent de créer ce capteur.
Ici, le phénomène physique est l'effet tunnel, en effet, il existe un lien entre la conduction des électrons et la distance interatopique du réseau percolet.
En faisant varier la distance séparant les particules du réeau (en pliant une feuille de papier sur laquelle on aura déposé du graphite par exemple), la conductivité du graphite varie, la résistivité varier également, et donc, la résistance variera aussi en fonction des dimensions du capteur, c'est cette propriété que l'on va exmploiter avec de créer notre capteur résistif. Nous avons également implémenté  un shield sur notre chaine de mesures, ce dernier a été conçu a l'aide du logiciel KICAD et aura un rôle de conditionneur du signal; le shield est composé d'un module Bluetooth, un écran OLED, un encodeur rotatoire,  un amplificateur transimpédance ainsi qu'une entrée analogique pour le capteur résistif; pour finir, nous avons effectué l'ensemble des tests du circuit sur le logiciel LTSpice.

Nous avons ensuite imprimé notre circuit PCB après validation de l'équipe pedagogique, on a utilisé une carte Arduino pour la lecture des mesures et la création des fonctions relatives à l'écran OLED, au module Bluetooth ainsi qu'a l'encodeur rotatoire même si on n'a pas fini de coder cette partie; avec le site MIT App Inventor, nous avons développé une application Android qui a pour but d'envoyer et de recevoir des donnérs via Bluetooth.
Pour tester notre capteur, nous avons utilisé différents types de crayons (B, HB, 2H), nous avons utilité le banc de test mis a disposition en salle d'instrumentation comportant 7 bosses de rayon de courbure différent, les mesures ont été lues directement sur l'écran OLED.

### Code Arduino

Le code Arduino permet d'afficher les valeurs de tension dans la console ainsi que les valeurs de résistance, nous avons implémenté dans le code arduino le calcul de résistance qui été déjà présent dans l'APK android, le code nous fourni également la valeur de tension lue en sortie du circuit transimpédance, il écrit également la valeur de résistance sur l'écran OLED

### KICAD

Sur le logiciel KICAD on a créé les modèles pour l'écran OLED, le module Bluetooth ainsi que l'encodeur rotatoire, il y a également une interface de notre capteur résistif en graphite.


### Application apk

L'application android permet de lire la valeur de tension, elle calcule également la résistance du capteur en connaissance toutes les valeurs des résistances du circuit transimpédance, elle dessine une courbe représentant la variation de tension sur toute la durée d'utilisation du capteur.

## Arduino
---
En résumé, notre code Arduino permet la mesure d'une tension en sortie du circuit transimpédance, d'envoyer la mesure de cette tension par Bluetooth, le code permet le calcul de la résistancede notre capteur résistif, il envoie également cette valeur par Bluetooth, il affiche la valeur de tension dans la console ainsi que la valeur de résistance sur l'écran OLED, n'ayant pas fini le code de l'encodeur rotatoire, toutes les mesures ont été réalisées sans celui-ci.

### Bibliotèques

- Installer la bibliothèque ["Adafruit GFX Library"](https://github.com/MOSH-Insa-Toulouse/Projet-GRP24-MOSH/blob/main/Libraries%20ajout%C3%A9es/Adafruit-GFX-Library-master.zip)
- Installer la bibliothèque ["Adafruit SSD1306"](https://github.com/MOSH-Insa-Toulouse/Projet-GRP24-MOSH/blob/main/Libraries%20ajout%C3%A9es/Adafruit_SSD1306-master.zip)
- Installer la bibliothèque ["Adafruit BusIOa"](https://github.com/MOSH-Insa-Toulouse/Projet-GRP24-MOSH/blob/main/Libraries%20ajout%C3%A9es/Adafruit_BusIO-master.zip)

### Notre code arduino

Notre code Arduino permet de:

- Mesure la tension de sortie du circuit transimpédance
- Calcule la résistance du capteur de graphite connaissant la fonction de transfert du conditionneur
- Envoie la mesure de la tension et de la resistance via Bluetooth sur 1 octet
- Affiche les mesures de tension, de résistance et possède un menu pour choisir entre un offset et un gain numérique sur un écran OLED
- Gère l'encodeur rotatoire

[_Pour télécharger le code_](https://github.com/MOSH-Insa-Toulouse/Projet-GRP24-MOSH/blob/main/code/code_avec_encodeur_et_gain_non_fini.ino)

[_Pour télécharger la version pour les mesures(sans encodeur rotatoire)_](https://github.com/MOSH-Insa-Toulouse/Projet-GRP24-MOSH/blob/main/code/code_banc_test.ino)

```C++
//connexion BT
#include <SoftwareSerial.h>
#define rxPin 10 //cable jaune sur Tx
#define txPin 11 //cable vert sur Rx
#define baudrate 9600
SoftwareSerial mySerial(rxPin,txPin);

volatile byte RX = 0;
byte serialRX;
byte serialTX;
int action=0;

//OLED (définition)
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>

#define oled Adafruit_SSD1306
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)

#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3C for 128x32
oled display(-1);

//Encodeur (définition)
boolean menu = true; //menu 
#define PinSW 2 // SWITCHS
#define PinCLK 4 //CLK OUTPUT
#define PinDT 3 //DT OUTPUT

volatile boolean TurnDetected;
volatile boolean up;
static long virtualPosition=0; //Position Gain    
 
//gestion des valeurs de tension
#define A0 0
int valeur=0;
int R1=100000;
int R3=100000;
int R2=1000;
int R5=10000;
int Vcc=5;

// detection de transition rotatoire
void ISR ()  {                    //Interrupt Service Routine
 if (digitalRead(PinCLK))
   up = digitalRead(PinDT);
 else
   up = !digitalRead(PinDT);
 TurnDetected = true;
}

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS); //initialisation OLED

  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);
  mySerial.begin(9600);

  // test l'affichage correct de l'Oled
 display.clearDisplay();
 display.setTextSize(1);
 display.setTextColor(WHITE);
 display.setCursor(25,15);
 display.println("Projet capteur");
 display.display();
 delay(100);
//pin encoder rotatoire
 pinMode(PinCLK,INPUT);
 pinMode(PinDT,INPUT);  
 pinMode(PinSW,INPUT);
 attachInterrupt (0,ISR,RISING); 
}

//lecture de la valeur sur l'arduino
float lectureValeur () {
  valeur=analogRead(A0);
  return valeur;
  }
//Affichage OLED
void affichage_resistance (float valeur) {
 display.clearDisplay();
 display.setTextSize(1);
 display.setTextColor(WHITE);
 display.setCursor(30,8);
 display.print("valeur res =");
 display.setCursor(30,18);
 float val_res=(1+(R3/R2))*R1*(Vcc/((5*valeur)/1024))-R1-R5; // calcul de la valeur de résistance
 display.print(val_res); //Affichage de la valeur de la résistance
 display.println(" Ohm");
 display.display();
 }

void loop() {
  while (mySerial.available()) {
      
      byte val = map(lectureValeur(), 0, 1024, 0, 255); // conversion 1024/255
  
      mySerial.write(val);

      Serial.println(val);//données envoyées au port

      mySerial.print(",");//données bluetooth
      affichage_resistance(val*4);
  
      sensorValue =   sensorValue * (1+virtualPosition*0.1) //Calcul du Gain

       // Le pushbutton est-il appuyé ?
      if (!(digitalRead(PinSW))) { 
        menu= !menu;
      }

  //modification du gain
      if (TurnDetected)  { 
        if (menu){ 
          if (up  )
        virtualPosition++;
          else
        virtualPosition--;
      }
    TurnDetected = false;

    delay(50);
}
 ```

## Projet KICAD

---
Le projet sur le logiciel KICAD permet de:

- Manipuler le PCB sous forme de Shield pour carte Arduino UNO
- Interfacer capteur graphite via un circuit transimpédance
- Interfacer un module Bluetooth
- Interfacer un écran oled
- Interfacer un encodeur rotatoire

Projet KICAD avec fichiers formats pdf et format GERBER à télécharger [_ici_](https://github.com/MOSH-Insa-Toulouse/Projet-GRP24-MOSH/tree/main/kicad)

### Image du fichier LT SPICE

![alt text](https://github.com/MOSH-Insa-Toulouse/Projet-GRP24-MOSH/blob/main/Images/LTSPICE.png "Screenshot du fichier LT SPICE pour la conception et la simulation du circuit électrique sur le PCB")

_Aperçu du Shield PCB (empreinte GERBER)_

![PCB pdf](https://github.com/MOSH-Insa-Toulouse/Projet-GRP24-MOSH/blob/main/kicad/kicad-B_Cu.pdf "Aperçu du shield PCB en pdf")

### Représentation électrique des composants principaux

![alt text](https://github.com/MOSH-Insa-Toulouse/Projet-GRP24-MOSH/blob/main/Images/Amplificateur.png "Amplificateur")

![alt text](https://github.com/MOSH-Insa-Toulouse/Projet-GRP24-MOSH/blob/main/Images/Modules.png "Modules")

### Placement des composants

![alt text](https://github.com/MOSH-Insa-Toulouse/Projet-GRP24-MOSH/blob/main/Images/Placement.png "Placement des composants")

### Sockets KICAD pour les différents composants

- Amplificateur transimpédance

![alt text](https://github.com/MOSH-Insa-Toulouse/Projet-GRP24-MOSH/blob/main/Images/Amplificateur%20transimpedance.png "Amplificateur transimpédance")

- Module Blueetooth

![alt text](https://github.com/MOSH-Insa-Toulouse/Projet-GRP24-MOSH/blob/main/Images/Module%20BT.png "modules")

- Encodeur rotatoire

![alt text](https://github.com/MOSH-Insa-Toulouse/Projet-GRP24-MOSH/blob/main/Images/Encodeur%20rotatoire.png "modules")


## Application Android apk

---
L'application android développée sur MIT App Inventor sert à:

- Récupérer la mesure de tension
- Calcule et affiche la valeur de la résistance du capteur de graphite connaissant la fonction de transfert du conditionneur (en MΩ)
- Trace un graphique qui décrit l'évolution de la mesure de tension au cours du temps

### MIT App inventor

Le site internet de création d'application [_MIT App Inventor_](https://appinventor.mit.edu/)

### Notre application

Notre code de l'application (format .aia) est à télécharger [_ici_](https://github.com/MOSH-Insa-Toulouse/Projet-GRP24-MOSH/blob/main/APK/Capteur_graph.aia)

Notre code de l'application (format .apk) est à télécharger [_ici_](https://github.com/MOSH-Insa-Toulouse/Projet-GRP24-MOSH/blob/main/APK/Capteur_graph.apk)

## Banc de test

---
Afin de tracer les courbes caractéristiques, on a mesuré la résistance du papier a l’aide d’un objet avec 7 « ponts » de différents rayons de courbure, on a déposé le capteur en papier dessus en faisant attention à reproduire à chaque mesure la même expérience et en déposant le papier au même endroit.. Les résultats sont dans notre [_datasheet_](https://github.com/MOSH-Insa-Toulouse/Projet-GRP24-MOSH/blob/main/Datasheet.pdf)

_Image du banc de test_

![alt text](https://github.com/MOSH-Insa-Toulouse/Projet-GRP24-MOSH/blob/main/Images/BancTest.png "banc de test")

## Pistes de réflexion

---

- Changer le banc de test car les mesures étaient souvent pas très précises et cela nous a demandé de faire plusieurs capteurs différents afin d'obtenir des résultats satisfaisants.

- Finaliser le code de l'encodeur rotatoire(les résultats de mesure sont fait sans la partie encodeur rotatoire)

- Tester et caractériser plus de capteurs (plus de pistes en graphites avec des différents types de crayons à papier)

## Information sur les auteurs

---
Valentin MORIN / Fayçal HOUSSAINI / François THULLIER

- morin.vltn@gmail.com
- houssain@etud.insa-toulouse.fr
- francois.thullier98@gmail.com 

Étudiants à l'INSA de Toulouse en 4ème année Génie Physique
