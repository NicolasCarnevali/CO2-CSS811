#include <Wire.h>
#include <SparkFun_I2C_Mux_Arduino_Library.h>


QWIICMUX myMux;


#define SCL 22
#define SDA 21

#define CS0 16
#define CS1 26
#define CS2 27

#define A0 2
#define A1 4
#define A2 12

#define RST 15
#define MEAS 13

#define LED_R 33
#define LED_G 25

#define I2C_ADDRESS_ENS 0x52
#define I2C_ADDRESS_AHT20 0x38



void setup() {
  // put your setup code here, to run once:
//Wire.begin();
Serial.begin(115200);
Serial.println("\nI2C Scanner");

pinMode(RST,OUTPUT);
pinMode(MEAS,OUTPUT);
pinMode(CS0, OUTPUT);
pinMode(CS1, OUTPUT);
pinMode(CS2, OUTPUT);
pinMode(A0, OUTPUT);
pinMode(A1, OUTPUT);
pinMode(A2, OUTPUT);
pinMode(LED_R,OUTPUT);
pinMode(LED_G,OUTPUT);



digitalWrite(RST, HIGH);
digitalWrite(MEAS,HIGH);
digitalWrite(CS0, HIGH);
digitalWrite(CS1, HIGH);
digitalWrite(CS2, HIGH);
digitalWrite(A0,LOW);
digitalWrite(A1,LOW);
digitalWrite(A2,LOW);

delay(1000);

Wire.begin(SDA, SCL);

//Wire.setClock(1000);
if (myMux.begin(0x70,Wire) == false)
  {
    Serial.println("Mux not detected. Freezing...");
    while (1)
      ;
  }
Serial.println("Mux detected");

myMux.setPort(0);

}


void loop() {

  // put your main code here, to run repeatedly:

  byte error, address;
  int nDevices;
  byte MyCurrentPort;
  
  MyCurrentPort = myMux.getPort();
  Serial.print("Current Port of MUX : ");Serial.println(MyCurrentPort);
  if(MyCurrentPort == 0)
  {
    digitalWrite(LED_R,LOW);
    digitalWrite(LED_G,LOW);
  }
  else if (MyCurrentPort == 1)
  {
    digitalWrite(LED_R,HIGH);
    digitalWrite(LED_G,LOW);
  }
  else if (MyCurrentPort ==2){
    digitalWrite(LED_R,HIGH);
    digitalWrite(LED_G,HIGH);
  }

  Serial.println("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++ ) {
     //Serial.println("1");
    Wire.beginTransmission(address);
    //Serial.println("2");
    error = Wire.endTransmission();
    //Serial.println("3");
    if (error == 0) {
      if(MyCurrentPort == 0){
        Serial.print("ID : 0 I2C device found at address 0x");        
      }
      else if(MyCurrentPort == 1){
        Serial.print("ID : 1 I2C device found at address 0x");        
      }
      else if(MyCurrentPort == 2){
        Serial.print("ID : 2 I2C device found at address 0x");        
      }
      if (address<16) {
        Serial.print("0");
      }
      Serial.println(address,HEX);
      nDevices++;
    }
    else if (error==4) {
      Serial.print("Unknow error at address 0x");
      if (address<16) {
        Serial.print("0");
      }
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found\n");
  }
  else {
    Serial.println("done\n");
  }

  delay(5000);      

if (MyCurrentPort == 0)
  {
    myMux.setPort(1);
  }
  else if (MyCurrentPort == 1)
  {
    myMux.setPort(2);
  }
  else if (MyCurrentPort == 2)
  {
    myMux.setPort(0);
  }

  delay(5000);

}
