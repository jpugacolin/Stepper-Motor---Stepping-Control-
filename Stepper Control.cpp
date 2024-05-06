// ME195B - Stepper Control Testing with Switch Statements
#include <Arduino.h>
#include <SPI.h>
#include <SoftwareSerial.h>

#define STEP_PIN 2  // Define the STEP pin
#define DIR_PIN 3   // Define the DIR pin


void spinMotor() {
  for (int i = 0; i < 200; i++) {  // Spin for 200 steps
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(25);  // Speed control
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(25);  // Speed control
  }
} 

void handleCommand(char cmd) {
  switch (cmd) {
    case 'f': // Move forward
      digitalWrite(DIR_PIN, HIGH); // Set direction forward
      spinMotor();
      break;
    case 'b': // Move backward
      digitalWrite(DIR_PIN, LOW); // Set direction backward
      spinMotor();
      break;
    case 's': // Stop
      noInterrupts(); // Disable interrupts to stop the motor immediately
      break;
    case 'r': // Resume
      interrupts(); // Enable interrupts to resume motor movement
      break;
  }
}



void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  Serial.begin(9600);  // Start serial communication at 9600 baud
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();  // Read the incoming byte from serial port
    handleCommand(command);  // Handle the command
  }
}

