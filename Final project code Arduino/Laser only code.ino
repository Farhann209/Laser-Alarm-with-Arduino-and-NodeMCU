// Define the pin used for the laser module
const int laserPin = 7;

void setup () {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
  
  // Set the pin mode for the laser module
  pinMode(laserPin, OUTPUT);
  
  // Turn on the laser module
  digitalWrite(laserPin, HIGH);
}

void loop() {
  // Do nothing
}