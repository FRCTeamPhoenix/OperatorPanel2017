#include <Joystick.h>


// Create the Joystick
Joystick_ Joystick;

int FlyWheel = 2;
int LEDoutput = 13;
int Indexer = 3;
int Shooter = 4;
int ClimberUp = 5;
int ClimberDown = 6;
int AutonomousStart = 7;
int AutonomousStop = 8;
int PotX = A0;
int PotY = A1;
int FlyWheelSpeed = A2;
int Turret = A3;

volatile int *lastFlyWheelState;

void setup() {
  // put your setup code here, to run once:
  pinMode(FlyWheel, INPUT);
  pinMode(LEDoutput, OUTPUT);
  pinMode(Indexer, INPUT);
  pinMode(Shooter, INPUT);
  pinMode(ClimberUp, INPUT);
  pinMode(ClimberDown, INPUT);
  pinMode(AutonomousStart, INPUT);
  pinMode(AutonomousStop, INPUT);
  pinMode(PotX, INPUT);
  pinMode(PotY, INPUT);
  pinMode(FlyWheelSpeed, INPUT);
  pinMode(Turret, INPUT);
  
  //attachInterrupt(FLyWheel )
  
  // Initialize Joystick Library
  Joystick.begin();
  Serial.begin(9600);

}




void loop() {
  // put your main code here, to run repeatedly:
  readButtonState(FlyWheel, 0, lastFlyWheelState);
  
  int KnobValue = analogRead(A0);
  Serial.print(KnobValue);
  Serial.print('\n');
  Joystick.setXAxis(KnobValue);
  Joystick.setYAxis(KnobValue);
  Joystick.setZAxis(KnobValue);
  Joystick.setRxAxis(KnobValue);
    
  }

 void readButtonState(int pin, int button, int *lastState) {
  int currentState = !digitalRead(pin);
  if (currentState != *lastState){
    Joystick.setButton(button, currentState);
    *lastState = currentState;
    Serial.print("Button Press ");
    Serial.print(button);
    Serial.print(" ");
    Serial.print(currentState);
    Serial.print('\n');
    }
    
  }

