#include <LiquidCrystal.h> 

/* Arduino Pro Mini (Inland version) Pinout

  +----------------------------------+
  |          A7  A6 GND              |
  | [ ] 10  [ ] [ ] [ ]        9 [X] |  // EN
  |                                  | 
  | [ ] 11                     8 [X] |  // RS
  |                                  | 
  | [ ] 12                     7 [X] |  // LCD_D7
  |                                  | 
  | [ ] 13          /\         6 [X] |  // LCD_D6
  |               /    \             | 
  | [ ] A0      /        \     5 [X] |  // LCD_D5
  |           /            \         | 
  | [ ] A1  /   ATmega328   /  4 [X] |  // LCD_D4
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
//Arduino
#define TX_DATA 3
//Hitachi
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
#define LCD_RS 8
#define LCD_EN 9

//Transmit rate
#define TX_RATE 5

const char *message = "Howdy, world!";

void setup() {
  pinMode(TX_DATA, OUTPUT);

  // Init Hitachi
  LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("        ");

  lcd.setCursor(0, 0);
  lcd.print("Howdy, World!");

  for (int byte_idx = 0; byte_idx < strlen(message); byte_idx++) {
    char tx_byte = message[byte_idx];

    // Clears Hitachi line 2
    lcd.noCursor();
    lcd.setCursor(0, 1);
    lcd.print("        ");
    lcd.setCursor(byte_idx, 0);
    lcd.cursor();

    for (int bit_idx = 0; bit_idx < 8; bit_idx++) {
      bool tx_bit = tx_byte & (0x80 >> bit_idx);

      digitalWrite(TX_DATA, tx_bit);

      // Update Hitachi
      lcd.noCursor();
      lcd.setCursor(bit_idx, 1);
      lcd.print(tx_bit ? "1" : "0");
      lcd.setCursor(byte_idx, 0);
      lcd.cursor();


      delay(1000 / TX_RATE);
    }
    delay(1000 / TX_RATE);
  }
  digitalWrite(TX_DATA, LOW);
}

void loop() {

}
