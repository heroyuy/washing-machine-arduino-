const int motorRight = 2;
const int motorLeft = 3;
const int drainPump = 4;
const int waterSolenoid = 5; 

void setup() {
  Serial.begin(9600); // Start the serial communication
  // ... your existing pinMode code ...
  Serial.println("System Initialized. Starting in 2 seconds...");

  pinMode(motorRight, OUTPUT);
  pinMode(motorLeft, OUTPUT);
  pinMode(drainPump, OUTPUT);
  pinMode(waterSolenoid, OUTPUT);

  allOff();
  
  delay(2000);
  
  startFullCycle();
}

void loop() {
}

void startFullCycle() {
  
  runDrain(90000); 

  runFill(190000); 

  runWash(900000); 

  runDrain(90000); 

  runFill(190000); 

  runWash(300000); 

  runDrain(90000); 

  allOff();
}


void runFill(unsigned long duration) {
  digitalWrite(waterSolenoid, HIGH);
  delay(duration);
  digitalWrite(waterSolenoid, LOW);
  delay(1000);
}

void runDrain(unsigned long duration) {
  Serial.print("Action: Filling Water... Time: ");
  Serial.print(duration / 1000);
  Serial.println(" seconds.");
  
  digitalWrite(drainPump, HIGH);
  delay(duration);
  digitalWrite(drainPump, LOW);
  delay(1000);
}

void runWash(unsigned long totalDuration) {
  unsigned long startTime = millis();
  while (millis() - startTime < totalDuration) {
    digitalWrite(motorRight, HIGH);  delay(10000);
    digitalWrite(motorRight, LOW); delay(3000);
    digitalWrite(motorLeft, HIGH);   delay(10000);
    digitalWrite(motorLeft, LOW);  delay(3000);
  }
}

void allOff() {
  digitalWrite(motorRight, LOW);
  digitalWrite(motorLeft, LOW);
  digitalWrite(drainPump, LOW);
  digitalWrite(waterSolenoid, LOW);
}