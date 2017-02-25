#include <Joystick.h>


// Create the Joystick
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_GAMEPAD, 32, 0,
  true, true, true, false, false, false,
  false, true, false, false, false);
  
  //Joystick_ Joystick;

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
  pinMode(Shooter, INPUT); //Feeder
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
  readButtonState(FlyWheel, 1, lastFlyWheelState); // now using the on-off-on switch // Joy 6
  readButtonState(Indexer, 2, lastIndexerState); // Joy 4
  readButtonState(Shooter, 3, lastShooterState); // Joy 2 (Loader)
  readButtonState(ClimberUp, 4, lastClimberUpState); // Joy 6 // now will be the 4th switch - Joy 3
  readButtonState(ClimberDown, 5, lastClimberDownState); // Joy 5 // No longer being used
  readButtonState(AutonomousStart, 6, lastAutonomousStartState); // Joy 8
  readButtonState(AutonomousStop, 7, lastAutonomousStopState); // Joy 7
  readPotState(PotX, 1, lastPotXState);
  readPotState(PotY, 2, lastPotYState);
  readPotState(FlyWheelSpeed, 4, lastFlyWheelSpeedState);
  readPotState(Turret, 3, lastTurretState);
  
    
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

       //currentValue = currentValue/1023.0;
       
       Joystick.setThrottle(currentValue);
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

