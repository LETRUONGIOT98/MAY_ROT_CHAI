#include <PCD8544.h>

#define chaymay 12
#define ruamay 11
#define menu 10
#define tang 9
#define giam 8
#include <PCD8544.h>
static PCD8544 lcd;
#include <EEPROM.h>
#include <HC595.h>

const int chipCount = 2; 
const int latchPin = 0; // Pin ST_CP
const int clockPin = 2; // Pin SH_CP
const int dataPin = 1;  // Pin DS


HC595 ledArray(chipCount,latchPin,clockPin,dataPin);
int sochai =0,chaivao,chaira;
long thoigian = 0;
long time,time1;
int i,j,h,old1,old2,val1,val2;
#define IN A4
#define OUT A5
void setup() {
  //Serial.begin(9600);
  pinMode(IN, INPUT_PULLUP);
  pinMode(OUT, INPUT_PULLUP);
  pinMode(giam, INPUT_PULLUP);
  pinMode(tang, INPUT_PULLUP);
  pinMode(menu, INPUT_PULLUP);
  pinMode(ruamay,INPUT_PULLUP);
  pinMode(chaymay,INPUT_PULLUP);
  for (int t = 0 ; t <= 13  ; t++) {
    ledArray.setPin(t, ON);
    delay(1);
  }
  lcd.begin(84, 48);
  ledArray.reset();
  Home();
  sochai = EEPROM.read(0);
  thoigian = EEPROM.read(1);
  thoigian = thoigian * 1000;
}
void hienthi(){
  if(millis() - time1 >= 3000){
  lcd.clear();
  time1=millis();
}
}

void Home(){
   
  lcd.setCursor(5, 0);
  lcd.print("  NHOM 2   " +String(j));
  lcd.setCursor(0, 1);
  lcd.print("SET CHAI: " + String(sochai)+"  ");
  lcd.setCursor(0, 2);
  lcd.print("CHAI VAO: " + String(chaivao)+"  ");
  lcd.setCursor(0, 3);
  lcd.print("CHAI RA: " + String(chaira)+"  ");
  lcd.setCursor(0, 4);
  lcd.print("TIME: " + String(thoigian/1000)+" s ");
}
void Menu1 (){
   
  lcd.setCursor(5, 0);
  lcd.print("NHOM 2");
  lcd.setCursor(0, 1);
  lcd.print("> SET CHAI: " + String(sochai)+"  ");
  lcd.setCursor(0, 2);
  lcd.print("CHAI VAO: " + String(chaivao)+"  ");
  lcd.setCursor(0, 3);
  lcd.print("CHAI RA: " + String(chaira)+"  ");
  lcd.setCursor(0, 4);
  lcd.print("TIME: " + String(thoigian/1000)+" s ");
 

}
void Menu2 (){
   
  lcd.setCursor(5, 0);
  lcd.print("NHOM 2");
  lcd.setCursor(0, 1);
  lcd.print("SET CHAI: " + String(sochai)+"  ");
  lcd.setCursor(0, 2);
  lcd.print("CHAI VAO: " + String(chaivao)+" ");
  lcd.setCursor(0, 3);
  lcd.print("CHAI RA: " + String(chaira)+"  ");
  lcd.setCursor(0, 4);
  lcd.print("> TIME: " + String(thoigian/1000)+" s ");
  
}

void loop() {
val1 = digitalRead(IN);
val2 = digitalRead(OUT);
//Serial.println(digitalRead(giam));
if(val1 != old1){
if(val1 == 0){
  chaivao = chaivao + 1;
}
}

if(val2 != old2){
if(val2 == 0){
  chaira = chaira + 1;
}
}
if(digitalRead(menu) == 0){
  j=0;
  i = i+1;
  i = i%3;
  //Serial.println(i);
  delay(300);
}
if(i == 0){
  Home();
}
if(i == 1){
  Menu1();
  if(digitalRead(tang) == 0){
    sochai = sochai + 1 ;
    sochai = sochai%13;
    for (int t = 0 ; t <= sochai ; t++) {
    ledArray.setPin(t-1, OFF);
    delay(1);
  } EEPROM.write(0,sochai);
    delay(300);
  }
   if(digitalRead(giam) == 0){
    sochai = sochai - 1 ;
     if(sochai <= 0) sochai = 0;
     for (int t = sochai-1 ; t <= sochai ; t++) {
    ledArray.setPin(t+1, ON);
    delay(1);
  } EEPROM.write(0,sochai);
    delay(300);
  }
  
}
if(i == 2){
  Menu2();
  if(digitalRead(tang) == 0){
    thoigian = thoigian + 1000;
    EEPROM.write(1,thoigian/1000);
    delay(300);
  }
  if(digitalRead(giam) == 0){
    thoigian = thoigian - 1000;
    EEPROM.write(1,thoigian/1000);
    delay(300);
  }
}
if(digitalRead(chaymay) == 0){
  time = millis();
  j = !j;
  i=0;
Home();
delay(300);
}
//hienthi();
if(j == 1 && i == 0){
  if(millis() - time <= thoigian){
for (int t = 0 ; t<= sochai ; t++) {
    ledArray.setPin(t-1, OFF);
    delay(1);
  }
}
if(millis() - time >= thoigian){
  for (int t = 0 ; t <= sochai ; t++) {
    ledArray.setPin(t-1, ON);
    delay(1);
  }
}
if(millis() - time >= thoigian * 2){
for (int t = 0 ; t <= sochai ; t++) {
    ledArray.setPin(t-1, ON);
    delay(1);
  }
  time = millis();
}


if(j == 0){
  time = millis();
  for (int t = sochai-1 ; t <= sochai ; t++) {
    ledArray.setPin(t+1, ON);
    delay(1);
  }
}
}
old1 = val1;
old2 = val2;
hienthi();
}
