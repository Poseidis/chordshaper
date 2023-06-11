const int sensorPins[] = {A0, A1}; //
//const int buttonPin = 3; 
//int buttonLast = 0;
//int button = 0;
int values[] = {0, 0};

//const int ledPin = 13;


void setup() {
  Serial.begin(38400);
  //  pinMode(ledPin, OUTPUT);
}

void loop() {
//  sensorValue = analogRead(sensorPin);
//  sensorValue = map(sensorValue, 0, 1023, 0, 255);

//  button = digitalRead(buttonPin);
//  if (!buttonLast)
//  {
////    Serial.write("start button");
////    Serial.write("button val");
////    Serial.write(button);
//    Serial.write(0);
//    Serial.write(button ? 1 : 0);
////    Serial.write("end button");
//  }
//  buttonLast = button;
  
  for (int i = 0; i < 2; i++) {
    values[i] = analogRead(sensorPins[i]);
    
    Serial.write(values[i] >> 3);
    Serial.write(values[i] & 7);
//    Serial.write(values[i]);
    Serial.write(255);
  }
  Serial.write(254);
}
