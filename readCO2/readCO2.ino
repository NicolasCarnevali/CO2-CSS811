#include <DFRobot_ENS160.h>


#define I2C_COMMUNICATION 
#ifdef  I2C_COMMUNICATION
  /**
   *   For Fermion version, the default I2C address is 0x53, connect SDO pin to GND and I2C address will be 0x52
   */
  DFRobot_ENS160_I2C ENS160(&Wire, /*I2CAddr*/ 0x53);
  //POUR avoir la mesure du 2eme capteur il faut mettre l'adress a 0x52
  //DFRobot_ENS160_I2C ENS160(&Wire, /*I2CAddr*/ 0x53);
#else
  /**
   * Set up digital pin according to the on-board pin connected with SPI chip-select pin
   * csPin Available Pins. For example: ESP32&ESP8266(D3), m0(6)
   */
  uint8_t csPin = D3;
  DFRobot_ENS160_SPI ENS160(&SPI, csPin);
#endif

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
void setup(void)
{
  pinMode(MEASURE,OUTPUT);
  digitalWrite(MEASURE, HIGH);
  pinMode(ADD1,OUTPUT);
  pinMode(ADD2,OUTPUT);
  pinMode(ADD3,OUTPUT);
  pinMode(INT3,INPUT);
  pinMode(MEASURE,OUTPUT);
  pinMode(RST_CO2,OUTPUT);
  pinMode(WAK_PIN1,OUTPUT);
  pinMode(WAK_PIN2,OUTPUT);
  pinMode(WAK_PIN3,OUTPUT);
 //Activer juste le capteur 1 en passant sa pin CS en 1 et le mettre la pin CS a 0 (SPI) pour le capteur 3
  digitalWrite(WAK_PIN1, HIGH);
  digitalWrite(WAK_PIN2, LOW);
  digitalWrite(WAK_PIN3, LOW);
  pinMode(ADD2,OUTPUT);
  digitalWrite(ADD2,LOW);

  Serial.begin(115200);

  // Init the sensor
  while( NO_ERR != ENS160.begin() ){
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  Serial.println("Begin ok!");

  /**
   * Set power mode
   * mode Configurable power mode:
   *   ENS160_SLEEP_MODE: DEEP SLEEP mode (low power standby)
   *   ENS160_IDLE_MODE: IDLE mode (low-power)
   *   ENS160_STANDARD_MODE: STANDARD Gas Sensing Modes
   */
  ENS160.setPWRMode(ENS160_STANDARD_MODE);

  /**
   * Users write ambient temperature and relative humidity into ENS160 for calibration and compensation of the measured gas data.
   * ambientTemp Compensate the current ambient temperature, float type, unit: C
   * relativeHumidity Compensate the current ambient temperature, float type, unit: %rH
   */
  ENS160.setTempAndHum(/*temperature=*/25.0, /*humidity=*/50.0);

}

void loop()
{
  /**
   * Get the sensor operating status
   * Return value: 0-Normal operation, 
   *         1-Warm-Up phase, first 3 minutes after power-on.
   *         2-Initial Start-Up phase, first full hour of operation after initial power-on. Only once in the sensor’s lifetime.
   * note: Note that the status will only be stored in the non-volatile memory after an initial 24h of continuous
   *       operation. If unpowered before conclusion of said period, the ENS160 will resume "Initial Start-up" mode
   *       after re-powering.
   */
  uint8_t Status = ENS160.getENS160Status();
  Serial.print("Sensor operating status : ");
  Serial.println(Status);

  /**
   * Get the air quality index
   * Return value: 1-Excellent, 2-Good, 3-Moderate, 4-Poor, 5-Unhealthy
   */
  uint8_t AQI = ENS160.getAQI();
  Serial.print("Air quality index : ");
  Serial.println(AQI);

  /**
   * Get TVOC concentration
   * Return value range: 0–65000, unit: ppb
   */
  uint16_t TVOC = ENS160.getTVOC();
  Serial.print("Concentration of total volatile organic compounds : ");
  Serial.print(TVOC);
  Serial.println(" ppb");

  /**
   * Get CO2 equivalent concentration calculated according to the detected data of VOCs and hydrogen (eCO2 – Equivalent CO2)
   * Return value range: 400–65000, unit: ppm
   * Five levels: Excellent(400 - 600), Good(600 - 800), Moderate(800 - 1000), 
   *               Poor(1000 - 1500), Unhealthy(> 1500)
   */
  uint16_t ECO2 = ENS160.getECO2();
  Serial.print("Carbon dioxide equivalent concentration : ");
  Serial.print(ECO2);
  Serial.println(" ppm");

  Serial.println();
  delay(1000);
}