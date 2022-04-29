/*
  Final Project Title: Sonification of 42
  Student Name & ID: Ivy Sun 3183268
  Course Code & Titlel: DIGF-3010-001 Advanced Wearable Electronics
  OCAD University
  Modified by Ivy Sun in Apr. 2022
  Based on:
  Sample Code file "Hello_Speaker" from Adafruit Circuit Playground Examples Library
  Sample Code file "Hello_LightSensor" from Adafruit Circuit Playground Express Examples Library
  Sample Code file "analog_sensors" from Adafruit Circuit Playground Express Examples Library

  Code Examples from "Working With Sensor Data" section of "Make: Wearable Electronics":
  "Mapping" by Prof. Kate Hartman
  https://github.com/katehartman/Make-Wearable-Electronics/tree/master/MWE_Ch07_Mapping
  https://github.com/katehartman/Make-Wearable-Electronics/blob/master/MWE_Ch07_Mapping/MWE_Ch07_Mapping.ino

  Arduino Tutorials/References/Resources/Built-In Examples:
  "Calibration" by SM
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Calibration

  https://www.arduino.cc/reference/en/language/functions/math/constrain/
  https://www.arduino.cc/en/Reference/Map
  https://www.arduino.cc/en/Reference/Millis
  https://www.arduino.cc/en/Reference/While
*/

#include <Adafruit_CircuitPlayground.h>

#define PIN_LDR      A8 // A8
// According to CPX pinout diragram, A8 is for CPX onborad/build-in light sensor.

#define PIN_PIEZO    12 // A0
// According to CPX pinout diragram, A0 is for CPX onborad/build-in speaker.

#define PIN_BUTTON   6 // A1
#define PIN_LED1     9 // A2
#define PIN_LED2     10 // A3
#define PIN_LED3     3 // A4
#define PIN_LED4     2 // A5
#define PIN_LED5     0 // A6
//#define PIN_LED6     1 // A7
// A7 pin of my CPX has connecting issue, thus, deselected 
// LED6 plug directly into the power supply

#define CALIBRATION_DURATION 5 // in seconds

/*
  // Pitch definitions in Hz
  #define PITCH_MIN_LOWER 5
  #define PITCH_MIN_UPPER 170
  #define PITCH_MAX_LOWER 20
  #define PITCH_MAX_UPPER 1000
*/

// These defines set the range of sound frequencies when mapping to the sensor value.
#define TONE_FREQ_MIN    400
#define TONE_FREQ_MAX    1000

int sensorValue = 0, sensorMin = 700, sensorMax = 0;
//int mappedsensorValue = 0;

//int pitchMin = TONE_FREQ_MIN, pitchMax = TONE_FREQ_MAX;

unsigned long lastPressedButton = 0;
byte buttonState = 0;

void setup()
{
  // Setup serial port.
  Serial.begin(9600);
  
  // print the sensor and mapped sensor values:
  Serial.print("Light Sensor Value: ");
  Serial.print(sensorValue);
  //Serial.print(", Mapped Light Sensor Value: ");
  //Serial.println(mappedsensorValue);

  // delay between readings:
  delay(100);

  //Serial.println(analogRead(PIN_LDR));

  // Setup Circuit Playground library.
  CircuitPlayground.begin();

  pinMode(PIN_PIEZO, OUTPUT);
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);
  pinMode(PIN_LED4, OUTPUT);
  pinMode(PIN_LED5, OUTPUT);
  //pinMode(PIN_LED6, OUTPUT);

  //pinMode(PIN_LDR, INPUT);

  pinMode(PIN_BUTTON, INPUT_PULLUP);

  //pinMode(PIN_POTI_MIN, INPUT);
  //pinMode(PIN_POTI_MAX, INPUT);

  // Map the sensor value to a tone frequency.
  //int frequency = map(sensorValue, sensorMin, sensorMax, TONE_FREQ_MIN, TONE_FREQ_MAX);

  tone(PIN_PIEZO, 550);

  //CircuitPlayground.playTone(frequency, 100);

  while (millis() < (CALIBRATION_DURATION * 1000)) {
    sensorValue = analogRead(PIN_LDR);
    sensorMax = max(sensorValue, sensorMax);
    sensorMin = min(sensorValue, sensorMin);
  }
  noTone(PIN_PIEZO);
  //digitalWrite(PIN_PIEZO, LOW);
  //CircuitPlayground.playTone(frequency, 100);
}

