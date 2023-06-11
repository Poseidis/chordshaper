const int sensorPins[] = {A0, A1}; //

int values[] = {0, 0};

void setup() {
  Serial.begin(38400);
}

void loop() {
  for (int i = 0; i < 2; i++) {
    values[i] = analogRead(sensorPins[i]);
    
    Serial.write(values[i] >> 3);
    Serial.write(values[i] & 7);
    Serial.write(255);
  }
  Serial.write(254);
}
