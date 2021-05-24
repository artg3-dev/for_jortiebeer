#include <Arduino.h>

// ------------------------------------------------------------------------
// THESE CONSTANTS SHOULD BE MODIFIED TO MATCH YOUR WANTS/NEEDS AND BASED
// ON YOUR CURRENT WIRING SCHEME
// ------------------------------------------------------------------------

// ******************
// TEMPERATURE SENSOR
// ******************

// Adjust this constant to calibrate your temperature sensor, decreasing it
// will lower your baseline temperature reading.
const float temperatureCalibration = -50.0;

// This is the temperature below which will trigger a change in the motor. A
// reading of 35.0 (or your set value) will not trigger a change.
const float targetTemperature = 35.0;

// **************
// MOTOR SETTINGS
// **************

// These steps represent where the motor will be set when above (warmStep) or
// below (coldStep) the target temperature. These values must be 0-7, anything
// above or below will not cause any change.
const int coldStep = 4;
const int warmStep = 3;

// ****************
// ARDUINO SETTINGS
// ****************

// The analog pin that reads the voltage from your temperature sensor
const int tempSensorPin = A4;

// The digital pins that write to the 4 connections of your motor. If
// the colors vary from your exact motor, please refer to the link below
// for the motor I used to build this script.
// https://components101.com/motors/28byj-48-stepper-motor
const int orangeCoilPin = 8;
const int pinkCoilPin = 9;
const int yellowCoilPin = 10;
const int blueCoilPin = 11;


//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

// ------------------------------------------------------------------------
// DO NOT MODIFY CODE BELOW THIS LINE, UNLESS YOU WANT TO MODIFY THE ACTUAL
// PROGRAMMING
// ------------------------------------------------------------------------

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

const int orange = 0;
const int yellow = 1;
const int pink = 2;
const int blue = 3;
const int red = 4;

int steps[8][5] = {{0, 1, 1, 1, 1}, {0, 0, 1, 1, 1}, {1, 0, 1, 1, 1},
    {1, 0, 0, 1, 1}, {1, 1, 0, 1, 1}, {1, 1, 0, 0, 1}, {1, 1, 1, 0, 1},
    {0, 1, 1, 0, 1}};

float getVoltagetFromADC(float adc) {
    return ((adc/1024.0) * 5.0);
}

float getTempFromVoltage(float voltage) {
    return ((voltage * 100) + temperatureCalibration);
}

float readTemp() {
    float adc = analogRead(tempSensorPin);
    float volts = getVoltagetFromADC(adc);
    return getTempFromVoltage(volts);
}

void setMotorStep(int step) {
    if(step >=0 && step < 8) { // Input validation, steps are 0-7
        digitalWrite(orangeCoilPin, steps[step][orange]);
        digitalWrite(yellowCoilPin, steps[step][yellow]);
        digitalWrite(pinkCoilPin, steps[step][pink]);
        digitalWrite(blueCoilPin, steps[step][blue]);
    }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(tempSensorPin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  float currentTemp = readTemp();
  if(currentTemp < targetTemperature) {
      setMotorStep(coldStep);
  } else {
      setMotorStep(warmStep);
  }
}
