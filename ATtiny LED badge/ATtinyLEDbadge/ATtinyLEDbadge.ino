/*
    (C)2016 FabLabAQ info@fablaquila.org

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*~~~~~~~~~~~~ SCRIVI IL TUO NOME TRA VIRGOLETTE ~~~~~~~~~~~~*/

#define YOUR_NAME "FABLABAQ"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef __AVR_ATtiny13__
	#error Selezionare ATtiny13 da: Strumenti -> Schede
#endif

// Character set
PROGMEM const unsigned long alphabet[] = {
	0b00000000000000000000,	// 32 space
	0b00100010001000000010,	// 33 !
	0b01010101000000000000,	// 34 "
	0b01101111011011110110,	// 35 #
	0b01101000010000101100,	// 36 $
	0b00001001001001001001,	// 37 %
	0b01001000010110100101,	// 38 &
	0b00100010000000000000,	// 39 '
	0b00100100010001000010,	// 40 (
	0b01000010001000100100,	// 41 )
	0b01010010010100000000,	// 42 *
	0b00000000010011100100,	// 43 +
	0b00000000000000100100,	// 44 ,
	0b00000000011000000000,	// 45 -
	0b00000000000000000100,	// 46 .
	0b00010011011011001000,	// 47 /
	0b01101101101110010110,	// 48 0
	0b00100110001000100111,	// 49 1
	0b11100001011010001111,	// 50 2
	0b11100001011000011110,	// 51 3
	0b00100110101011110010,	// 52 4
	0b11111000111000011110,	// 53 5
	0b01101000111010010110,	// 54 6
	0b11110001001001001000,	// 55 7
	0b01101001011010010110,	// 56 8
	0b01101001011100010110,	// 57 9
	0b00000100000001000000,	// 58 :
	0b00000100000001001000,	// 59 ;
	0b00110110110001100011,	// 60 <
	0b00001111000011110000,	// 61 =
	0b11000110001101101100,	// 62 >
	0b01001010001001000100,	// 63 ?
	0b01101011101110000110,	// 64 @
	0b01101001111110011001,	// 65 A
	0b11101001111010011110,	// 66 B
	0b01111000100010000111,	// 67 C
	0b11101001100110011110,	// 68 D
	0b11111000111010001111,	// 69 E
	0b11111000111010001000,	// 70 F
	0b01111000101110010110,	// 71 G
	0b10011001111110011001,	// 72 H
	0b01110010001000100111, // 73 I
	0b01110010001010100100, // 74 J
	0b10011010110010101001, // 75 K
	0b10001000100010001111, // 76 L
	0b10011111111110011001, // 77 M
	0b10011101101110011001, // 78 N
	0b01101001100110010110, // 79 O
	0b11101001111010001000, // 80 P
	0b01101001101101100001, // 81 Q
	0b11101001111010101001, // 82 R
	0b01111000011000011110, // 83 S
	0b01110010001000100010, // 84 T
	0b10011001100110010110, // 85 U
	0b10011001100110100100, // 86 V
	0b10011001111111110110, // 87 W
	0b10011001011010011001, // 88 X
	0b10011001011000101100, // 89 Y
	0b11110001001001001111,	// 90 Z
	0b01100100010001000110,	// 91 [
	0b10001100011000110001,	// 92 \
	0b01100010001000100110,	// 93 ]
	0b01001010000000000000,	// 94 ^
	0b00000000000000001111,	// 95 _
	0b01000010000000000000,	// 96 `
	0b01100001011110010111,	// 97 a
	0b10001000111010011110,	// 98 b
	0b00000110100010000110,	// 99 c
	0b00010001011110010111,	// 100 d
	0b01101001111010000110,	// 101 e
	0b00110100111001000100,	// 102 f
	0b00110101001100010110,	// 103 g
	0b10001000111010011001,	// 104 h
	0b00100000001000100010,	// 105 i
	0b00100010001000100100,	// 106 j
	0b10001010101011001010,	// 107 k
	0b01000100010001000100,	// 108 l
	0b00001001111110011001,	// 109 m
	0b00000000111010011001,	// 110 n
	0b00000110100110010110,	// 111 o
	0b01100101011001000100,	// 112 p
	0b00110101001100010001,	// 113 q
	0b00001010110010001000,	// 114 r
	0b00110100001000010110,	// 115 s
	0b01001110010001000010,	// 116 t
	0b00001001100110010111,	// 117 u
	0b00000101010101010010,	// 118 v
	0b00000000100111110110,	// 119 w
	0b00000000010100100101,	// 120 x
	0b00000101001100010110,	// 121 y
	0b00001111001001001111,	// 122 z
	0b01100100110001000110,	// 123 {
	0b00100010001000100010,	// 124 |
	0b01100010001100100110,	// 125 }
	0b00000101101000000000	// 126 ~
};

const int displayWidth = 4;
const int displayHeight = 5;

// between pixels
const unsigned int timeout = 150;

const char PROGMEM displayString[] = YOUR_NAME;
const byte stringLength = sizeof(displayString);

// The offset of our string in the display
int offset = 0;
unsigned long lastMillis = 0;
unsigned long currentMillis = 0;

// render the string on the given offset
void renderString(int offset) {
  for(byte index=0; index< (stringLength-1); index++){
  	uint8_t pos = pgm_read_byte(&displayString[index]) - 32;
  	unsigned long gfx = pgm_read_dword(&alphabet[pos]);
    renderCharacter(gfx, offset - index * (displayWidth + 1));
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
  if (x < displayWidth) {
    if (y <= x) {
      x++;
    }
    setLed(4-x, 4-y, ledStatus);
  }
}

// turn on the pins to light a LED
void setLed(byte vin, byte gnd, boolean ledStatus) {
  delayMicroseconds(500);
  
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
    if (offset > (stringLength-1) * (displayWidth + 1)) {
      offset = -displayWidth;
    }
  }
}
