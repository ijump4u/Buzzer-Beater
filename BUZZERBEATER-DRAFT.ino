// C++ code
void setup()
{
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(7, INPUT_PULLUP);
  pinMode(10, OUTPUT);
  
}

void loop()
{
  if (digitalRead(7) == LOW) {
    tone(10, 262, 150); //C4
    digitalWrite(11, HIGH);
    delay(200);
    
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    tone(10, 330, 150); //E4
    delay(200);
    
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    tone(10, 392, 150); //G4
    delay(200);
    
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    tone(10, 523, 300); //C5
    delay(350);
    
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    
    delay(1000);
    
    int waitTime = random(5000, 15000);
  	gameStart(waitTime);
    unsigned long reactionTime = goGoGo();
    
    if(reactionTime <= 500){
      winTune();
    } 
    else {
      loseTune();
    }
    
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    noTone(10);
    
    while(true);
    
  }
  delay(10); // Delay a little bit to improve simulation performance
}

void gameStart(int durationMs){
  unsigned long startTime = millis();
  while(millis() - startTime < durationMs / 2){
    tone(10, 800, 50);
    digitalWrite(12, HIGH);
    delay(150);
    tone(10, 600, 50);
    digitalWrite(12, LOW);
    delay(300);
  }
  noTone(100);
  
}

unsigned long goGoGo(){
  tone(10, 1000, 500);
  digitalWrite(11, HIGH);
  delay(500);
  noTone(10);
  
  unsigned long goTime = millis();
  while(digitalRead(7) == HIGH);
  
  unsigned long pressTime = millis();
  unsigned long reactionTime = pressTime - goTime;
  
  Serial.begin(9600);
  Serial.print("Reaction Time: ");
  Serial.print(reactionTime);
  Serial.println("ms");
  
  return reactionTime;
  
}

void winTune(){
  tone(10, 523, 150); //G4
  delay(300);
  tone(10, 659, 150); //G4
  delay(300);
  tone(10, 784, 300); //G4
  delay(500);
  noTone(10);
  
}

void loseTune(){
  tone(10, 392, 300); //G4
  delay(300);
  tone(10, 330, 300); //G4
  delay(300);
  tone(10, 262, 500); //G4
  delay(500);
  noTone(10);
  
}
  