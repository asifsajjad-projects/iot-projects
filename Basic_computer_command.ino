bool start = false;
const int ledPin = LED_BUILTIN; 
const int motorPin = 8;
int ledState = LOW; 

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Serial connected!");
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
}

void loop() {  // run over and over
  // Serial.print("Start status: --");
  Serial.println(start);
  String myInput = Serial.readString();
  myInput.trim();
  // Serial.print(myInput);
  if (myInput.equalsIgnoreCase(String("start"))) {
    start = true;
    ledState = HIGH;
  } else if(myInput.equalsIgnoreCase(String("end"))){
    start = false;
    ledState = LOW;
  }
  digitalWrite(ledPin, ledState);
  digitalWrite(motorPin, ledState);
  delay(500);
}