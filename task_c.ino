const int pinLED     = 13;
const int pinTaster1 = 2;   
const int pinTaster2 = 4;   

bool blinking      = false;  
bool ledState      = false;  
bool slowMode      = false;  

int buttonState1     = HIGH;
int lastButtonState1 = HIGH;
unsigned long lastDebounceTime1 = 0;

int buttonState2     = HIGH;
int lastButtonState2 = HIGH;
unsigned long lastDebounceTime2 = 0;

unsigned long debounceDelay = 50;
unsigned long lastBlinkTime = 0;

void setup() {
  pinMode(pinLED,     OUTPUT);
  pinMode(pinTaster1, INPUT_PULLUP);
  pinMode(pinTaster2, INPUT_PULLUP);
}

void loop() {

  int reading1 = digitalRead(pinTaster1);

  if (reading1 != lastButtonState1) {
    lastDebounceTime1 = millis();
  }
  if ((millis() - lastDebounceTime1) > debounceDelay) {
    if (reading1 != buttonState1) {
      buttonState1 = reading1;
      if (buttonState1 == LOW) {
        blinking = !blinking;        
        if (!blinking) {
          ledState = false;
          digitalWrite(pinLED, LOW); 
        }
      }
    }
  }
  lastButtonState1 = reading1;

  int reading2 = digitalRead(pinTaster2);

  if (reading2 != lastButtonState2) {
    lastDebounceTime2 = millis();
  }
  if ((millis() - lastDebounceTime2) > debounceDelay) {
    if (reading2 != buttonState2) {
      buttonState2 = reading2;
      if (buttonState2 == LOW) {
        slowMode = !slowMode;        
      }
    }
  }
  lastButtonState2 = reading2;

  unsigned long blinkInterval = slowMode ? 2000 : 1000;

  if (blinking) {
    if ((millis() - lastBlinkTime) >= blinkInterval) {
      lastBlinkTime = millis();
      ledState = !ledState;
      digitalWrite(pinLED, ledState);
    }
  }
}