#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

#define PIR_PIN 34
#define LDR_PIN 35
#define GAS_PIN 32

#define RELAY_LIGHT 26
#define RELAY_FAN 27
#define RELAY_SAFETY 14
#define RELAY_EXTRA 12

#define LED_GREEN 2
#define LED_YELLOW 4
#define LED_RED 5

void setup() {

  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);

  pinMode(RELAY_LIGHT, OUTPUT);
  pinMode(RELAY_FAN, OUTPUT);
  pinMode(RELAY_SAFETY, OUTPUT);
  pinMode(RELAY_EXTRA, OUTPUT);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  digitalWrite(RELAY_LIGHT, LOW);
  digitalWrite(RELAY_FAN, LOW);
  digitalWrite(RELAY_SAFETY, LOW);
  digitalWrite(RELAY_EXTRA, LOW);

  ina219.begin();

}

void loop() {

  bool motion = digitalRead(PIR_PIN);

  int ldr = analogRead(LDR_PIN);

  int gas = analogRead(GAS_PIN);

  float current = ina219.getCurrent_mA();

  float voltage = ina219.getBusVoltage_V();

  float power = voltage * current / 1000.0;

 

  if (motion && ldr < 1500)
  {
      digitalWrite(RELAY_LIGHT, HIGH);
  }
  else
  {
      digitalWrite(RELAY_LIGHT, LOW);
  }

  

  if (ldr > 2500)
  {
      digitalWrite(RELAY_FAN, HIGH);
  }
  else
  {
      digitalWrite(RELAY_FAN, LOW);
  }


  if (gas > 2500)
  {
      digitalWrite(RELAY_SAFETY, HIGH);

      digitalWrite(LED_RED, HIGH);

      digitalWrite(LED_GREEN, LOW);
  }
  else
  {
      digitalWrite(RELAY_SAFETY, LOW);

      digitalWrite(LED_RED, LOW);

      digitalWrite(LED_GREEN, HIGH);
  }


  Serial.print("{");

  Serial.print("\"motion\":");
  Serial.print(motion);

  Serial.print(",");

  Serial.print("\"ldr\":");
  Serial.print(ldr);

  Serial.print(",");

  Serial.print("\"gas\":");
  Serial.print(gas);

  Serial.print(",");

  Serial.print("\"voltage\":");
  Serial.print(voltage);

  Serial.print(",");

  Serial.print("\"current\":");
  Serial.print(current);

  Serial.print(",");

  Serial.print("\"power\":");
  Serial.print(power);

  Serial.println("}");

  delay(1000);

}