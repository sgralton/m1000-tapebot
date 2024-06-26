#include <EEPROM.h>
int address = 0;
byte value;

const int twenty_pin = 6;
const int cm_pin = 4;
const int mm_pin = 5;
const int knife_pin = 7;

const int array_length = 3;
const int distance [array_length] = {53, 77, 101};
int seq = 0;
bool knife_triggered = false;

void setup() {
  Serial.begin(9600);

  pinMode(twenty_pin, OUTPUT);
  pinMode(cm_pin, OUTPUT);
  pinMode(mm_pin, OUTPUT);
  pinMode(knife_pin, INPUT);
  digitalWrite(twenty_pin, HIGH);
  digitalWrite(cm_pin, HIGH);
  digitalWrite(mm_pin, HIGH);

  value = EEPROM.read(address);
  if (value == 1) {
    value = 0;
    EEPROM.put(address, value);
    while (1){
      Serial.println("Disabled");
      delay(200);
    }
  } else {
    value = 1;
    EEPROM.put(address, value);
    Serial.println("Enabled");
  }
}

void loop() {
  if(!digitalRead(knife_pin)){
    if (!knife_triggered) {
      seq++;
      Serial.print(seq);
      Serial.print("(");
      Serial.print(distance[seq]);
      Serial.println(")");
      }
    if (seq == array_length) {seq = 0;}
    knife_triggered = true;

  } else {

    if (knife_triggered) {
      knife_triggered = false;
      delay(1000);
      digitalWrite(twenty_pin, LOW);
      delay(100);
      digitalWrite(twenty_pin, HIGH);
      delay(100);

      int cm = distance[seq]/10 - 2;
      int mm = distance[seq] % 10;

      int i = 0;
      while (i < cm){
        i++;
        digitalWrite(cm_pin, LOW);
        delay(50);
        digitalWrite(cm_pin, HIGH);
        delay(50);
      }

      i = 0;
      while (i < mm){
        i++;
        digitalWrite(mm_pin, LOW);
        delay(50);
        digitalWrite(mm_pin, HIGH);
        delay(50);
      }
    }
  }
}

