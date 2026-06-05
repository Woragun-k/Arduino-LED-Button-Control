bool state = false;     // Current LED state (on/off)
int buttonState     = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay    = 50; // Debounce delay in milliseconds

void setup() {
  pinMode(13, OUTPUT);       // LED as output
  pinMode(2,  INPUT_PULLUP); // Button with internal pull-up
                             // No external resistor needed
}

void loop() {
  int reading = digitalRead(2); // Read current button state

  // If button changed → restart debounce timer
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // Wait until signal stable for 50ms
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      // INPUT_PULLUP: button pressed = LOW
      if (buttonState == LOW) {
        state = !state;          // Toggle state
        digitalWrite(13, state); // Update LED
      }
    }
  }

  lastButtonState = reading; // Save last state
}
