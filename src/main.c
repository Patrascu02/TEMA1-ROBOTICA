#include <Arduino.h>

#define BLUE1_PIN 10
#define BLUE2_PIN 9
#define BLUE3_PIN 8
#define BLUE4_PIN 7
#define GREEN_RGB_PIN 5
#define BLUE_RGB_PIN 4
#define RED_RGB_PIN 6
#define START_PIN 2
#define STOP_PIN 3

int buttonState = HIGH;          
int lastButtonState = HIGH;      
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50;    

int stopButtonState = HIGH;       
int lastStopButtonState = HIGH;   
unsigned long lastStopDebounceTime = 0;  
unsigned long stopButtonPressTime = 0;  
bool charging = false;            

void startCharging();
bool checkStopButton();
void stopCharging();

void setup() {
  
  pinMode(START_PIN, INPUT_PULLUP);
  pinMode(STOP_PIN, INPUT_PULLUP);
  
  
  pinMode(BLUE1_PIN, OUTPUT);
  pinMode(BLUE2_PIN, OUTPUT);
  pinMode(BLUE3_PIN, OUTPUT);
  pinMode(BLUE4_PIN, OUTPUT);
  pinMode(RED_RGB_PIN, OUTPUT);
  pinMode(GREEN_RGB_PIN, OUTPUT);
  pinMode(BLUE_RGB_PIN, OUTPUT);

  analogWrite(RED_RGB_PIN, 0);    
  analogWrite(GREEN_RGB_PIN, 255);
  analogWrite(BLUE_RGB_PIN, 0);
}

void loop() {
  
  int reading = digitalRead(START_PIN);

  
  if (reading != lastButtonState) {
    lastDebounceTime = millis(); 
  }

  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      
      if (buttonState == LOW) {
        startCharging(); 
      }
    }
  }

  
  int stopReading = digitalRead(STOP_PIN);
  
  
  if (stopReading != lastStopButtonState) {
    lastStopDebounceTime = millis(); 
  }

 
  if ((millis() - lastStopDebounceTime) > debounceDelay) {
    if (stopReading != stopButtonState) {
      stopButtonState = stopReading;

      
      if (stopButtonState == LOW) {
        
        if (stopButtonPressTime == 0) {
          stopButtonPressTime = millis();
        } else if (millis() - stopButtonPressTime >= 1000) {
          
          stopCharging();
        }
      } else {
        
        stopButtonPressTime = 0;
      }
    }
  }

  lastButtonState = reading;      
  lastStopButtonState = stopReading;  
}

void startCharging() {
  charging = true; 

  
  analogWrite(RED_RGB_PIN, 255);    
  analogWrite(GREEN_RGB_PIN, 0);     
  analogWrite(BLUE_RGB_PIN, 0);

  
  for (int j = 0; j < 3; j++) {
    if (checkStopButton()) return;
    for (int i = 0; i < 2; i++) {
      digitalWrite(BLUE1_PIN - j, HIGH);
      delay(750);
      digitalWrite(BLUE1_PIN - j, LOW);
      delay(750);
      digitalWrite(BLUE1_PIN - j, HIGH);
    }
  }

  
  digitalWrite(BLUE1_PIN, LOW);
  digitalWrite(BLUE2_PIN, LOW);
  digitalWrite(BLUE3_PIN, LOW);
  digitalWrite(BLUE4_PIN, LOW);

  
  for (int i = 0; i < 3; i++) {
    
    if (checkStopButton()) return;

    delay(750);
    digitalWrite(BLUE1_PIN, HIGH);
    digitalWrite(BLUE2_PIN, HIGH);
    digitalWrite(BLUE3_PIN, HIGH);
    digitalWrite(BLUE4_PIN, HIGH);
    delay(750);
    digitalWrite(BLUE1_PIN, LOW);
    digitalWrite(BLUE2_PIN, LOW);
    digitalWrite(BLUE3_PIN, LOW);
    digitalWrite(BLUE4_PIN, LOW);
  }

  
  analogWrite(RED_RGB_PIN, 0);    
  analogWrite(GREEN_RGB_PIN, 255); 
  analogWrite(BLUE_RGB_PIN, 0);    
}

bool checkStopButton() {
  
  int stopReading = digitalRead(STOP_PIN);
  if (stopReading == LOW) {
    stopCharging(); 
    return true;   
  }
  return false; 
}

void stopCharging() {
  charging = false;
  digitalWrite(BLUE1_PIN, LOW);
  digitalWrite(BLUE2_PIN, LOW);
  digitalWrite(BLUE3_PIN, LOW);
  digitalWrite(BLUE4_PIN, LOW);

  
  for (int i = 0; i < 3; i++) {
   
    delay(750);
    digitalWrite(BLUE1_PIN, HIGH);
    digitalWrite(BLUE2_PIN, HIGH);
    digitalWrite(BLUE3_PIN, HIGH);
    digitalWrite(BLUE4_PIN, HIGH);
    delay(750);
    digitalWrite(BLUE1_PIN, LOW);
    digitalWrite(BLUE2_PIN, LOW);
    digitalWrite(BLUE3_PIN, LOW);
    digitalWrite(BLUE4_PIN, LOW);
  }

  
  analogWrite(RED_RGB_PIN, 0);    
  analogWrite(GREEN_RGB_PIN, 255); 
  analogWrite(BLUE_RGB_PIN, 0);    
}