void loop()
{
  if ((millis() - lastPressedButton > 200) && digitalRead(PIN_BUTTON) == LOW) {
    lastPressedButton = millis();
    buttonState++;
    buttonState %= 7;
    // six modes of preset tempo in total
    // pressed time should at least an interval of 0.2 seconds

    //pitchMin = PITCH_MIN_LOWER + map(analogRead(PIN_POTI_MIN), 0, 1023, 0, PITCH_MIN_UPPER);
    //pitchMin = constrain(pitchMin, TONE_FREQ_MIN, TONE_FREQ_MAX);
    //pitchMax = PITCH_MAX_LOWER + map(analogRead(PIN_POTI_MAX), 0, 1023, 0, PITCH_MAX_UPPER);
    //pitchMax = constrain(pitchMax, TONE_FREQ_MIN, TONE_FREQ_MAX));

  }


  if (buttonState > 0) {
    sensorValue = analogRead(PIN_LDR);

    // apply the calibration to the sensor reading
    sensorValue = map(sensorValue, sensorMin, sensorMax, TONE_FREQ_MIN, TONE_FREQ_MAX);
    //mappedsensorValue = map(sensorValue, sensorMin, sensorMax, TONE_FREQ_MIN, TONE_FREQ_MAX);

    // in case the sensor value is outside the range seen during calibration
    sensorValue = constrain(sensorValue, TONE_FREQ_MIN, TONE_FREQ_MAX);

    //CircuitPlayground.playTone(PIN_PIEZO, sensorValue);

    tone(PIN_PIEZO, sensorValue);

    //analogWrite(PIN_LED1, sensorValue);
    digitalWrite(PIN_LED1, HIGH);;
    //analogWrite(PIN_LED1, mappedsensorValue);
    //delay(500);
    //digitalWrite(PIN_LED1, LOW);
    //delay(500);
    
    //analogWrite(PIN_LED2, sensorValue);
    digitalWrite(PIN_LED2, HIGH);
    //delay(1000);
    //digitalWrite(PIN_LED2, LOW);
    //delay(500);
    
    //analogWrite(PIN_LED3, sensorValue);
    digitalWrite(PIN_LED3, HIGH);
    //delay(750);
    //digitalWrite(PIN_LED3, LOW);
    //delay(300);

    //analogWrite(PIN_LED4, sensorValue);
    digitalWrite(PIN_LED4, HIGH);
    //delay(200);
    //digitalWrite(PIN_LED4, LOW);
    //delay(500);

    //analogWrite(PIN_LED5, sensorValue);
    digitalWrite(PIN_LED5, HIGH);
    //delay(800);
    //digitalWrite(PIN_LED5, LOW);
    //delay(750);

    //analogWrite(PIN_LED6, sensorValue);
    //digitalWrite(PIN_LED6, HIGH);
    //delay(900);
    //digitalWrite(PIN_LED6, LOW);
    //delay(300);

    //digitalWrite(PIN_PIEZO, HIGH);
    
    if (buttonState == 2) {
      //tone(PIN_PIEZO, sensorValue);
      delay(160);
    } else if (buttonState == 3) {
      //tone(PIN_PIEZO, sensorValue);
      delay(75);
    }
    else if (buttonState == 4) {
      //tone(PIN_PIEZO, sensorValue);
      delay(250);
    }
    else if (buttonState == 5) {
      //tone(PIN_PIEZO, sensorValue);
      delay(400);
    }
    else if (buttonState == 6) {
      //tone(PIN_PIEZO, sensorValue);
      delay(100);
    }
  }

  else {
    noTone(PIN_PIEZO);
    digitalWrite(PIN_LED1, LOW);
    digitalWrite(PIN_LED2, LOW);
    digitalWrite(PIN_LED3, LOW);
    digitalWrite(PIN_LED4, LOW);
    digitalWrite(PIN_LED5, LOW);
    //digitalWrite(PIN_LED6, LOW);
  }
}
