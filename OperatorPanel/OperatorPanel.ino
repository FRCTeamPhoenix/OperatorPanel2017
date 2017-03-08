#include <Joystick.h>
#include <SoftwareSerial.h>

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
  


int FlywheelAuto = 3;
int FlywheelManual = 2;
int Feeder = 4;
int IndexerForward= 6;
int IndexerBackward= 5;
int Climber = 8;
int SpareA = 7;
int SpareB = 9;
int AutonomousStart = 10;
int AutonomousStop = 11;

//
int FlywheelTrim = A0;
int TurretTrim = A1;
int TurretRotation = A5;
int FlywheelSpeed = A2;

// TODO: Need to add Serial 7-segment Rx pin
const int softwareTx = 12;
const int softwareRx = 13;
SoftwareSerial perDis(softwareRx, softwareTx);
char tempString[10]; // Will be used with sprintf to create strings

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
  perDis.begin(9600);

  perDis.write(0x76);  // Clear display command
  perDis.write(0x7A);  // Set brightness command byte
  perDis.write(200);  // brightness data byte

  perDis.print("0000");
  delay(1000);
  perDis.print("   -");
  delay(250);
  perDis.print("  --");
  delay(250);
  perDis.print(" ---");
  delay(250);
  perDis.print("----");
  delay(250);
  perDis.print("--- ");
  delay(250);
  perDis.print("--  ");
  delay(250);
  perDis.print("-   ");
  delay(250);
  perDis.print("    ");
  delay(250);

  // TODO: Need to add LED output pins
  pinMode(ledFlywheelTrim, OUTPUT);
  pinMode(ledTurretTrim, OUTPUT);
  pinMode(ledTurretRotation, OUTPUT);
 
  
  
  // Future possible interrupt method
  //attachInterrupt(FlyWheel )
  
  // Initialize Joystick Library
  Joystick.begin();

  // Initialize serial for seven-segment display
  // TODO set the pins
  //Serial.begin(9600);

}


void loop() {
  // put your main code here, to run repeatedly:
  
  readButtonState(FlywheelAuto, 5, lastFlywheelAutoState); 
  readButtonState(FlywheelManual, 4, lastFlywheelManualState); 
  readButtonState(Feeder, 1, lastFeederState); 
  readButtonState(IndexerForward, 3, lastIndexerForwardState); 
  readButtonState(IndexerBackward, 6, lastIndexerBackwardState); 
  readButtonState(Climber, 2, lastClimberState); 
  readButtonState(SpareA, 0, lastSpareAState); 
  readButtonState(SpareB, 9, lastSpareBState); 
  readButtonState(AutonomousStart, 7, lastAutonomousStartState); 
  readButtonState(AutonomousStop, 8, lastAutonomousStopState); 

  readPotState(FlywheelTrim, 2, lastFlywheelTrimState);
  readPotState(TurretTrim, 1, lastTurretTrimState);
  readPotState(TurretRotation, 3, lastTurretRotationState);
  readPotState(FlywheelSpeed, 4, lastFlywheelSpeedState);

    
  }

 void readButtonState(int pin, int button, volatile int &lastState) {
  int currentState = digitalRead(pin);
  if (currentState != lastState){
    Joystick.setButton(button, currentState);
    lastState = currentState;

    // Debounce for 50 mS
    delay(50);
    
    /*
    Serial.print("Button Press "); 
    Serial.print(button); 
    Serial.print(" ");
    Serial.print(currentState); 
    Serial.print('\n');
    */
    }
    
  }
  void readPotState(int pin, int axis, volatile int &lastState){
    int currentValue = analogRead(pin);
    
     
  if(currentValue != lastState){
    if(axis == 1){
       Joystick.setXAxis(currentValue);
       if((currentValue > 480) && (currentValue < 560)) {
        digitalWrite(ledTurretTrim, HIGH);
       }
       else {
        digitalWrite(ledTurretTrim, LOW);
       }

 

      }
    else if(axis == 2){
       Joystick.setYAxis(currentValue);
       if((currentValue > 480) && (currentValue < 560)) {
        digitalWrite(ledFlywheelTrim, HIGH);
       }
       else {
        digitalWrite(ledFlywheelTrim, LOW);
       }
    

      }
    else if(axis == 3){
       Joystick.setZAxis(currentValue);
       if((currentValue > 480) && (currentValue <560)) {
        analogWrite(ledTurretRotation, 255);
       }
       else{
        analogWrite(ledTurretRotation, 0);
       }
    
        
      }
    else if(axis == 4){

       int potValue = 1023 - currentValue;
       
       Joystick.setThrottle(potValue);
       
       int scaledValue = (int) ((float) potValue/10.23);
       sprintf(tempString, "%3d ", (int) scaledValue);
       perDis.print(tempString);
       
       delay(100);
      }

      /* 
      // For debugging
      Serial.print("Pot ");
      Serial.print(axis);
      Serial.print(" ");
      Serial.print(currentValue);
      Serial.print(" ");
      Serial.print(lastState);
      Serial.print('\n');
      */
    
    lastState = currentValue;
   }    
 }

