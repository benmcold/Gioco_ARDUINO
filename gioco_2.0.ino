#include <LiquidCrystal.h>

LiquidCrystal lcd( 12, 11, 5, 4, 3, 2);//definisci i pin del display

#define JOYSTICK_X A0 //definisci i pin del joystick
#define JOYSTICK_Y A1



#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_F4  349
#define NOTE_C4  262
#define NOTE_E4  330
#define NOTE_D4  294
#define NOTE_B3  247

byte ostacolo [] { //crea l'ostacolo
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

byte personaggio [] = { // crea il personaggio
    B01100,
    B01100,
    B00000,
    B01110,
    B11100,
    B01100,
    B11010,
    B10011,
};


int START_PIN = 6;
int buzzerPin = 0;
//definisci tutte le variabili
int JoystickPositionx;
int JoystickPositiony;
int ObstaclePosition1 = 12;
int ObstaclePosition2 = 12;
int RandomRiga;
String SpazioVuoto = (" ");
int LastRandom1;
int LastRandom2;
int LastRandomPosition;
int punteggio = 0;
int start;
int contatore = 0;




 void setup() {
   lcd.begin(16, 2);//inizializza il display
   Serial.begin(9600);//inizializza il seriale
   //crea i personaggi
   lcd.createChar(0, ostacolo);
   lcd.createChar(1, personaggio);
   randomSeed(F(__TIME__));
  pinMode(buzzerPin, OUTPUT);
   pinMode(START_PIN, INPUT);
    lcd.setCursor(0, 0);
    lcd.print("PREMI PER");
    lcd.setCursor(0, 1);
    lcd.print("GIOCARE");
  }

 void loop() {
   if(digitalRead(START_PIN) == HIGH){
     start = 1;
     lcd.clear();
   }

   if(start == 1){
   lcd.setCursor(14, 0);
  lcd.print("PT");
  Movimento_ostacolo();
  salta();
  Destra_sinistra();
  ContaPunti();
}

  if(((ObstaclePosition1 == JoystickPositionx) && (LastRandom1 == JoystickPositiony)) 
        || ((ObstaclePosition2 == JoystickPositionx) && (LastRandom2 == JoystickPositiony))){
          if(contatore == 0){
           playGameOverSound();
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("GAME OVER");
    delay(8000);
    lcd.clear();
    contatore = 1;
   }

    start = 0;
    lcd.setCursor(0, 0);
    lcd.print("PREMI PER");
    lcd.setCursor(0, 1);
    lcd.print("GIOCARE");
    delay(2000);
  }
 }






void Movimento_ostacolo(){
    Primo_ostacolo(); 
    Secondo_ostacolo();
}
 
 void Primo_ostacolo(){

     int randomRiga = random(2); //riga
        if(ObstaclePosition1 == 12){
            LastRandom1 = randomRiga;
        } 

  lcd.setCursor(ObstaclePosition1, LastRandom1);
  lcd.write(byte(0));
   lcd.setCursor(ObstaclePosition1 + 2, LastRandom1);
  lcd.print(SpazioVuoto);
  delay(270);
  ObstaclePosition1 = ObstaclePosition1 - 1;
  
  if(ObstaclePosition1 == - 3){
    ObstaclePosition1 = 12;
  }
 }


 void Secondo_ostacolo(){

   int RandomPosition = random(5);
   int randomRiga2 = random(2); //riga
        if(ObstaclePosition2 == 12){
            LastRandom2 = randomRiga2;
            LastRandomPosition = RandomPosition;
        } 
    
      lcd.setCursor(ObstaclePosition2, LastRandom2);
      lcd.write(byte(0));
      lcd.setCursor(ObstaclePosition2 + 2 , LastRandom2);
      lcd.print(SpazioVuoto);
      delay(270);
      ObstaclePosition2 = ObstaclePosition1 - LastRandomPosition;
      if(ObstaclePosition2 == -3){
        ObstaclePosition2 = 12;
      }
 }
 
 
 
void Destra_sinistra(){ 
  int x = analogRead(JOYSTICK_X);// destra = 0, sinistra = 1000
  Serial.println(x);
     if(analogRead(x) < 300){  
          JoystickPositionx = JoystickPositionx + 1;
          delay(200);
          lcd.setCursor(JoystickPositionx, JoystickPositiony);
          lcd.write(byte(1));
          lcd.setCursor(JoystickPositionx - 1, JoystickPositiony);
          lcd.print(SpazioVuoto);
        }
          if(JoystickPositionx > 13){
          JoystickPositionx = 13;
          lcd.setCursor(13, JoystickPositiony);
          lcd.write(byte(1));
        }

    



 if(analogRead(x) > 700){
         JoystickPositionx = JoystickPositionx - 1;
         delay(200);
         lcd.setCursor(JoystickPositionx, JoystickPositiony);
         lcd.write(byte(1));
         lcd.setCursor(JoystickPositionx + 1, JoystickPositiony);
         lcd.print(SpazioVuoto);
              }

        if(JoystickPositionx < 0){
             JoystickPositionx = 0;
             lcd.setCursor(0, JoystickPositiony);
             lcd.write(byte(1));
        }
  


 if(analogRead(x) < 600 && (x) > 400){
        lcd.setCursor(JoystickPositionx, JoystickPositiony);
         lcd.write(byte(1));
  }
}  




void salta(){
   int y = analogRead(JOYSTICK_Y);
     if(analogRead(y) <  400){
                        JoystickPositiony = 0;
                        lcd.setCursor(JoystickPositionx, JoystickPositiony);
                        lcd.write(byte(1));
                        lcd.setCursor(JoystickPositionx , 1);
                        lcd.print(SpazioVuoto);
    
    
     }
     if (analogRead(y) > 600) {
                         JoystickPositiony = 1;
                         lcd.setCursor(JoystickPositionx, JoystickPositiony);
                         lcd.write(byte(1));
                         lcd.setCursor(JoystickPositionx , 0);
                        lcd.print(SpazioVuoto);
     }
}


void ContaPunti (){
  punteggio = punteggio + 1;
  lcd.setCursor(14, 1);
  lcd.print(punteggio);
  if(punteggio == 100){
    lcd.noDisplay();
    lcd.display();
    lcd.setCursor(7, 0);
    lcd.print("HAI VINTO");
  }
}



void playGameOverSound()
{
  tone(buzzerPin, NOTE_G4, 200);   // Suona la nota G4 per 200 millisecondi
  delay(200);              // Pausa di 200 millisecondi
  tone(buzzerPin, NOTE_A4, 200);   // Suona la nota A4 per 200 millisecondi
  delay(200);              // Pausa di 200 millisecondi
  tone(buzzerPin, NOTE_F4, 400);   // Suona la nota F4 per 400 millisecondi
  delay(400);              // Pausa di 400 millisecondi
  tone(buzzerPin, NOTE_C4, 400);   // Suona la nota C4 per 400 millisecondi
  delay(400);              // Pausa di 400 millisecondi
  tone(buzzerPin, NOTE_E4, 300);   // Suona la nota E4 per 300 millisecondi
  delay(300);              // Pausa di 300 millisecondi
  tone(buzzerPin, NOTE_D4, 300);   // Suona la nota D4 per 300 millisecondi
  delay(300);              // Pausa di 300 millisecondi
  tone(buzzerPin, NOTE_B3, 600);   // Suona la nota B3 per 600 millisecondi
  delay(600);              // Pausa di 600 millisecondi
}
