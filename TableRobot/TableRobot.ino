#include <Servo.h>
#include <LiquidCrystal.h>

Servo head;
LiquidCrystal lcd(31,33,35,37,39,41);

const int trigPin = 23;
const int echoPin = 25;
int sensors[3];


int distance(){
  long duration, cm;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  cm = duration/29/2;
  return cm;
}

void motorControl(int input1,int input2,int enable,int speed){
	//Single motor controll function
  if (speed>0) {
    digitalWrite(input1,HIGH);
    digitalWrite(input2, LOW);
  }
  else {
    digitalWrite(input1, LOW);
    digitalWrite(input2, HIGH);
  }
  analogWrite(enable, abs(speed));
}

void calibration(){
	//initialize duration of calibration

	int calibrationTime = 60;
	int startTime = millis();
	int counter;
	//start spinning
	// add spinFunc(); here 

	while (((millis()-startTime)/1000) < calibrationTime){
		sensors[0]+=analogRead(A0);
		sensors[1]+=analogRead(A1);
		sensors[2]+=analogRead(A3);
		sensors[3]+=analogRead(A4);
		++counter;
	}

	for (int i = 0; i < 3; i++) 
		sensors[i]/=counter;


}

void showIRreadings(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(analogRead(A0));
  lcd.setCursor(0,1);
  lcd.print(analogRead(A1));
  lcd.setCursor(0,2);
  lcd.print(analogRead(A3));
  lcd.setCursor(0,3);
  lcd.print(analogRead(A4));
}

void setup(){
  head.attach(A2);
  head.write(85);
  lcd.begin(20,4);
  lcd.clear();

  pinMode(A0, INPUT);
  digitalWrite(A0,HIGH); //pull-up pre !degenerovanie dat 
  pinMode(A1, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);  
}

void loop(){
  showIRreadings();
  lcd.setCursor(13,0);
  lcd.print("cm: ");
  lcd.print(distance());
  lcd.setCursor(10,1);
  lcd.print("servo: ");
  lcd.print(head.read());
  delay(100);
}






