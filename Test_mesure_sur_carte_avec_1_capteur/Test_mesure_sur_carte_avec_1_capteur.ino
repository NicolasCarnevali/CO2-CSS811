#include <Wire.h>
#include <SparkFun_I2C_Mux_Arduino_Library.h>
#include <Arduino.h>
#include <ScioSense_ENS16x.h>
#include <AHT20.h>

QWIICMUX myMux;
ENS160 ens160;
AHT20 aht20;

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
#define I2C_ADDRESS_AHT 0x38


void setup() {
  Serial.begin(115200);

pinMode(RST,OUTPUT);
pinMode(MEAS,OUTPUT);
pinMode(CS0, OUTPUT);
pinMode(CS1, OUTPUT);
pinMode(CS2, OUTPUT);
pinMode(A0, OUTPUT);
pinMode(A1, OUTPUT);
pinMode(A2, OUTPUT);
pinMode(LED_R, OUTPUT);
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
Serial.println("\nDétection Multiplexeur ..");

//Wire.setClock(1000);
if (myMux.begin(0x70,Wire) == false)
  {
    Serial.println("Mux not detected. Freezing...");
    while (1)
      ;
  }
Serial.println("Mux detected");

myMux.setPort(0);

ens160.begin(&Wire, I2C_ADDRESS_ENS);
Serial.println("begin..");
    while (ens160.init() != true)
    {
        Serial.print(".");
        delay(1000);
    }
Serial.println("ENS0 connection successful");

ens160.startStandardMeasure();

while (aht20.begin() != true)
  {
    Serial.println("AHT20 not detected. Please check wiring. Freezing.");
    Serial.print(".");
    delay(1000);
  }
Serial.println("AHT connection successful");

}

char buff[100];

void loop() {
  if (ens160.update() == RESULT_OK){
        if (ens160.hasNewData())
        {
          sprintf(buff,"UBA = %d, TVOC = %d, ECO2 = %d, T = %f, H = %f",(uint8_t)ens160.getAirQualityIndex_UBA(),ens160.getTvoc(),ens160.getEco2(),aht20.getTemperature(),aht20.getHumidity());
          //Serial.print("AQI UBA:"); Serial.print((uint8_t)ens160.getAirQualityIndex_UBA());
          //Serial.print(" TVOC:"); Serial.print(ens160.getTvoc());
          //Serial.print(" ECO2:"); Serial.println(ens160.getEco2());
          //Serial.print("\nT: "); Serial.print(Temperature);
          //Serial.print("°C\nH: "); Serial.print(Humidity);
          //Serial.println("%");          
          Serial.println(buff);
          delay(1000);
        }
      }
}
