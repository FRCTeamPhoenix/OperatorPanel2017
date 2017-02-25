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

volatile int lastFlyWheelState = 0;
volatile int lastLEDoutputState = 0;
volatile int lastIndexerState = 0;
volatile int lastShooterState = 0;
volatile int lastClimberUpState = 0;
volatile int lastClimberDownState = 0;
volatile int lastAutonomousStartState = 0;
volatile int lastAutonomousStopState = 0;
volatile int lastPotXState = 0;
volatile int lastPotYState = 0;
volatile int lastFlyWheelSpeedState = 0;
volatile int lastTurretState = 0;

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
  readButtonState(Indexer, 2, lastIndexerState);
  readButtonState(Shooter, 3, lastShooterState);
  readButtonState(ClimberUp, 4, lastClimberUpState);
  readButtonState(ClimberDown, 5, lastClimberDownState);
  readButtonState(AutonomousStart, 6, lastAutonomousStartState);
  readButtonState(AutonomousStop, 7, lastAutonomousStopState);
  readPotState(PotX, 1, lastPotXState);
  readPotState(PotY, 2, lastPotYState);
  readPotState(FlyWheelSpeed, 3, lastFlyWheelSpeedState);
  readPotState(Turret, 4, lastTurretState);
  
    
  }

 void readButtonState(int pin, int button, volatile int &lastState) {
  int currentState = digitalRead(pin);
  if (currentState != lastState){
    Joystick.setButton(button, currentState);
    lastState = currentState;
    Serial.print("Button Press "); 
    Serial.print(button); 
    Serial.print(" ");
    Serial.print(currentState); 
    Serial.print('\n');
    }
    
  }
  void readPotState(int pin, int axis, volatile int &lastState){
    int currentValue = analogRead(pin);
    
    
  if(currentValue != lastState){
    if(axis == 1){
       Joystick.setXAxis(currentValue);
      }
    else if(axis == 2){
       Joystick.setYAxis(currentValue);
      }
    else if(axis == 3){
       Joystick.setZAxis(currentValue);
      }
    else if(axis == 4){
       Joystick.setRxAxis(currentValue);
      }
    
    Serial.print("Pot ");
    Serial.print(axis);
    Serial.print(" ");
    Serial.print(currentValue);
    Serial.print(" ");
    Serial.print(lastState);
    Serial.print('\n');
    lastState = currentValue;
   }    
 }

