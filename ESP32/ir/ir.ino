#define IR_Analog_INPUT 2

void setup() {
  Serial.begin(9600);      
  pinMode(IR_Analog_INPUT, INPUT); 
}

void loop() {
  int analogValue = analogRead(IR_Analog_INPUT);
  
  Serial.print("A_In: ");
  Serial.println(analogValue);

  delay(500);
}
