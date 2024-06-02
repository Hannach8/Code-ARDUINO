#include<LiquidCrystal.h>

const int rs = 4, en = 5, d4 = 6, d5 = 7, d6 = 8, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int capteurHumidty = A0, capteurlum = A1, nvDeauBas = 0, nvDeauHaut = 1, Pompe = 2, Led = 13, buzzer = 12, vanne = 3;
bool bas, haut;

int humidity, analoghumidity;
int lux, analoglux;

void setup(){
  
 
  pinMode(nvDeauBas, INPUT);
  pinMode(nvDeauHaut, INPUT);
  pinMode(Pompe, OUTPUT);
  pinMode(Led, OUTPUT);
  pinMode(vanne, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.begin(16, 4);
  lcd.setCursor(0, 0);
  lcd.print("EST BM (systeme");
  lcd.setCursor(0, 1);
  lcd.print("d'irrigation");
  lcd.setCursor(0,2);
  lcd.print("automatique)");
  delay(1500);
 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("realiser par :");
  delay(700);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ATIFI mohamed");
  lcd.setCursor(0, 1);
  lcd.print("MARAOUI Ayoub");
  lcd.setCursor(0, 2);
  lcd.print("KHOULANE MOUSSA");
  delay(1000);
  
  }
void loop() {

  bas = digitalRead(nvDeauBas);
  haut = digitalRead(nvDeauHaut);

  analoghumidity = analogRead(capteurHumidty);

  humidity = map(analoghumidity, 1023, 0, 100, 0);

  analoglux = analogRead(capteurlum);

  lux = map(analoglux, 9600, 0, 100, 0);

  if (!haut == HIGH) {
    if (bas == HIGH) {
      digitalWrite(vanne, HIGH);
      tone(buzzer, 3000);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("humidity ");
      lcd.print(humidity);
      lcd.print(" %");
      lcd.setCursor(0, 2);
      lcd.print("niveau bas");
      delay(300);
    }
    else {
      noTone(buzzer);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("humidity ");
      lcd.print(humidity);
      lcd.print(" %");
      lcd.setCursor(0, 2);
      lcd.print("niveau moyen :");
      delay(300);
    }
  }
  if (!bas == HIGH) {
    if (haut == HIGH) {
      digitalWrite(vanne, LOW);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("humidity ");
      lcd.print(humidity);
      lcd.print(" %");
      lcd.setCursor(0, 2);
      lcd.print("niveau haut");
      delay(200);
    }
    else {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("humidity ");
      lcd.print(humidity);
      lcd.print(" %");
      lcd.setCursor(0, 2);
      lcd.print("niveau moyen");
      delay(200);
    }
  }

  if (humidity <= 30) {
    if (lux <= 1) {
      digitalWrite(Pompe, HIGH);
      digitalWrite(Led, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Pompe: arroser");
      lcd.setCursor(0, 1);
      lcd.print("humidity ");
      lcd.print(humidity);
      lcd.print(" %");
      delay(200);
    }
  }
  if (humidity > 30)   {
      digitalWrite(Pompe, LOW);
      digitalWrite(Led, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Pompe: arret");
      lcd.setCursor(0, 1);
      lcd.print("humidity ");
      lcd.print(humidity);
      lcd.print(" %");
  }
  delay(300);

}
