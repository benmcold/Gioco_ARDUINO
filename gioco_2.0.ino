#include <LiquidCrystal.h>

LiquidCrystal lcd( 12, 11, 5, 4, 3, 2);//definisci i pin del display

#define JOYSTICK_X A0 //definisci i pin del joystick
#define JOYSTICK_Y A1

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




 void setup() {
   lcd.begin(16, 2);//inizializza il display
   Serial.begin(9600);//inizializza il seriale
   //crea i personaggi
   lcd.createChar(0, ostacolo);
   lcd.createChar(1, personaggio);
   //randomSeed(F(__DATE__));
   randomSeed(punteggio);
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
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("GAME OVER");
    delay(10000);
    lcd.noDisplay();
    start = 0;
    lcd.display();
    lcd.setCursor(0, 0);
    lcd.print("PREMI PER");
    lcd.setCursor(0, 1);
    lcd.print("GIOCARE");
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
     if(analogRead(x) < 400){  
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
     
                  }else if (analogRead(y) < 700) {
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

