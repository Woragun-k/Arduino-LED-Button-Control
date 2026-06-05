bool state = false;     
int buttonState     = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay    = 50; 

void setup() {
  pinMode(13, OUTPUT);        
  pinMode(2,  INPUT_PULLUP);  
}

void loop() {
  int reading = digitalRead(2);  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        state = !state;           
        digitalWrite(13, state);  
      }
    }
  }

  lastButtonState = reading;  
}
