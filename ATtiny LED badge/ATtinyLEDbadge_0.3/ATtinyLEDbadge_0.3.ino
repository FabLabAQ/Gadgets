// Character set
// Rows:         1---2---3---4---5---
const unsigned long PROGMEM char_A = 0b01101001111110011001;
const unsigned long PROGMEM char_B = 0b11101001111010011110;
const unsigned long PROGMEM char_C = 0b01111000100010000111;
const unsigned long PROGMEM char_D = 0b11101001100110011110;
const unsigned long PROGMEM char_E = 0b11111000111010001111;
const unsigned long PROGMEM char_F = 0b11111000111010001000;
const unsigned long PROGMEM char_G = 0b01111000101110010110;
const unsigned long PROGMEM char_H = 0b10011001111110011001;
const unsigned long PROGMEM char_I = 0b01110010001000100111;
const unsigned long PROGMEM char_J = 0b01110010001010100100;
const unsigned long PROGMEM char_K = 0b10011010110010101001;
const unsigned long PROGMEM char_L = 0b10001000100010001111;
const unsigned long PROGMEM char_M = 0b10011111111110011001;
const unsigned long PROGMEM char_N = 0b10011101101110011001;
const unsigned long PROGMEM char_O = 0b01101001100110010110;
const unsigned long PROGMEM char_P = 0b11101001111010001000;
const unsigned long PROGMEM char_Q = 0b01101001101101100001;
const unsigned long PROGMEM char_R = 0b11101001111010101001;
const unsigned long PROGMEM char_S = 0b11111000111100011111;
const unsigned long PROGMEM char_T = 0b01110010001000100010;
const unsigned long PROGMEM char_U = 0b10011001100110010110;
const unsigned long PROGMEM char_V = 0b10011001100110100100;
const unsigned long PROGMEM char_W = 0b10011001111111110110;
const unsigned long PROGMEM char_X = 0b10011001011010011001;
const unsigned long PROGMEM char_Y = 0b10011001011000101100;
const unsigned long PROGMEM char_Z = 0b11110001001001001111;
const unsigned long PROGMEM char_space = 0b00000000000000000000;

const byte displayWidth = 4;
const byte displayHeight = 5;

// between pixels
const byte timeout = 100;

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ADJUST STRING LENGTH FIRST !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
const unsigned long PROGMEM displayString[] = {char_F, char_A, char_B, char_L, char_A, char_B, char_A, char_Q};
const byte length = sizeof(displayString);

// The offset of our string in the display
int offset = 0;
unsigned long lastMillis = 0;
unsigned long currentMillis = 0;

// render the string on the given offset
void renderString(int offset) {
  int index = 0;
  while (displayString[index]) {
    renderCharacter(displayString[index], offset - index * (displayWidth + 1));
    index++;
  }
}


void renderCharacter(unsigned long graphic, int charOffset) {
  if (charOffset <= -displayWidth || charOffset > displayWidth) {
    // off the 'screen' nothing to do
    delay(100);
    return;
  }

  for (byte y = 0; y < displayHeight; y++) {
    for (byte x = 0; x < displayWidth; x++) {
      // 3 - x to reverse order
      setPixel(3 - x - charOffset, y, graphic & 0x1);
      graphic = graphic >> 1;
    }
  }
}

// light a pixel at the given coordinates
void setPixel(byte x, byte y, bool ledStatus) {
  if (x >= 0 && x < displayWidth) {
    if (y <= x) {
      x++;
    }
    setLed(y, x, ledStatus);
  }
}

// turn on the pins to light a LED
void setLed(byte vin, byte gnd, bool ledStatus) {
  // delay(1);

  for(byte i=0; i<=4; i++) {
    pinMode(i, INPUT);
  }

  if(!ledStatus) return;

  pinMode(vin, OUTPUT);   
  pinMode(gnd, OUTPUT); 
  digitalWrite(vin, HIGH);
  digitalWrite(gnd, LOW); 
}


void setup() {
}


void loop() {
  currentMillis = millis();

  renderString(offset);

  if (currentMillis - lastMillis > timeout) {
    lastMillis = currentMillis;
    // shift string over one "pixel"
    offset++;
    // if it's past the length of the string, start over from the beginning
    if (offset > length * (displayWidth + 1)) {
      offset = -displayWidth;
    }
  }
}
