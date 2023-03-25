// Define the Blynk template ID, template name, and authentication token
#define BLYNK_TEMPLATE_ID "TMPL6mZEnYTKZ"
#define BLYNK_TEMPLATE_NAME "laser sec"
#define BLYNK_AUTH_TOKEN "wmGRQvnv4TDg3OoOG6oqXEC6suAdrjuo"

// Include the ESP8266 WiFi library and the Blynk library
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

const char* ssid = "KH_2.4";  // The SSID of your WiFi network
const char* password = "CLB356930B";  // The password for your WiFi network

// Define the pins used for the LED, buzzer, and LDR
const int ledPin = D1;  // The NodeMCU pin connected to the LED
const int buzzerPin = D2;  // The NodeMCU pin connected to the buzzer
const int ldrPin = A0;  // The analog pin on the NodeMCU connected to the LDR

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
  
  // Connect to WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  // Wait for connection to be established
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");

  // Initialize Blynk with the authentication token and WiFi network credentials
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  
  // Set the pin modes for the LED, buzzer, and LDR
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ldrPin, INPUT);
}

void loop() {
  // Run the Blynk app
  Blynk.run();
  
  // Read the value of the LDR (light dependent resistor)
  int ldrStatus = analogRead(ldrPin);
  
  // If the LDR value is greater than or equal to 600 (it's dark enough to trigger the alarm)
  if (ldrStatus >= 600) {
    // Log the event in the Blynk app
    Blynk.logEvent("laser_alarm");
    
    // Send a notification to the Blynk app
    Blynk.notify("Laser security alarm triggered!");
    
        // Turn on the LED
      digitalWrite(ledPin, HIGH);
      // Activate the alarm by blinking the LED and sounding the buzzer
      for (int i = 0; i < 15; i++) {
      // Turn on the buzzer
      digitalWrite(buzzerPin, HIGH);
      // Wait for 100 milliseconds
      delay(100);
      // Turn off the buzzer
      digitalWrite(buzzerPin, LOW);
      // Wait for 100 milliseconds
      delay(100);
      // Turn on the LED
      digitalWrite(ledPin, HIGH);
      // Wait for 80 milliseconds
      delay(80);
      // Turn off the LED
      digitalWrite(ledPin, LOW);
      // Wait for 80 milliseconds
      delay(80);
      }
      // Turn off the LED
      digitalWrite(ledPin, LOW);
  }
}