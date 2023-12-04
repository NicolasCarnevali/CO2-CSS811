#include <Wire.h>
#define MEASURE 13
#define RST_CO2 15
#define WAK_PIN1 16
#define WAK_PIN2 26
#define WAK_PIN3 27
#define SDA 21
#define SCL 22
#define ADD1 2
#define ADD2 4
#define ADD3 12
void setup() {
  Wire.begin();
  pinMode(ADD1,OUTPUT);
  pinMode(ADD2,OUTPUT);
  pinMode(ADD3,OUTPUT);
  pinMode(MEASURE,OUTPUT);
  pinMode(RST_CO2,OUTPUT);
  pinMode(WAK_PIN1,OUTPUT);
  pinMode(WAK_PIN2,OUTPUT);
  pinMode(WAK_PIN3,OUTPUT);
  //Serial.println("1");
  Serial.begin(115200);
  Serial.println("\nI2C Scanner");
digitalWrite(MEASURE, HIGH);
digitalWrite(2, HIGH);
digitalWrite(WAK_PIN1, HIGH);
digitalWrite(WAK_PIN2, HIGH);
digitalWrite(WAK_PIN3, HIGH);
digitalWrite(RST_CO2, LOW);
delay(100);
digitalWrite(RST_CO2, HIGH);
digitalWrite(ADD3,LOW);
  Wire.begin(SDA, SCL);
Wire.setClock(1000);
}
 
void loop() {
  byte error, address;
  int nDevices;
  
  Serial.println("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++ ) {
     //Serial.println("1");
    Wire.beginTransmission(address);
    //Serial.println("2");
    error = Wire.endTransmission();
    //Serial.println("3");
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
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
}