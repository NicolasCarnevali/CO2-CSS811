#include <Wire.h>

#define MEASURE 13
#define RST_CO2 150
#define WAK_PIN1 16
#define WAK_PIN2 26
#define WAK_PIN3 27
#define SDA 21
#define SCL 22
#define ADD1 15
#define ADD2 12
#define ADD3 4
#define INT3 17
#define LEDR 33
#define LEDG 25
#define CS0 16
#define CS1 26
#define CS2 27
#define A0 2
#define A1 4
#define A2 12
#define RST_MUX 15



void setup() {
  // put your setup code here, to run once:
//Wire.begin();
Serial.begin(115200);
Serial.println("\nI2C Scanner");

pinMode(LEDR, OUTPUT);
pinMode(LEDG, OUTPUT);
pinMode(MEASURE,OUTPUT);
pinMode(CS0, OUTPUT);
pinMode(CS1, OUTPUT);
pinMode(CS2, OUTPUT);
pinMode(A0, OUTPUT);
pinMode(A1, OUTPUT);
pinMode(A2, OUTPUT);
pinMode(RST_MUX, OUTPUT);

digitalWrite (RST_MUX, LOW);




Wire.begin(SDA, SCL);
Wire.setClock(1000);


}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite (MEASURE, HIGH);
digitalWrite (RST_MUX, HIGH);
digitalWrite (LEDR, HIGH);
digitalWrite (LEDG,HIGH);

digitalWrite (CS0, HIGH);
digitalWrite (CS1, HIGH);
digitalWrite (CS2, HIGH);

digitalWrite (A0, HIGH);
digitalWrite (A1, HIGH);
digitalWrite (A2, LOW);




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
