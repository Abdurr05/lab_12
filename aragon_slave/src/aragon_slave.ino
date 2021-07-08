SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
char tx[1];
char rx[1];
bool CS = false;
void takeAction(uint8_t state) {
  if (state) {
     CS = true; // watch for this variable in loop and set it back to false once you detect it.
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(D5, OUTPUT);
  pinMode(D7, INPUT);

  SPI1.setBitOrder(MSBFIRST);
  SPI1.setDataMode(SPI_MODE0);
  SPI1.onSelect(takeAction);
  SPI1.begin(SPI_MODE_SLAVE, D6);
  // Put initialization like pinMode and begin functions here.

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  if(CS == true){
    SPI1.transfer(tx, rx, 1, NULL);
    // if master enters 1 turn on the led
    if (rx[0] == '1'){
      digitalWrite(D5,HIGH);
    }
    // if master enters 0 turn off the led
    if(rx[0] == '0'){
      digitalWrite(D5,LOW);
    }
    // if master enters ? return 1 if the button is pressed and return 0 if the button isn't pressed
    if(rx[0] == '?'){
      if(digitalRead(D7)== 1){
        tx[0] = '1';
      } else{
        tx[0] = '0';
      }
    }
    CS = false;
  }


  

  // The core of your code will likely live here.

}