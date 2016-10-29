// Character set
// Rows:         1---2---3---4---5---
const unsigned long  char_A = 0b01101001111110011001;
const unsigned long  char_B = 0b11101001111010011110;
const unsigned long  char_C = 0b01111000100010000111;
const unsigned long  char_D = 0b11101001100110011110;
const unsigned long  char_E = 0b11111000111010001111;
const unsigned long  char_F = 0b11111000111010001000;
const unsigned long  char_G = 0b01111000101110010110;
const unsigned long  char_H = 0b10011001111110011001;
const unsigned long  char_I = 0b01110010001000100111;
const unsigned long  char_J = 0b01110010001010100100;
const unsigned long  char_K = 0b10011010110010101001;
const unsigned long  char_L = 0b10001000100010001111;
const unsigned long  char_M = 0b10011111111110011001;
const unsigned long  char_N = 0b10011101101110011001;
const unsigned long  char_O = 0b01101001100110010110;
const unsigned long  char_P = 0b11101001111010001000;
const unsigned long  char_Q = 0b01101001101101100001;
const unsigned long  char_R = 0b11101001111010101001;
const unsigned long  char_S = 0b11111000111100011111;
const unsigned long  char_T = 0b01110010001000100010;
const unsigned long  char_U = 0b10011001100110010110;
const unsigned long  char_V = 0b10011001100110100100;
const unsigned long  char_W = 0b10011001111111110110;
const unsigned long  char_X = 0b10011001011010011001;
const unsigned long  char_Y = 0b10011001011000101100;
const unsigned long  char_Z = 0b11110001001001001111;
const unsigned long  char_space = 0b00000000000000000000;

const int displayWidth = 4;
const int displayHeight = 5;

// between pixels
const unsigned int timeout = 130;

const unsigned long displayString[] = {char_F, char_A, char_B, char_L, char_A, char_B, char_A, char_Q};
const int stringLength = sizeof(displayString);

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
void setPixel(byte x, byte y, boolean ledStatus) {
  if (x >= 0 && x < displayWidth) {
    if (y <= x) {
      x++;
    }
    setLed(4-x, 4-y, ledStatus);
  }
}

// turn on the pins to light a LED
void setLed(byte vin, byte gnd, boolean ledStatus) {
  delayMicroseconds(1000);
  
  if(ledStatus) {
    DDRB = (B00000001 << vin) | (B00000001 << gnd);
    PORTB = B00000001 << vin;
  }
  else {
    DDRB = B00000000;
  }
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
    if (offset > stringLength * (displayWidth + 1)) {
      offset = -displayWidth;
    }
  }
}
