#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);

const int Aman = A0;
const int Waspada = A1;
const int Siaga = A2;
const int Bahaya = A3;
int s1 = 0; int s2 = 0; int s3 = 0; int s4 = 0; //sensor level

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(3, 0);
  lcd.print("Kondisi");
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(2, OUTPUT);
}

void loop() { 
int volt = analogRead(A0||A1||A2||A3);
float nilai = volt * (5.0/1023.0);
s1 = analogRead(A0);
s2 = analogRead(A1);
s3 = analogRead(A2);
s4 = analogRead(A3);
if(s1 >= 200 && s2 <=5 && s3 <=5 && s4 <=5){
    digitalWrite(3, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    lcd.setCursor(2, 1);
    lcd.print("--Aman--");
    Serial.print("--Level Aman--");
    }
    
if(s1 >= 150 && s2 >= 150 && s3 <=5 && s4 <=5){
    digitalWrite(4, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    lcd.setCursor(2, 1);
    lcd.print("--Waspada--");
    Serial.print("--Level Waspada--");
}
if(s1 >= 120 && s2 >= 120 && s3 >= 120 && s4 <=5 ){
    digitalWrite(5, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(6, LOW);
    lcd.setCursor(2, 1);
    lcd.print("--Siaga--");
    Serial.print("--Level Siaga--");
}
if(s1 >= 80 && s2 >= 80 && s3 >= 80 && s4 >=80 ){
    digitalWrite(6, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    digitalWrite(5, LOW);
    lcd.setCursor(2, 1);
    lcd.print("--Bahaya--");
    Serial.print("--Level Bahaya--");
}
if(s1 <=5 && s2 <=5 && s3 <=5 && s4 <=5){
    digitalWrite(6, LOW);
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    digitalWrite(5, LOW);
    lcd.setCursor(2, 1);
    lcd.print("---------");
    Serial.print("--System On--");
}
Serial.println(volt);
delay(100); }

/*if((s1 || s2 || s3 || s4  >= 0)){
    digitalWrite(6, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    digitalWrite(3, LOW);
    digitalWrite(5, LOW);
    lcd.setCursor(0, 1);
    lcd.print("--Eror--");
  }*/

