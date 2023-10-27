/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-led-blink
 */
#define LED_R 33
#define LED_V 25
#define Measure 13
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin GPIO18 as an output.
  Serial.begin(9600);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_V, OUTPUT);
  pinMode(Measure, INPUT);

}

// the loop function runs over and over again forever
void loop() {
 // digitalWrite(Measure, HIGH);
 // digitalWrite(LED_R, HIGH);
  digitalWrite(LED_V, HIGH); // turn the LED on
//   delay(500);             // wait for 500 milliseconds
//   digitalWrite(LED_R, LOW);  // turn the LED off
//   delay(500);             // wait for 500 milliseconds
}
