#include "charactermap.h"

const int displayWidth = 4;
const int displayHeight = 5;

// between pixels
const unsigned int timeout = 130;

const unsigned long displayString[] = {char_F, char_A, char_B, char_L, char_A, char_B, char_A, char_Q};
const int stringLength = sizeof(displayString)/4;

// The offset of our string in the display
int offset = 0;
unsigned long lastMillis = 0;
unsigned long currentMillis = 0;

// render the string on the given offset
void renderString(int offset) {
  for(byte index=0; index<stringLength; index++){
    renderCharacter(displayString[index], offset - index * (displayWidth + 1));
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
    DDRB = (0x01 << vin) | (0x01 << gnd);
    PORTB = 0x01 << vin;
  }
  else {
    DDRB = 0x00;
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
