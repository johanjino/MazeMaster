#define IR_Right 4
#define IR_Left 15

void setup() {
  Serial.begin(9600);      
  pinMode(IR_Right, INPUT); 
  pinMode(IR_Left, INPUT); 
}

void loop() {
  int IR_Right_Val = analogRead(IR_Right);
  int IR_Left_Val = analogRead(IR_Left);
  
  Serial.print("IR_Right: ");
  Serial.print(IR_Right_Val);
  Serial.print("  IR_Left: ");
  Serial.print(IR_Left_Val);
  Serial.println("");

  delay(500);
}
