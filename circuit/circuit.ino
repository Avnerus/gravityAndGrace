#include "pumpng.h"

PumpNg musclePump(13, 4, 3, 6);
PumpNg musclePump2(8, 9, 10, 6);
int muscle1ReleasePin = 7;

PumpNg muscle2Pump(A0, 12, 5, A1);
PumpNg muscle2Pump2(A2, A3, 11, A1);
int muscle2ReleasePin = 2;

int stretch1Sum = 0;
int stretch2Sum = 0;

int stretchCount = 0;

int STRETCH1_THRESHOLD = 340;
int STRETCH2_THRESHOLD = 320;


void setup() {
  Serial.begin(9600); 
  Serial.println("Gravity and Grace starting");
  musclePump.init();
  musclePump2.init();
  muscle2Pump.init();
  muscle2Pump2.init();

  pinMode(2, OUTPUT);
  pinMode(7, OUTPUT);

  //pinMode(killPin, INPUT);
}

void loop() {
/*
    musclePump.inflate();
    musclePump2.inflate();
    
    muscle2Pump.inflate();
    muscle2Pump2.inflate();
    digitalWrite(2, LOW);
    digitalWrite(7, HIGH);
    delay(10000);
    musclePump.stop();
    musclePump2.stop();
    muscle2Pump.stop();
    muscle2Pump2.stop();
    digitalWrite(2, HIGH);
    digitalWrite(7, LOW);
    delay(3000); */

    stretch1Sum += analogRead(A4);
    stretch2Sum += analogRead(A5);
    stretchCount++;

    if (stretchCount == 2) {
        int stretch1Average = stretch1Sum / 3;
        int stretch2Average = stretch2Sum / 3;
        
        Serial.println(stretch1Average);

        if (stretch1Average > STRETCH1_THRESHOLD) {
            muscle2Pump.inflate();
            muscle2Pump2.inflate();
            digitalWrite(muscle2ReleasePin, LOW);
        } else {
            muscle2Pump.stop();
            muscle2Pump2.stop();
            digitalWrite(muscle2ReleasePin, HIGH);
        }
        if (stretch2Average > STRETCH2_THRESHOLD) {
            musclePump.inflate();
            musclePump2.inflate();
            digitalWrite(muscle1ReleasePin, HIGH);
        } else {
            musclePump.stop();
            musclePump2.stop();
            digitalWrite(muscle1ReleasePin, LOW);
        }

        stretchCount = 0;
        stretch1Sum = 0;
        stretch2Sum = 0;
    }

}

