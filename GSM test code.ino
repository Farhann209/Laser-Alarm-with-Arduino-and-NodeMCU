#include <SoftwareSerial.h>

// Define the pins used for the LED, buzzer, LDR and laser module
const int ledPin = 13;
const int buzzerPin = 12;
const int ldrPin = A0;
const int laserPin = 7;

// Initialize a software serial port to communicate with the SIM900A module
SoftwareSerial gsmSerial(10, 11); // RX, TX

void setup () {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
  
  // Initialize the software serial port for the GSM Shield
  gsmSerial.begin(9600);
  
  // Set the pin modes for the LED, buzzer, LDR and laser module
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ldrPin, INPUT);
  pinMode(laserPin , OUTPUT);
  
  // Turn on the laser module
  digitalWrite(laserPin, HIGH);
}

void loop() {
  // Read the status of the LDR
  int ldrStatus = analogRead(ldrPin);
  
  // If LDR status is above 500 (i.e. it's bright), activate the alarm
  if (ldrStatus >= 500) {
    // Turn on the LED
    digitalWrite(ledPin, HIGH);
    
    // Play the alarm sound and blink the LED
    for (int i = 0; i < 15; i++) {
      // Turn on the buzzer and play a tone at 300Hz
      digitalWrite(buzzerPin, HIGH);
      tone(buzzerPin, 300);
      delay(100);
      
      // Turn off the buzzer and stop the tone
      digitalWrite(buzzerPin, LOW);
      noTone(buzzerPin);
      delay(100);
      
      // Blink the LED on and off
      digitalWrite(ledPin, HIGH);
      delay(80);
      digitalWrite(ledPin, LOW);
      delay(80);
    }
    
    // Turn off the LED
    digitalWrite(ledPin, LOW);

    // Send an SMS notification to the specified number
    gsmSerial.println("AT+CMGF=1"); // set the SMS mode to text
    delay(1000);
    gsmSerial.println("AT+CMGS=\"9841530670\""); // set the destination number
    delay(1000);
    gsmSerial.println("Warning: Burglar alarm has been triggered!"); // set the SMS content
    delay(1000);
    gsmSerial.write((char)26); // send the SMS message
    delay(1000);
  }
}