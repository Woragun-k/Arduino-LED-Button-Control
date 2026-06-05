bool blinking  = false; // Whether LED is currently blinking
bool ledState  = false; // Current LED state (on/off)

int buttonState     = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay    = 50; // Debounce delay in milliseconds

unsigned long lastBlinkTime = 0;
unsigned long blinkInterval = 1000; // Blink interval: 1000ms = 1 second

void setup() {
  pinMode(13, OUTPUT);       // LED as output
  pinMode(2,  INPUT_PULLUP); // Button with internal pull-up
}

void loop() {

  // --- Read button with debouncing ---
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
        blinking = !blinking;      // Toggle blinking on/off

        // If stopped → turn LED off immediately
        if (!blinking) {
          ledState = false;
          digitalWrite(13, LOW);
        }
      }
    }
  }

  lastButtonState = reading; // Save last state

  // --- Blink logic without delay() ---
  // millis() used so button can respond at any time
  if (blinking) {
    if ((millis() - lastBlinkTime) >= blinkInterval) {
      lastBlinkTime = millis();  // Reset timer
      ledState = !ledState;      // Toggle LED state
      digitalWrite(13, ledState); // Update LED
    }
  }
}
