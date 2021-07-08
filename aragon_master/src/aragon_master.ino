SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
char rx[1];
char tx[1];
char value;


// setup() runs once, when the device is first turned on.
void setup() {
  Serial.begin(9600);
  pinMode(D5, OUTPUT);

  SPI.setClockSpeed(1, MHZ);
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.begin(SPI_MODE_MASTER, D5);

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  value = Serial.read();
  tx[0] = value; // send to slave what the user entered

  digitalWrite(D5, LOW);
  SPI.transfer(tx, rx, 1, NULL);
  digitalWrite(D5, HIGH);

  if(value == '?'){
    Serial.println(rx[0]); // if user enterd ? return data from the slave
  }
  // The core of your code will likely live here.

}