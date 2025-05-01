#include <LiquidCrystal.h>

#define LCD_RS 12   
#define LCD_E  11   
#define LCD_D4  5   
#define LCD_D5  4   
#define LCD_D6  3   
#define LCD_D7  2   
#define LCD_COL 16  
#define LCD_ROW 2   
#define LCD_CONTRAST  6 

int Contrast = 127;

LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
int trigPin = 10;
int echoPin = 9;
int buzzerPin = 13;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  analogWrite(LCD_CONTRAST, Contrast);
  lcd.begin(LCD_COL, LCD_ROW);
  }

float getDistanceUltrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.0343 / 2;
  return distance;
}

void loop() {
 
  float ultrasonicDistance = getDistanceUltrasonic();

  Serial.print("Ultrasonic Distance: ");
  Serial.println(ultrasonicDistance);

  if (ultrasonicDistance < 45)
  {
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);

    lcd.setCursor(0, 0);
    lcd.print("Alert! Obstacle");

    lcd.setCursor(3, 1);
    lcd.print(ultrasonicDistance);

    lcd.setCursor(11, 1);
    lcd.print("cm");

    delay(333);
    lcd.clear();
  }
  else
  {
    lcd.setCursor(3, 0);
    lcd.print("Distance:");

    lcd.setCursor(3, 1);
    lcd.print(ultrasonicDistance);

    lcd.setCursor(11, 1);
    lcd.print("cm");

    delay(333);
    lcd.clear();
  }
}
