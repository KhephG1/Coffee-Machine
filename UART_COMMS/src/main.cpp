#include <Arduino.h>
 
#define BUF_SIZE 20
//device sends on RTS and listens on CTS
String receive_buffer = "";
//global status variable to indicate if the arduino is ready to read more bytes into its buffer
bool READY = 1;
uint num_bytes = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);  
}

void loop() {
  // put your main code here, to run repeatedly:
    Serial1.write("Hi");
    Serial1.flush();
    while (Serial1.available() > 0) {
    char receivedChar = Serial1.read();
    if (receivedChar == '\0') {
      Serial.println(receive_buffer);  // Print the received message in the Serial monitor
      receive_buffer = "";  // Reset the received message
    } else {
      receive_buffer += receivedChar;  // Append characters to the received message
    }
    }
    delay(5000);

    
}

