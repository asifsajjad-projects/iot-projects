// Set up the hardware serial ports
#define rs232Serial Serial1 // or any other hardware serial (Serial1, Serial2, etc.)

void setup() {
  // Initialize the built-in serial port (USB)
  Serial.begin(9600); // USB communication at 9600 baud rate
  
  // Initialize the RS232 serial port (RS232 to TTL converter)
  rs232Serial.begin(9600); // Match the baud rate of the RS232 device

  Serial.println("RS232 to TTL communication started...");
}

void loop() {
  // If data is available on the RS232 serial port, read and send it to the USB Serial Monitor
  if (rs232Serial.available()) {
    char data = rs232Serial.read();
    Serial.print("Received from RS232: ");
    Serial.println(data);
  }

  // If data is available on the USB serial port (Serial Monitor), send it to the RS232 serial port
  if (Serial.available()) {
    char data = Serial.read();
    rs232Serial.print(data);  // Send to RS232 device
  }
}
