
#include <Wire.h>
#include <BH1750.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
BH1750 lightMeter(0x5C);

#define MaxMinute 1

unsigned long start_time, time_now, minute;
unsigned long  time_read;

void time_to_minute()
{
  float minute_float;
  time_read = millis();
  time_now = time_read - start_time;
  minute_float = time_now/1000/60;
  minute = minute_float;
}


void setup() {
  // put your setup code here, to run once:
  pinMode(A3,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(11,INPUT);
  Wire.begin();
  lcd.begin();
  digitalWrite(A3,1);
  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Smart Lamp!");
  lcd.setCursor(0,1);
  lcd.print("INIT SYSTEM...");
  lightMeter.begin();
  delay(1000);
  lcd.clear();
  start_time = millis();
  
}
float lux;
int power_on, get_out;
void loop() {
  // put your main code here, to run repeatedly:
  
   if((power_on == 1)&&(get_out == 0))
   {
   lux = lightMeter.readLightLevel();
   lcd.setCursor(0,0);
   lcd.print("Do Sang:");
   lcd.print(lux);
   lcd.print("      ");
   time_to_minute();
   lcd.setCursor(0,1);
   lcd.print("Con Lai:");
   lcd.print(MaxMinute - minute);
   lcd.print("      ");
   if(digitalRead(11)==1)
   {
    delay(200);
    if(digitalRead(11)==1) power_on=0;
   }
   if(minute >= MaxMinute)
   {
    while((digitalRead(11)==0))
    {
      digitalWrite(12,0); // tat den hoc
      digitalWrite(13,1);
      delay(200);
      digitalWrite(13,0);
      delay(200);
      lcd.setCursor(0,0);
      lcd.print("Ngoi Qua Lau   ");
      lcd.setCursor(0,1);
      lcd.print("Hay Dung Day");
    }
    get_out = 1;
    power_on=0;
   }
   delay(500);
   }
   else if(digitalRead(11)==0) // co nguoi ngoi vao ghe
   {
    delay(200);
    if(digitalRead(11)==0) 
    {
      if(power_on == 0)
      {
        digitalWrite(12,1);
        start_time = millis();
      }
      power_on=1;
      
    }
   }
   else if(digitalRead(11)==1)
   {
    delay(500);
    if(digitalRead(11)==1)
    {
      get_out=0;
      digitalWrite(12,0);
      lcd.setCursor(0,0);
      lcd.print("WAIT...          ");
      lcd.setCursor(0,1);
      lcd.print("                 ");
    }
   }
}
