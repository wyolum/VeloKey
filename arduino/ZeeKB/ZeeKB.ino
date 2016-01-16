void setup() {
  Serial1.begin(9600); // serial connection to BF EZ-Key
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
}


void loop() {
  if(digitalRead(2) == LOW){
    Serial1.print("2");
  }
  if(digitalRead(3) == LOW){
    Serial1.print("3");
  }
  if(digitalRead(4) == LOW){
    Serial1.print("4");
  }
  if(digitalRead(5) == LOW){
    Serial1.print("5");
  }
  delay(100);
}
