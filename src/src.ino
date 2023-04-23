/* Arduino Pro Mini (Inland version) Pinout

  +----------------------------------+
  |          A7  A6 GND              |
  | [ ] 10  [ ] [ ] [ ]        9 [ ] |
  |                                  | 
  | [ ] 11                     8 [ ] |
  |                                  | 
  | [ ] 12                     7 [ ] |
  |                                  | 
  | [ ] 13         /\          6 [ ] |
  |              /    \              | 
  | [ ] A0     /        \      5 [ ] |
  |          /            \          | 
  | [ ] A1  |   ATmega328  |   4 [ ] |
  |          \            /          |
  | [ ] A2     \        /      3 [X] |  // Connects to LED
  |    [ ] A4    \    /              |
  | [ ] A3         \/          2 [ ] |
  |    [ ] A5                        | 
  | [X] 5V                   GND [ ] |  // Power
  |                                  | 
  | [ ] RST                  RST [ ] |
  |                                  | 
  | [X] GND                   RX [ ] |  // Ground
  |                                  | 
  | [ ] VIN                   TX [ ] |
  |                                  |
  |      [X] [X] [X] [X] [X] [X]     |  // FTDI connector
  |      GND GND  5V  RX  TX DTR     |
  +-------|---|---|---|---|---|------+
.         |   |   |   |   |   |
.         |   |   |   |   |   |
*/
/*
  PINS:
  [3] output for transmitted data

*/
//Pins
#define TX_DATA 3

//Transmit rate
#define TX_RATE 5

const char *message = "Howdy, world!";

void setup() {
  pinMode(TX_DATA, OUTPUT);

  for (int byte_idx = 0; byte_idx < strlen(message); byte_idx++) {
    char tx_byte = message[byte_idx];

    for (int bit_idx = 0; bit_idx < 8; bit_idx++) {
      bool tx_bit = tx_byte & (0x80 >> bit_idx);

      digitalWrite(TX_DATA, tx_bit);

      delay(1000 / TX_RATE);
    }
  }
  digitalWrite(TX_DATA, LOW);
}

void loop() {

}
