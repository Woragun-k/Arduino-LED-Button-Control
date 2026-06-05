const int pinLED     = 13;
const int pinButton1 = 2;  // Start/stop blinking
const int pinButton2 = 4;  // Switch frequency

bool blinking = false; // Whether LED is currently blinking
bool ledState = false; // Current LED state (on/off)
bool slowMode = false; // false = 1s interval | true = 2s interval

// --- Debounce variables for Button 1 ---
int buttonState1     = HIGH;
int lastButtonState1 = HIGH;
unsigned long lastDebounceTime1 = 0;

// --- Debounce variables for Button 2 ---
int buttonState2     = HIGH;
int lastButtonState2 = HIGH;
unsigned long lastDebounceTime2 = 0;

unsigned long debounceDelay = 50; // Debounce delay in milliseconds
unsigned long lastBlinkTime = 0;

void setup() {
  pinMode(pinLED,     OUTPUT);
  pinMode(pinButton1, INPUT_PULLUP); // Button 1 with internal pull-up
  pinMode(pinButton2, INPUT_PULLUP); // Button 2 with internal pull-up
}

void loop() {

  // --- Button 1: Start/stop blinking ---
  int reading1 = digitalRead(pinButton1);

  if (reading1 != lastButtonState1) {
    lastDebounceTime1 = millis(); // Restart debounce timer
  }
  if ((millis() - lastDebounceTime1) > debounceDelay) {
    if (reading1 != buttonState1) {
      buttonState1 = reading1;

      if (buttonState1 == LOW) {
        blinking = !blinking;        // Toggle blinking on/off
        if (!blinking) {
          ledState = false;
          digitalWrite(pinLED, LOW); // Turn LED off immediately
        }
      }
    }
  }
  lastButtonState1 = reading1; // Save last state

  // --- Button 2: Switch frequency ---
  int reading2 = digitalRead(pinButton2);

  if (reading2 != lastButtonState2) {
    lastDebounceTime2 = millis(); // Restart debounce timer
  }
  if ((millis() - lastDebounceTime2) > debounceDelay) {
    if (reading2 != buttonState2) {
      buttonState2 = reading2;

      if (buttonState2 == LOW) {
        slowMode = !slowMode; // Toggle: 1s ↔ 2s
      }
    }
  }
  lastButtonState2 = reading2; // Save last state

  // --- Blink interval based on mode ---
  // Ternary operator: slowMode true → 2000ms | false → 1000ms
  unsigned long blinkInterval = slowMode ? 2000 : 1000;

  // --- Blink logic without delay() ---
  // millis() used so buttons can respond at any time
  if (blinking) {
    if ((millis() - lastBlinkTime) >= blinkInterval) {
      lastBlinkTime = millis();       // Reset timer
      ledState = !ledState;           // Toggle LED state
      digitalWrite(pinLED, ledState); // Update LED
    }
  }
}
