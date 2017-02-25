#include <Joystick.h>


// Create the Joystick
Joystick_ Joystick;

int FlyWheel = 2;
int LEDoutput = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(FlyWheel, INPUT);
  pinMode(LEDoutput, OUTPUT);
  pinMode(A0, INPUT);

  // Initialize Joystick Library
  Joystick.begin();
  Serial.begin(9600);

}
// Last state of the flyWheel
int lastFlyWheelState = 0;


void loop() {
  // put your main code here, to run repeatedly:
  int currentFlyWheelState = !digitalRead(FlyWheel);
  int KnobValue = analogRead(A0);
  Serial.print(KnobValue);
  Serial.print('\n');
  Joystick.setXAxis(KnobValue);
  Joystick.setYAxis(KnobValue);
  Joystick.setZAxis(KnobValue);
  Joystick.setRxAxis(KnobValue);
  
  
  if (currentFlyWheelState != lastFlyWheelState){
    Joystick.setButton(0, currentFlyWheelState);
    lastFlyWheelState = currentFlyWheelState;
    Serial.print("Button Press \n");
    }
    digitalWrite(LEDoutput, currentFlyWheelState); 
    delay(50);
    
    
  }

