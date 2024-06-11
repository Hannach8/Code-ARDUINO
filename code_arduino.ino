#include <LiquidCrystal.h>

const int rs = 4, en = 5, d4 = 6, d5 = 7, d6 = 8, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int capteurHumidty = A0, capteurlum = A1, capteurNiveauEau = 10;
const int Pompe = 2, LedRed = 13, buzzer = 12, vanne = 3, LedBleue = 11;

int humidity, analoghumidity;
int lux, analoglux;
bool niveauEau;

void setup() {
  Serial.begin(9600);
  pinMode(capteurNiveauEau, INPUT);
  pinMode(Pompe, OUTPUT);
  pinMode(LedRed, OUTPUT);
  pinMode(vanne, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(LedBleue, OUTPUT);

  lcd.begin(16, 2);
  
  // Afficher les crédits
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Realise par :");
  delay(1500);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MARAOUI Ibrahim");
  delay(1500);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("HANNACH Hamza");
  delay(1500);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LAMRABET Marouane");
  delay(1500);
  
  lcd.clear();
}

void loop() {
  // Lire les valeurs du capteur d'humidité et vérifier les lectures
  analoghumidity = analogRead(capteurHumidty);
  Serial.print("Valeur du capteur d'humidite: ");
  Serial.println(analoghumidity);

  // Mapper les valeurs lues en pourcentage d'humidité
  humidity = map(analoghumidity, 1023, 0, 100, 0);

  // Lire les valeurs du capteur de lumière et les mapper
  analoglux = analogRead(capteurlum);
  lux = map(analoglux, 9600, 0, 100, 0);

  // Lire l'état du capteur de niveau d'eau
  niveauEau = digitalRead(capteurNiveauEau);

  // Logique de contrôle pour l'humidité et la lumière
  if (humidity >= 30 && lux <= 1) {
    digitalWrite(Pompe, HIGH);
    digitalWrite(LedRed, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pompe: arroser");
    lcd.setCursor(0, 1);
    lcd.print("humidite ");
    lcd.print(humidity);
    lcd.print(" %");
    delay(2000); // Augmenter le délai ici pour une durée d'affichage plus longue
  } else {
    digitalWrite(Pompe, LOW);
    digitalWrite(LedRed, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pompe: arret");
    lcd.setCursor(0, 1);
    lcd.print("humidite ");
    lcd.print(humidity);
    lcd.print(" %");
    delay(2000); // Augmenter le délai ici pour une durée d'affichage plus longue
  }

  // Logique de contrôle pour le niveau d'eau
  if (!niveauEau) { // Niveau d'eau bas
    digitalWrite(vanne, HIGH);
    digitalWrite(LedBleue, HIGH);
    tone(buzzer, 3000);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("niveau bas");
    delay(3000); // Augmenter le délai ici pour une durée d'affichage plus longue
  } else { // Niveau d'eau haut
    digitalWrite(vanne, LOW);
    digitalWrite(LedBleue, LOW);
    noTone(buzzer);
  }

  // Afficher les valeurs sur l'écran LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("humidite ");
  lcd.print(humidity);
  lcd.print(" %");
  lcd.setCursor(0, 1);
  lcd.print("luminosite ");
  lcd.print(lux);
  lcd.print(" %");
  delay(3000); // Augmenter le délai ici pour une durée d'affichage plus longue
}
