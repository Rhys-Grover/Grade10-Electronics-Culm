
#define echoPin 10
#define trigPin 9
#define Speaker 7

void setup() {
pinMode(Speaker, OUTPUT);
Serial.begin(9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
}

void loop() {
int distance = msToCm( getDistance() );
Serial.print(distance);
Serial.println(" cm");
Serial.println("-----");
if(distance < 90){
  tone(Speaker, 1000);
  delay(200);
  tone(Speaker, 700);
  delay(200);
}
else
{
  noTone(Speaker);
  delay(400);
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
