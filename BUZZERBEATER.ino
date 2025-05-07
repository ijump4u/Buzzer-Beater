// BUZZER BEATER!!
void setup() {
  pinMode(12, OUTPUT); // Green LED
  pinMode(11, OUTPUT); // Red LED
  pinMode(7, INPUT_PULLUP); // Button (active LOW)
  pinMode(10, OUTPUT); // Buzzer or speaker

  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  Serial.begin(9600); // Start serial monitor for debug
}

void loop() {
  // Wait for player to press button to start the game
  if (digitalRead(7) == LOW) {
    startMelody(); // Startup sound + LED sequence

    delay(1000); // Brief pause before game starts
    int waitTime = random(5000, 15000); // Random wait time
    if (!gameStart(waitTime)) return; // Ends if player cheats

    unsigned long reactionTime = goGoGo(); // Measure reaction time

    // Show result based on timing
    if (reactionTime <= 500) {
      winTune();
    } else {
      loseTune();
    }

    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    noTone(10);

    while (true); // End game after one run
  }

  delay(10); // Short delay for stability
}

void startMelody() {
  // Simple startup light + sound sequence
  tone(10, 262, 150); // C4
  digitalWrite(11, HIGH);
  delay(200);

  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  tone(10, 330, 150); // E4
  delay(200);

  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  tone(10, 392, 150); // G4
  delay(200);

  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  tone(10, 523, 300); // C5
  delay(350);

  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  noTone(10);
}

bool gameStart(int durationMs) {
  // Wait period before reaction test begins
  unsigned long startTime = millis();

  while (millis() - startTime < durationMs / 2) {
    // Check for early press (cheating)
    if (digitalRead(7) == LOW) {
      digitalWrite(11, HIGH); // Red LED on
      cheatLose();
      Serial.println("False start!");
      while (true); // End game immediately
    }

    // Flash LED with tones for suspense
    digitalWrite(12, HIGH);  // Green LED
    tone(10, 800, 50);
    delay(150);

    digitalWrite(12, LOW);
    tone(10, 600, 50);
    delay(300);
  }

  noTone(10);
  return true; // Ready for reaction test
}

unsigned long goGoGo() {
  // Signal player to press button now!
  tone(10, 1000, 500);
  digitalWrite(11, HIGH); // Red LED = GO
  delay(500);
  noTone(10);

  unsigned long goTime = millis();

  // Wait for user to press the button
  while (digitalRead(7) == HIGH);

  unsigned long pressTime = millis();
  unsigned long reactionTime = pressTime - goTime;

  Serial.print("Reaction Time: ");
  Serial.print(reactionTime);
  Serial.println(" ms");

  return reactionTime;
}

void winTune() {
  digitalWrite(11, HIGH); // Green LED for win
  digitalWrite(12, LOW);
  tone(10, 523, 150); // C5
  delay(300);
  tone(10, 659, 150); // E5
  delay(300);
  tone(10, 784, 300); // G5
  delay(500);
  noTone(10);
}

void loseTune() {
  digitalWrite(12, HIGH); // Red LED for loss
  digitalWrite(11, LOW);
  tone(10, 392, 300); // G4
  delay(300);
  tone(10, 330, 300); // E4
  delay(300);
  tone(10, 262, 500); // C4
  delay(500);
  noTone(10);
}

void cheatLose() {
  tone(10, 100, 500); // Flat fail tone
  digitalWrite(12, HIGH);
  delay(500);
  digitalWrite(12, LOW);
  tone(10, 100, 500);
  delay(500);
  noTone(10);
  Serial.println("You pressed too early!");
}
