
#define echoPin 13
#define trigPin 12
#define Speaker 11
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27,20,4);
char keypressed;
const byte ROWS = 4; 
const byte COLS = 4; 
String password="1234";
String tempPassword;
boolean alarmon = true;
boolean alarmprimed = true;

char keyMap[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {6, 7, 8, 9}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad myKeypad = Keypad( makeKeymap(keyMap), rowPins, colPins, ROWS, COLS);
 
void setup() {
pinMode(Speaker, OUTPUT);
Serial.begin(9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
lcd.init();
lcd.clear();         
lcd.backlight();

}

void loop() {

int distance = msToCm( getDistance() );
Serial.print(distance);
Serial.println(" cm");
Serial.println("-----");

if(alarmprimed = true)
{
  if(distance < 90)
  {
  Alarmnoise();
  enterPassword();
  alarmprimed = false;
  }
}

}

long getDistance() {
long duration;
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
return duration;
}

long Alarmnoise(){
  tone(Speaker, 1000);
  delay(200);
  tone(Speaker, 700);
  delay(200);
}

long msToCm(long microseconds) {
return microseconds / 29 / 2;
}

void enterPassword() {
  int k=8;
  tempPassword = "";
  alarmon = true;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("**ALARM** **ALARM**");
  lcd.setCursor(3, 1);
  lcd.print("ENTER THE CODE");
  lcd.setCursor(0,3);
  lcd.print("**ALARM** **ALARM**");
  lcd.setCursor(3,2);
  lcd.print("Pass>");
      while(alarmon) {
      keypressed = myKeypad.getKey();
      if (keypressed != NO_KEY){
        if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
            keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
            keypressed == '8' || keypressed == '9' ) {
          tempPassword += keypressed;
          lcd.setCursor(k,2);
          lcd.print("*");
          k++;
        }
      }
      if (k > 12 || keypressed == '#') {
        tempPassword = "";
        k=5;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("**ALARM** **ALARM**");
        lcd.setCursor(3, 1);
        lcd.print("ENTER THE CODE");
        lcd.setCursor(0,3);
        lcd.print("**ALARM** **ALARM**");
        lcd.setCursor(3,2);
        lcd.print("Pass>");
      }
      if ( keypressed == '*') {
        if ( tempPassword == password ) {
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print(" !CORRECT!!CORRECT!");
          lcd.setCursor(2,2);
          lcd.print("SYSTEMS DISABLED");
          alarmon = false;
          alarmprimed = false;
          noTone(Speaker);
        }
        else if (tempPassword != password) {
          lcd.setCursor(3,2);
          lcd.print("Wrong! Try Again");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("**ALARM** **ALARM**");
          lcd.setCursor(3, 1);
          lcd.print("ENTER THE CODE");
          lcd.setCursor(0,3);
          lcd.print("**ALARM** **ALARM**");
          lcd.setCursor(3,2);
          lcd.print("Pass>");
        }
      }    
    }
}
