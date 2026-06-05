bool blinking  = false;  
bool ledState  = false;  

int buttonState     = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay    = 50;    

unsigned long lastBlinkTime = 0;
unsigned long blinkInterval = 1000;    

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
        blinking = !blinking;          

        if (!blinking) {
          ledState = false;
          digitalWrite(13, LOW);
        }
      }
    }
  }
  lastButtonState = reading;

  if (blinking) {
    if ((millis() - lastBlinkTime) >= blinkInterval) {
      lastBlinkTime = millis();        
      ledState = !ledState;            
      digitalWrite(13, ledState);      
    }
  }
}
