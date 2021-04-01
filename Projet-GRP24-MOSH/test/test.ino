#include<SoftwareSerial.h>
#define baudrate 9600
#define BTbaudrate 38400
#define TxD 11
#define RxD 10

// 98 1f 

String bt = "";

int sensorPin = A0;
int sensorValue = 0;


SoftwareSerial BT(RxD, TxD);


void setup() {
  
  Serial.begin(baudrate);
  BT.begin(BTbaudrate);

}

void loop() {
  
  if(BT.available()){
    bt = BT.readString();
  }
  Serial.println(bt);
  while(!BT.available());
}
