const int photoCellPin = A1;
const int ledPin = 9;

int brightness = 0;
const int roomBrightness = 800; // Adjust this value according to your room's brightness

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(photoCellPin);
  
  if (sensorValue > roomBrightness) {
    brightness = 0; // LED off when room brightness is detected
  } else {
    brightness = map(sensorValue, 0, roomBrightness, 255, 0); // Invert mapping for brightness
  }
  
  Serial.print("Brightness: ");
  Serial.print(brightness);
  Serial.print(", Sensor Value: ");
  Serial.println(sensorValue);
  
  analogWrite(ledPin, brightness);
  
  delay(100);
}