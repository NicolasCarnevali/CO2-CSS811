#include "Adafruit_CCS811.h"
#include "DFRobot_ENS160.h"
#define LED_R 33
#define LED_V 25
#define Measure 13

DFRobot_ENS160_I2C ENS160(&Wire,0x53);

void setup() {
  Serial.begin(9600);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_V, OUTPUT);
  pinMode(Measure, OUTPUT);

  while( NO_ERR !=ENS160.begin() ) {
    Serial.println("communication with device failed");
    delay (3000);
  }
  Serial.println("Begin");

  ENS160.setPWRMode(ENS160_STANDARD_MODE);
  ENS160.setTempAndHum(25.0, 50.0);
}
// the setup function runs once when you press reset or power the board

// the loop function runs over and over again forever
void loop() {
  digitalWrite(Measure, HIGH);

  uint8_t ECO2 = ENS160.getECO2();

  Serial.print("ECO2");
  Serial.print(ECO2);
  Serial.println(" ppm ");

  delay(1000);

  

}

