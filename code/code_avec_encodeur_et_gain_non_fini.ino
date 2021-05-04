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
