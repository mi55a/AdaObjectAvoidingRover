#include "pitches.h"

int buzzer = 8;
int tempo = 120;
int melody[] = {
  //Based on the arrangement at https://www.flutetunes.com/tunes.php?id=192
  NOTE_E5, 4,  NOTE_B4, 8,  NOTE_C5, 8,  NOTE_D5, 4,  NOTE_C5, 8,  NOTE_B4, 8,
  NOTE_A4, 4,  NOTE_A4, 8,  NOTE_C5, 8,  NOTE_E5, 4,  NOTE_D5, 8,  NOTE_C5, 8,
  NOTE_B4, -4,  NOTE_C5, 8,  NOTE_D5, 4,  NOTE_E5, 4,
  NOTE_C5, 4,  NOTE_A4, 4,  NOTE_A4, 8,  NOTE_A4, 4,  NOTE_B4, 8,  NOTE_C5, 8,
  NOTE_D5, -4,  NOTE_F5, 8,  NOTE_A5, 4,  NOTE_G5, 8,  NOTE_F5, 8,
  NOTE_E5, -4,  NOTE_C5, 8,  NOTE_E5, 4,  NOTE_D5, 8,  NOTE_C5, 8,
  NOTE_B4, 4,  NOTE_B4, 8,  NOTE_C5, 8,  NOTE_D5, 4,  NOTE_E5, 4,
  NOTE_C5, 4,  NOTE_A4, 4,  NOTE_A4, 8,  NOTE_A4, 4,  NOTE_B4, 8,  NOTE_C5, 8,
  NOTE_D5, -4,  NOTE_F5, 8,  NOTE_A5, 4,  NOTE_G5, 8,  NOTE_F5, 8,
  NOTE_E5, -4,  NOTE_C5, 8,  NOTE_E5, 4,  NOTE_D5, 8,  NOTE_C5, 8,
  NOTE_B4, 4,  NOTE_B4, 8,  NOTE_C5, 8,  NOTE_D5, 4,  NOTE_E5, 4,
  NOTE_C5, 4,  NOTE_A4, 4,  NOTE_A4, 4,  REST, 4,
  NOTE_E5, 4,  NOTE_B4, 8,  NOTE_C5, 8,  NOTE_D5, 4,  NOTE_C5, 8,  NOTE_B4, 8,
  NOTE_A4, 4,  NOTE_A4, 8,  NOTE_C5, 8,  NOTE_E5, 4,  NOTE_D5, 8,  NOTE_C5, 8,
  NOTE_B4, -4,  NOTE_C5, 8,  NOTE_D5, 4,  NOTE_E5, 4,
  NOTE_C5, 4,  NOTE_A4, 4,  NOTE_A4, 8,  NOTE_A4, 4,  NOTE_B4, 8,  NOTE_C5, 8,
  NOTE_D5, -4,  NOTE_F5, 8,  NOTE_A5, 4,  NOTE_G5, 8,  NOTE_F5, 8,
  NOTE_E5, -4,  NOTE_C5, 8,  NOTE_E5, 4,  NOTE_D5, 8,  NOTE_C5, 8,
  NOTE_B4, 4,  NOTE_B4, 8,  NOTE_C5, 8,  NOTE_D5, 4,  NOTE_E5, 4,
  NOTE_C5, 4,  NOTE_A4, 4,  NOTE_A4, 4,  REST, 4,
  NOTE_E5, 2,  NOTE_C5, 2,
  NOTE_D5, 2,  NOTE_B4, 2,
  NOTE_C5, 2,  NOTE_A4, 2,
  NOTE_GS4, 2,  NOTE_B4, 4,  REST, 8,
  NOTE_E5, 2,  NOTE_C5, 2,
  NOTE_D5, 2,  NOTE_B4, 2,
  NOTE_C5, 4,  NOTE_E5, 4,  NOTE_A5, 2,
  NOTE_GS5, 2,
};

int songLength = sizeof(melody) / sizeof(melody[0]);
int notesCount = songLength / 2;
int wholenote = (60000 * 4) / tempo;

int trigPin = 9;
int echoPin = 10;
int motorPinR = 5;
int motorPinL = 6;
int buttonPin = 2;

int onOff = 0;
int buttonState = 0;
long duration;
long distance;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorPinR, OUTPUT);
  pinMode(motorPinL, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);

  for (int thisNote = 0; thisNote < notesCount * 2; thisNote = thisNote + 2) {
    int divider = melody[thisNote + 1];
    int noteDuration = 0;
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;
    }
    tone(buzzer, melody[thisNote], noteDuration * 0.9);
    delay(noteDuration);
    noTone(buzzer);
  }
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    onOff = 1;
    delay(1000);
  }

  while (onOff == 1) {
    analogWrite(motorPinL, 255);
    analogWrite(motorPinR, 255);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;

    if (distance < 60) {
      analogWrite(motorPinL, 0);
      analogWrite(motorPinR, 0);
      delay(500);
      analogWrite(motorPinR, 255);
      delay(700);
      analogWrite(motorPinR, 0);
      delay(500);
    }

    buttonState = digitalRead(buttonPin);

    if (buttonState == HIGH) {
      analogWrite(motorPinR, 0);
      analogWrite(motorPinL, 0);
      onOff = 0;
      delay(1000);
    }

    Serial.print("Distance: ");
    Serial.println(distance);
    delay(50);
  }
}

