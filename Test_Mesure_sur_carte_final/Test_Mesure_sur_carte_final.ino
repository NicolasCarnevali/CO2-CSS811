#include <Wire.h>
#include <SparkFun_I2C_Mux_Arduino_Library.h>
#include <Arduino.h>
#include <ScioSense_ENS16x.h>
#include <AHT20.h>
#include <stdbool.h>
#include <inttypes.h>


QWIICMUX myMux;
ENS160 ens160_0;
ENS160 ens160_1;
ENS160 ens160_2;
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
  // put your setup code here, to run once:
//Wire.begin();
config();
}

void loop() {
  // put your main code here, to run repeatedly:
  byte MyCurrentPort;
  MyCurrentPort = myMux.getPort();


  //ens160.wait();
  //Serial.print("\nDébut des mesures sur capteur : ");Serial.println(MyCurrentPort);

  //measure(MyCurrentPort);
  ens160_0.update();
  Serial.print("\nT: "); Serial.print(aht20.getTemperature(),2);
  Serial.print("°C;H: "); Serial.print(aht20.getHumidity(),2);
  Serial.print("%;");
  Serial.print("TVOC:"); Serial.print(ens160_0.getTvoc());
  Serial.print(";ECO2:"); Serial.println(ens160_0.getEco2());

  //Serial.println("Changement de capteur ...");
  //Serial.print("Current Port : "); Serial.println(myMux.getPort());

  /*if (MyCurrentPort == 0)
  {
    myMux.setPort(1);
    digitalWrite(LED_R,HIGH);
    digitalWrite(LED_G,LOW);
  }
  else if (MyCurrentPort == 1)
  {
    myMux.setPort(2);
    digitalWrite(LED_R,HIGH);
    digitalWrite(LED_G,HIGH);
  }
  else if (MyCurrentPort == 2)
  {
    myMux.setPort(0);
    digitalWrite(LED_R,LOW);
    digitalWrite(LED_G,LOW);
  }
  Serial.println("Changement effectué");
  Serial.print("Current Port : "); Serial.println(myMux.getPort());
  delay(1000);*/
}


void measure(int ID)
{
  switch(ID){
    case 0 : 
      if (ens160_0.update() == RESULT_OK){
        if (ens160_0.hasNewData())
        {
          Serial.print("Status = ");Serial.println(ens160_0.getDeviceStatus());
          Serial.print("AQI UBA:"); Serial.print((uint8_t)ens160_0.getAirQualityIndex_UBA());
          Serial.print(" TVOC:"); Serial.print(ens160_0.getTvoc());
          Serial.print(" ECO2:"); Serial.println(ens160_0.getEco2());
        }
      }
    break;

    case 1 : 
      //if (ens160_1.update() == RESULT_OK){
        //if (ens160_1.hasNewData())
        //{
          Serial.print("Status = ");Serial.println(ens160_1.getDeviceStatus());
          ens160_1.update();
          Serial.println("ENS160_1 measure :");
          Serial.print("AQI UBA:"); Serial.print((uint8_t)ens160_1.getAirQualityIndex_UBA());
          Serial.print(" TVOC:"); Serial.print(ens160_1.getTvoc());
          Serial.print(" ECO2:"); Serial.println(ens160_1.getEco2());
        //}
      //}
    break;

    case 2 : 
      //if (ens160_2.update() == RESULT_OK){
        //if (ens160_2.hasNewData())
        //{
          Serial.print("ENS160_2 measure :");
          Serial.print("AQI UBA:"); Serial.print((uint8_t)ens160_2.getAirQualityIndex_UBA());
          Serial.print(" TVOC:"); Serial.print(ens160_2.getTvoc());
          Serial.print(" ECO2:"); Serial.println(ens160_2.getEco2());
        //}
      //}
    break;

    default : 
      Serial.println("Port Mux inconnu");
      break; 
  }
}


void config()
{
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

ens160_0.begin(&Wire, I2C_ADDRESS_ENS);
Serial.println("begin..");
    while (ens160_0.init() != true)
    {
        Serial.print(".");
        delay(1000);
    }
Serial.println("ENS0 connection successful");

ens160_0.startStandardMeasure();
ens160_0.wait();

myMux.setPort(1);

ens160_1.begin(&Wire, I2C_ADDRESS_ENS);
Serial.println("begin..");
    while (ens160_1.init() != true)
    {
        Serial.print(".");
        delay(1000);
    }
Serial.println("ENS1 connection successful");

ens160_1.startStandardMeasure();
ens160_1.wait();

myMux.setPort(2);

ens160_2.begin(&Wire, I2C_ADDRESS_ENS);
Serial.println("begin..");
    while (ens160_2.init() != true)
    {
        Serial.print(".");
        delay(1000);
    }
Serial.println("ENS2 connection successful");
ens160_2.startStandardMeasure();
ens160_2.wait();

myMux.setPort(0);

while (aht20.begin() != true)
  {
    Serial.println("AHT20 not detected. Please check wiring. Freezing.");
    Serial.print(".");
    delay(1000);
  }
Serial.println("AHT connection successful");
}
