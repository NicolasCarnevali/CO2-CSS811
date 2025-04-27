
#include <Arduino.h>
#include <Wire.h>
#include <ScioSense_ENS16x.h>


#define SCL 19
#define SDA 20
#define CS 7
#define I2C_ADDRESS 0x52

#define USE_INTERRUPT
#define INTN 2

ENS160 ens160;

void setup()
{
    pinMode(CS, OUTPUT);
    digitalWrite(CS, HIGH);

    Serial.begin(115200);
    ens160.enableDebugging(Serial);

    Wire.begin(SDA,SCL);
    ens160.begin(&Wire, I2C_ADDRESS);

    Serial.println("begin..");
    while (ens160.init() != true)
    {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("success");


//#ifdef USE_INTERRUPT
//   ens160.setInterruptPin(INTN);
//    ens160.writeConfiguration
//    (
//          ENS16X_CONFIGURATION_INTERRUPT_ENABLE
//        | ENS16X_CONFIGURATION_NEW_GENERAL_PURPOSE_DATA
//        | ENS16X_CONFIGURATION_NEW_DATA
//    );
//#endif

    ens160.startStandardMeasure();
}

void loop()
{
     ens160.wait();

     // Enable Tools->Serial Plotter to see the sensor output as a graph

     if (ens160.update() == RESULT_OK)
     {
        if (ens160.hasNewData())
        {
            Serial.print("AQI UBA:"); Serial.print((uint8_t)ens160.getAirQualityIndex_UBA());
            Serial.print("\tTVOC:"); Serial.print(ens160.getTvoc());
            Serial.print("\tECO2:"); Serial.println(ens160.getEco2());
        }
     }
}
