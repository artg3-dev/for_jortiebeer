#include <Arduino.h>

const int tempSensorPin = A4;

const int orangeCoilPin = 8;
const int pinkCoilPin = 9;
const int yellowCoilPin = 10;
const int blueCoilPin = 11;

const float temperatureCalibration = -50.0;


const int orange = 0;
const int yellow = 0;
const int pink = 0;
const int blue = 0;

int step1[] = {0, 1, 1, 1};
int step2[] = {0, 0, 1, 1};
int step3[] = {1, 0, 1, 1};
int step4[] = {1, 0, 0, 1};
int step5[] = {1, 1, 0, 1};
int step6[] = {1, 1, 0, 0};
int step7[] = {1, 1, 1, 0};
int step8[] = {0, 1, 1, 0};

float getVoltagetFromADC(float adc) {
    return ((adc/1024.0) * 5.0);
}

float getTempFromVoltage(float voltage) {
    return ((voltage * 100) + temperatureCalibration);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(tempSensorPin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  // float adc = analogRead(tempSensorPin);
  // float volts = getVoltagetFromADC(adc);
  // float c = getTempFromVoltage(volts);
  // Serial.println(adc);
  // Serial.println(volts);
  // Serial.println(c);
  // Serial.println("--------------");
  // delay(500);
}
