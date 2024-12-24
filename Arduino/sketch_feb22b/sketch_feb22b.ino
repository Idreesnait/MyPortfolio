#include <SoftwareSerial.h>

// Define pins for the software serial connection to the DY-HV20T
const int rxPin = 10; // RX pin not used in this setup but required for SoftwareSerial initialization
const int txPin = 11; // Connected to the DY-HV20T's RX through a 1kΩ resistor

// Initialize software serial for DY-HV20T communication
SoftwareSerial mySerial(rxPin, txPin);

// HC-SR04 Pin Configuration
const int trigPin = 2; // Trigger pin connected to the HC-SR04
const int echoPin = 3; // Echo pin connected to the HC-SR04

void setup() {
  mySerial.begin(9600); // Start serial communication with the DY-HV20T at 9600 baud rate
  
  // Configure HC-SR04 pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  long duration, distance;

  // Clear the trigPin by setting it LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Trigger the ultrasonic pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pulse
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Calculate the distance

  // If an object is detected within 20 cm, play the audio file
  if (distance > 0 && distance < 20) {
    playAudioFile(1); // Adjust the file number based on your audio file naming convention
    // Delay to prevent continuous playback, adjust based on your audio file length
    delay(5000); 
  }

  // Short delay before the next measurement cycle
  delay(100);
}

void playAudioFile(int fileNumber) {
  // Replace these commands with the actual command sequence for your DY-HV20T module
  mySerial.write(0xAA); // Example: Start byte for command sequence (hypothetical)
  mySerial.write(0x07); // Example: Command byte to play a file (hypothetical)
  mySerial.write(fileNumber); // Specify the file number to play
  mySerial.write((byte)0); // Example: Additional data bytes if needed
  mySerial.write(0xFF); // Example: Stop byte for command sequence (hypothetical)
}