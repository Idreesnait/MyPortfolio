const int photoCellPin = A1;
const int ledPin = 9;

int brightness = 0;
const int minBrightness = 30;
const int maxBrightness = 115; // roombrightness

const int threshold = 10;

void setup() {
  pinMode(photoCellPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(photoCellPin);
  
  if (sensorValue > maxBrightness) {
    brightness = 0; 
  } else {
    brightness = map(sensorValue, minBrightness, maxBrightness, 255, 0); 
    brightness = constrain(brightness,0,255);
  }
  Serial.print("Brightness: ");
  Serial.print(brightness);
  Serial.print(", Sensor Value: ");
  Serial.println(sensorValue);
  
  if(brightness<threshold)
    analogWrite(ledPin,0);
  else
    analogWrite(ledPin, brightness);
  
  delay(100);
}