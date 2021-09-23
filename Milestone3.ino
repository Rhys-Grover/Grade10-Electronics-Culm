  
#define echoPin 31
#define trigPin 33
#define Speaker 11
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27,20,4);
char keypressed;
const byte ROWS = 4; 
const byte COLS = 4; 
String password="1234";
String tempPassword;
String tempPassword2;
boolean alarmon = false;
boolean alarmprimed = false;
boolean menumenu = true;
boolean passChangeMode = false;
boolean passChanged = false;
int k=8;

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

if(alarmprimed == true)
{
  if(distance < 50)
  {
  alarmon = true;
  tone(Speaker, 1000);
  enterPassword();
  alarmprimed = false;
  }
}


if(menumenu == true){
  lcd.setCursor(0,0);
  lcd.print("A - To Prime Alarm");
  lcd.setCursor(0,2);
  lcd.print("B - To Set Code");
  keypressed = myKeypad.getKey();
 
        if (keypressed == 'A') {
          int i = 9;
          menumenu = false;
          lcd.clear();
          lcd.setCursor(5,1);
          lcd.print("!Priming!");
          lcd.setCursor(9,2);
          lcd.print("10");
          delay(1000);
          lcd.clear();
           lcd.setCursor(5,1);
          lcd.print("!Priming!");
          while(i != 0){
            lcd.setCursor(9,2);
            lcd.print(i);
            delay(1000);
            i--;
          if(i == 1){
            alarmprimed = true;
            lcd.clear();
            lcd.setCursor(6,1);
            lcd.print("!PRIMED!");
            lcd.setCursor(6,2);
            lcd.print("!PRIMED!");
          }
         }
        }
      if (keypressed =='B') {
      lcd.clear();
      int h=1;
      tone(Speaker, 2000, 100);
      tempPassword = "";
      lcd.setCursor(0,0);
      lcd.print("Current Password");
      lcd.setCursor(0,1);
      lcd.print(">");
      passChangeMode = true;
      passChanged = true;   
      while(passChanged == true) {      
      keypressed = myKeypad.getKey();
      if (keypressed != NO_KEY){
        if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
            keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
            keypressed == '8' || keypressed == '9' ) {
         tempPassword += keypressed;
         lcd.setCursor(h,1);
         lcd.print("*");
         h++;
         tone(Speaker, 2000, 100);
        }
      }
      if (h > 5 || keypressed == '#') {
        tempPassword = "";
        h=1;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Current Password");
        lcd.setCursor(0,1);
        lcd.print(">"); 
      }
      if ( keypressed == '*') {
        h=1;
        tone(Speaker, 2000, 100);
        if (password == tempPassword) {
          tempPassword="";
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Set New Password");
          lcd.setCursor(0,1);
          lcd.print(">");
          while(passChangeMode == true) {
            keypressed = myKeypad.getKey();
            if (keypressed != NO_KEY){
              if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
                  keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
                  keypressed == '8' || keypressed == '9' ) {
                tempPassword += keypressed;
                lcd.setCursor(h,1);
                lcd.print("*");
                h++;
                tone(Speaker, 2000, 100);
              }
            }
            if (h > 5 || keypressed == '#') {
              tempPassword = "";
              h=1;
              tone(Speaker, 2000, 100);
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Set New Password");
              lcd.setCursor(0,1);
              lcd.print(">");
            }
            if ( keypressed == '*') {
              passChangeMode = false;
              passChanged = false;
              h=1;
              tone(Speaker, 2000, 100);
              password = tempPassword;
              lcd.clear();
            }            
          }
        }
         
          
         
    }
}

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


long msToCm(long microseconds) {
return microseconds / 29 / 2;
}

void enterPassword() {
  k=8;
  tempPassword2 = "";
  alarmon = true;
  tone(Speaker, 1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("**ALARM** **ALARM**");
  lcd.setCursor(3, 1);
  lcd.print("ENTER THE CODE");
  lcd.setCursor(0,3);
  lcd.print("**ALARM** **ALARM**");
  lcd.setCursor(3,2);
  lcd.print("Pass>");
      while(alarmprimed) {
      keypressed = myKeypad.getKey();
      if (keypressed != NO_KEY){
        if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
            keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
            keypressed == '8' || keypressed == '9' ) {
          tempPassword2 += keypressed;
          lcd.setCursor(k,2);
          lcd.print("*");
          k++;
        }
      }
      if (k > 12 || keypressed == '#') {
        tempPassword2 = "";
        k=8;
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
        if ( tempPassword2 == password ) {
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print(" !CORRECT!!CORRECT!");
          lcd.setCursor(2,2);
          lcd.print("SYSTEMS DISABLED");
          alarmon = false;
          alarmprimed = false;
          noTone(Speaker);
          delay(3000);
          menumenu = true;
          lcd.clear();
        }
        else if (tempPassword2 != password) {
          lcd.setCursor(3,2);
          lcd.print("Wrong! Try Again");
          delay(1000);
          tempPassword2 = "";
          k=8;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("**ALARM** **ALARM**");
          lcd.setCursor(3, 1);
          lcd.print("ENTER THE CODE");
          lcd.setCursor(0,3);
          lcd.print("**ALARM** **ALARM**");
          lcd.setCursor(3,2);
          lcd.print("Pass>");
          lcd.setCursor(8,2);
        }
      }    
      }
}
