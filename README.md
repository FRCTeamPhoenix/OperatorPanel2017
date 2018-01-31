# OperatorPanel2017

This season had two custom USB controllers for STEAMworks.

1) Arduino controlled custom USB gamepad for the drive station, with a 3D printed enclosure.

2) Some switches built into the driver station for the driver, also interfaced with an Arduino. It used a slightly modified version of the Operator panel code.

Both used an Arduino Leonardo, since it can emulate a USB HID device, such as a keyboard, joystick, mouse. The code used the Arduino joystick library: 

https://github.com/MHeironimus/ArduinoJoystickLibrary
