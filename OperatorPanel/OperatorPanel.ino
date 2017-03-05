#include <Joystick.h>

//Written by Maya Yaakov 2/25/16
//This is for the Operator Control panel used by team 2342 

// Create the Joystick

// Simple initial method
//Joystick_ Joystick;

// Needs to be declared with non-default constructor to set Axes and Gamepad 
// profile in order for the driver station software to see the axes
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_GAMEPAD, 32, 0,
  true, true, true, false, false, false,
  false, true, false, false, false);
  


int FlywheelAuto = 2;
int FlywheelManual = 3;
int Feeder = 4;
int IndexerForward= 5;
int IndexerBackward= 6;
int Climber = 7;
int SpareA = 8;
int SpareB = 9;
int AutonomousStart = 10;
int AutonomousStop = 11;

//
int FlywheelTrim = A0;
int TurretTrim = A1;
int TurretRotation = A5;
int FlywheelSpeed = A2;

// TODO: Need to add Serial 7-segment Rx pin

// TODO: Need to add LED output pins
int ledFlywheelTrim = 0;
int ledTurretTrim = 1;
int ledTurretRotation = A4;


// Global state variables
volatile int lastFlywheelAutoState = 0;
volatile int lastFlywheelManualState = 0;
volatile int lastFeederState = 0;
volatile int lastIndexerForwardState = 0;
volatile int lastIndexerBackwardState = 0;
volatile int lastClimberState = 0;
volatile int lastSpareAState = 0;
volatile int lastSpareBState = 0;
volatile int lastAutonomousStartState = 0;
volatile int lastAutonomousStopState = 0;
volatile int lastFlywheelTrimState = 0;
volatile int lastTurretTrimState = 0;
volatile int lastFlywheelSpeedState = 0;
volatile int lastTurretRotationState = 0;


void setup() {
  // put your setup code here, to run once:

  // Set up switches
  pinMode(FlywheelAuto, INPUT);
  pinMode(FlywheelManual, INPUT);
  pinMode(Feeder, INPUT); //Feeder
  pinMode(IndexerForward, INPUT);
  pinMode(IndexerBackward, INPUT);
  pinMode(Climber, INPUT);
  pinMode(SpareA, INPUT);
  pinMode(SpareB, INPUT);
  pinMode(AutonomousStart, INPUT);
  pinMode(AutonomousStop, INPUT);

  // Set up pots
  pinMode(FlywheelTrim, INPUT);
  pinMode(TurretTrim, INPUT);
  pinMode(TurretRotation, INPUT);
  pinMode(FlywheelSpeed, INPUT);

  // TODO: Need to add Serial 7-segment Rx pin

  // TODO: Need to add LED output pins
  pinMode(ledFlywheelTrim, OUTPUT);
  pinMode(ledTurretTrim, OUTPUT);
  pinMode(ledTurretRotation, OUTPUT);
 
  
  
  // Future possible interrupt method
  //attachInterrupt(FLyWheel )
  
  // Initialize Joystick Library
  Joystick.begin();

  // Initialize serial for seven-segment display
  // TODO set the pins
  Serial.begin(9600);

}


void loop() {
  // put your main code here, to run repeatedly:
  
  readButtonState(FlywheelAuto, 1, lastFlywheelAutoState); 
  readButtonState(FlywheelManual, 2, lastFlywheelManualState); 
  readButtonState(Feeder, 3, lastFeederState); 
  readButtonState(IndexerForward, 4, lastIndexerForwardState); 
  readButtonState(IndexerBackward, 5, lastIndexerBackwardState); 
  readButtonState(Climber, 6, lastClimberState); 
  readButtonState(SpareA, 7, lastSpareAState); 
  readButtonState(SpareB, 8, lastSpareBState); 
  readButtonState(AutonomousStart, 9, lastAutonomousStartState); 
  readButtonState(AutonomousStop, 10, lastAutonomousStopState); 

  readPotState(FlywheelTrim, 1, lastFlywheelTrimState);
  readPotState(TurretTrim, 2, lastTurretTrimState);
  readPotState(TurretRotation, 3, lastTurretRotationState);
  readPotState(FlywheelSpeed, 4, lastFlywheelSpeedState);

    
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
    
  //TODO: Add LED output

  //TODO: Add percent output
    
  if(currentValue != lastState){
    if(axis == 1){
       Joystick.setXAxis(currentValue);
       if((currentValue > 480) && (currentValue < 560)) {
        digitalWrite(ledFlywheelTrim, HIGH);
       }
       else {
        digitalWrite(ledFlywheelTrim, LOW);
       }

        // Enable for debugging
        /*
        Serial.print("Pot ");
        Serial.print(axis);
        Serial.print(" ");
        Serial.print(currentValue);
        Serial.print(" ");
        Serial.print(lastState);
        Serial.print('\n');
        */
        

      }
    else if(axis == 2){
       Joystick.setYAxis(currentValue);
       if((currentValue > 480) && (currentValue < 560)) {
        digitalWrite(ledTurretTrim, HIGH);
       }
       else {
        digitalWrite(ledTurretTrim, LOW);
       }
       /*
       if((currentValue > 480) && (currentValue <560)) {
        analogWrite(ledTurretRotation, 255);
       }
       else{
        analogWrite(ledTurretRotation, 0);
       }
       */
              /*
       Serial.print("Pot ");
        Serial.print(axis);
        Serial.print(" ");
        Serial.print(currentValue);
        Serial.print(" ");
        Serial.print(lastState);
        Serial.print('\n');
        */

      }
    else if(axis == 3){
       Joystick.setZAxis(currentValue);
       if((currentValue > 480) && (currentValue <560)) {
        analogWrite(ledTurretRotation, 255);
       }
       else{
        analogWrite(ledTurretRotation, 0);
       }
       
       Serial.print("Pot ");
        Serial.print(axis);
        Serial.print(" ");
        Serial.print(currentValue);
        Serial.print(" ");
        Serial.print(lastState);
        Serial.print('\n');
        
      }
    else if(axis == 4){

       //currentValue = currentValue/1023.0;
       
       Joystick.setThrottle(currentValue);
      }

    
    lastState = currentValue;
   }    
 }

