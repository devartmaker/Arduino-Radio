int f;

void setup() {
  Serial.begin(9600);
  
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
}

void loop() {
  int a = digitalRead(2);
  int b = digitalRead(3);

  Serial.print(a);
  Serial.print(" ");
  Serial.println(b);
}
