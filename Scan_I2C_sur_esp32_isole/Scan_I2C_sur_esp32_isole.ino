#include <Wire.h>


#define SCL 19
#define SDA 20

#define CS 7
#define ADD 42
#define I2C_ADDRESS 0x52


void setup() {
  // put your setup code here, to run once:
//Wire.begin();
Serial.begin(115200);
Serial.println("\nI2C Scanner");


pinMode(ADD, OUTPUT);
pinMode(CS, OUTPUT);
digitalWrite(ADD,LOW);
digitalWrite(CS, HIGH);
delay(1000);


Wire.begin(SDA, SCL);
//Wire.setClock(1000);


}

void loop() {

  // put your main code here, to run repeatedly:

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
