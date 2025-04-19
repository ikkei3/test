/*

 L fuwa
  for digital Port (not PWM Port)
  Arduino UNO

 MaiaR create
  maiar_create@zeus.eonet.ne.jp
  
*/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  static int a = 0;
  static int b = 1;
  static int c = 0;

  a = a + b;
  if (a >= 127){
    b = -1;
  }else if (a == 0){
    b =  1;
  }
  c = a * a / 1024;
  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(c);
  digitalWrite(LED_BUILTIN, LOW);
  delay(16 - c);
}
