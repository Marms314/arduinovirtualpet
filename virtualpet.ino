// Needed dependencies Wire for I2C, and graphics
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display height and width in pixels
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// Reset pin not used, but neededd for library
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Menu graphics size values
#define MENU_ITEM_HEIGHT 13
#define MENU_ITEM_WIDTH 16
#define MENU_ITEM_COUNT 3

// Heart graphics size values
#define HEART_HEIGHT 13
#define HEART_HALF_WIDTH 8

// Create button arrays. Order is: green, left, right, red
int btns[] = {2, 3, 4, 5};
int btnReads[] = {0, 0, 0, 0};
int prevBtnReads[] = {0, 0, 0, 0};
byte menuSelection = 0;

// Create Pet animation variables
byte jumpFramePet = 0;
int xPosPet = -37;
int yPosPet = 40;
bool isFacingRightPet = true;
byte petIdleCount = 0;
byte petRestCount = 0;

// Create enemy Pet animation variables
byte jumpFramePetEnemy = 0;
int xPosEnemy = 129;
int yPosEnemy = 40;
bool isFacingRightEnemy = false;
byte enemyRestCount = 0;

// Bitmaps for graphics
const uint8_t empty_heart_half_bmp[] PROGMEM =
{ B00111000,
  B01000100,
  B10000010,
  B10000001,
  B10000000,
  B10000000,
  B01000000,
  B00100000,
  B00010000,
  B00001000,
  B00000100,
  B00000010,
  B00000001
};

const uint8_t full_heart_half_bmp[] PROGMEM =
{ B00111000,
  B01111100,
  B11111110,
  B11111111,
  B11111111,
  B11111111,
  B01111111,
  B00111111,
  B00011111,
  B00001111,
  B00000111,
  B00000011,
  B00000001
};

const uint8_t apple_bmp[] PROGMEM =
{ B00000001, B10000000,
  B00111001, B00011100,
  B01111111, B01100110,
  B11111111, B11100011,
  B11111111, B11110001,
  B11111111, B11110001,
  B11111111, B11110011,
  B11111111, B11110111,
  B01111111, B11111110,
  B00111111, B11111100,
  B00011111, B11111000,
  B00011111, B11111000,
  B00001101, B10110000
};

const uint8_t boxing_glove_bmp[] PROGMEM =
{ B00000001, B11110000,
  B00000011, B11110000,
  B00000111, B11100000,
  B00001111, B11111110,
  B11111111, B11011111,
  B10011111, B10111111,
  B10011111, B10111111,
  B10011111, B10111111,
  B10011111, B10111111,
  B10011111, B10111111,
  B11111111, B11011111,
  B00001111, B11101110,
  B00000111, B11111100
};

const uint8_t jumpBmp[23][120] PROGMEM = {
  { // 'jump_00', 40x24px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0f, 0x8f, 0x00, 0x00, 0x00, 0x10, 0x50, 0x80, 0x00, 0x00, 0x20, 0x20, 0x40, 0x00, 0x00,
    0x43, 0x06, 0x20, 0x00, 0x00, 0x44, 0x89, 0x20, 0x00, 0x00, 0x49, 0x52, 0xa0, 0x00, 0x07, 0xcb,
    0x56, 0xa0, 0x00, 0x08, 0x49, 0x52, 0xa0, 0x00, 0x30, 0x04, 0x89, 0x10, 0x00, 0x40, 0x03, 0x06,
    0x08, 0x00, 0x80, 0x10, 0x00, 0x88, 0x01, 0x06, 0x0f, 0xff, 0x08, 0x01, 0x01, 0x00, 0x00, 0x10,
    0x01, 0x00, 0x80, 0x00, 0x60, 0x00, 0xa1, 0x00, 0x01, 0x80, 0x00, 0x42, 0x09, 0x06, 0x00, 0x00,
    0x44, 0x09, 0x39, 0x80, 0x00, 0x43, 0x88, 0xc8, 0x60, 0x00, 0x80, 0x78, 0x24, 0x10, 0x00, 0x7f,
    0x87, 0xc3, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00
  },
  
  { // 'jump_01', 40x24px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x0f, 0x8f, 0x00, 0x00, 0x00, 0x10, 0x50, 0x80, 0x00, 0x00, 0x20, 0x20, 0x40, 0x00, 0x00,
    0x43, 0x06, 0x20, 0x00, 0x00, 0x44, 0x89, 0x20, 0x00, 0x00, 0x49, 0x52, 0xa0, 0x00, 0x07, 0xcb,
    0x56, 0xa0, 0x00, 0x08, 0x49, 0x52, 0xa0, 0x00, 0x30, 0x04, 0x89, 0x10, 0x00, 0x40, 0x03, 0x06,
    0x08, 0x00, 0x80, 0x10, 0x00, 0x28, 0x01, 0x06, 0x0f, 0xff, 0xc8, 0x01, 0x01, 0x00, 0x00, 0x10,
    0x01, 0x00, 0x80, 0x00, 0x60, 0x00, 0xa1, 0x00, 0x01, 0x80, 0x00, 0x42, 0x09, 0x06, 0x00, 0x00,
    0x44, 0x09, 0x39, 0x80, 0x00, 0x43, 0x88, 0xc8, 0x60, 0x00, 0x80, 0x78, 0x24, 0x10, 0x00, 0x7f,
    0x87, 0xc3, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00
  },

  { // 'jump_02', 40x24px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x8f, 0x00, 0x00, 0x00, 0x10, 0x50, 0x80, 0x00, 0x00,
    0x20, 0x20, 0x40, 0x00, 0x00, 0x43, 0x06, 0x20, 0x00, 0x00, 0x44, 0x89, 0x20, 0x00, 0x00, 0x49,
    0x52, 0xa0, 0x00, 0x07, 0xcb, 0x56, 0xa0, 0x00, 0x08, 0x49, 0x52, 0xa0, 0x00, 0x30, 0x04, 0x89,
    0x10, 0x00, 0x40, 0x03, 0x06, 0x08, 0x00, 0x80, 0x10, 0x00, 0x28, 0x01, 0x06, 0x0f, 0xff, 0xc8,
    0x01, 0x01, 0x00, 0x00, 0x10, 0x01, 0x00, 0x80, 0x00, 0x60, 0x00, 0xa1, 0x00, 0x01, 0x80, 0x00,
    0x42, 0x09, 0x06, 0x00, 0x00, 0x47, 0x89, 0xf9, 0xe0, 0x00, 0x80, 0x78, 0x24, 0x10, 0x00, 0x7f,
    0x87, 0xc3, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00
  },

  { // 'jump_03', 40x24px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x8f, 0x00, 0x00, 0x00,
    0x10, 0x50, 0x80, 0x00, 0x00, 0x20, 0x20, 0x40, 0x00, 0x00, 0x43, 0x06, 0x20, 0x00, 0x00, 0x44,
    0x89, 0x20, 0x00, 0x00, 0x49, 0x52, 0xa0, 0x00, 0x07, 0xcb, 0x56, 0xa0, 0x00, 0x08, 0x49, 0x52,
    0xa0, 0x00, 0x30, 0x04, 0x89, 0x10, 0x00, 0x40, 0x03, 0x06, 0x08, 0x00, 0x80, 0x04, 0x00, 0x88,
    0x01, 0x06, 0x03, 0xff, 0x08, 0x01, 0x01, 0x00, 0x00, 0x10, 0x01, 0x00, 0x80, 0x00, 0x60, 0x00,
    0xa1, 0x00, 0x01, 0x80, 0x00, 0x42, 0x09, 0x06, 0x00, 0x00, 0xc7, 0xf9, 0xfd, 0xf0, 0x00, 0x7f,
    0x87, 0xc3, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00
  },

  { // 'jump_04', 40x24px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x8f, 0x00, 0x00, 0x00, 0x10, 0x50, 0x80, 0x00, 0x00,
    0x20, 0x20, 0x40, 0x00, 0x00, 0x43, 0x06, 0x20, 0x00, 0x00, 0x44, 0x89, 0x20, 0x00, 0x00, 0x49,
    0x52, 0xa0, 0x00, 0x07, 0xcb, 0x56, 0xa0, 0x00, 0x08, 0x49, 0x52, 0xa0, 0x00, 0x30, 0x04, 0x89,
    0x10, 0x00, 0x40, 0x03, 0x06, 0x08, 0x00, 0x80, 0x00, 0x00, 0x08, 0x01, 0x06, 0x01, 0xfc, 0x08,
    0x01, 0x01, 0x00, 0x70, 0x10, 0x01, 0x00, 0x80, 0x00, 0x60, 0x00, 0xa1, 0x00, 0x01, 0x80, 0x00,
    0x42, 0x09, 0x06, 0x00, 0x00, 0x47, 0x89, 0xf9, 0xe0, 0x00, 0x80, 0x78, 0x24, 0x10, 0x00, 0x7f,
    0x87, 0xc3, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00
  },

  { // 'jump_05', 40x24px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x8f, 0x00, 0x00,
    0x00, 0x10, 0x50, 0x80, 0x00, 0x00, 0x20, 0x20, 0x40, 0x00, 0x00, 0x43, 0x06, 0x20, 0x00, 0x00,
    0x44, 0x89, 0x20, 0x00, 0x00, 0x49, 0x52, 0xa0, 0x00, 0x07, 0xcb, 0x56, 0xa0, 0x00, 0x08, 0x49,
    0x52, 0xa0, 0x00, 0x30, 0x04, 0x89, 0x10, 0x00, 0x40, 0x03, 0x06, 0x08, 0x00, 0x80, 0x00, 0x00,
    0x08, 0x01, 0x04, 0x01, 0xfc, 0x08, 0x01, 0x02, 0x00, 0xf8, 0x10, 0x01, 0x01, 0x00, 0x00, 0x60,
    0x00, 0xa0, 0x80, 0x01, 0x80, 0x00, 0x41, 0x09, 0x06, 0x00, 0x00, 0x42, 0x09, 0x39, 0x00, 0x00,
    0x44, 0x09, 0x48, 0x80, 0x00, 0x83, 0xb8, 0xc4, 0x60, 0x00, 0x60, 0x46, 0x23, 0x10, 0x00, 0x1f,
    0x81, 0xc0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00
  },

  { // 'jump_06', 40x24px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x8f, 0x00, 0x00, 0x00, 0x10, 0x50, 0x80, 0x00,
    0x00, 0x20, 0x20, 0x40, 0x00, 0x00, 0x43, 0x06, 0x20, 0x00, 0x00, 0x44, 0x89, 0x20, 0x00, 0x00,
    0x49, 0x52, 0xa0, 0x00, 0x07, 0xcb, 0x56, 0xa0, 0x00, 0x08, 0x49, 0x52, 0xa0, 0x00, 0x30, 0x04,
    0x89, 0x10, 0x00, 0x40, 0x03, 0x06, 0x08, 0x00, 0x80, 0x00, 0x00, 0x08, 0x01, 0x00, 0x01, 0xfc,
    0x08, 0x01, 0x02, 0x00, 0xf8, 0x10, 0x01, 0x01, 0x00, 0x00, 0x60, 0x00, 0x81, 0x00, 0x01, 0x80,
    0x00, 0x42, 0x01, 0x06, 0x00, 0x00, 0x84, 0x09, 0x3a, 0x00, 0x01, 0x0c, 0x19, 0xca, 0x00, 0x01,
    0x13, 0xe9, 0x09, 0x00, 0x01, 0x0f, 0x24, 0xc4, 0xc0, 0x00, 0xc0, 0x92, 0x22, 0x20, 0x00, 0x3f,
    0xe1, 0xc1, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00
  },

  { // 'jump_07', 40x24px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x8f, 0x00, 0x00, 0x00, 0x10, 0x50, 0x80, 0x00,
    0x00, 0x20, 0x20, 0x40, 0x00, 0x00, 0x43, 0x06, 0x20, 0x00, 0x00, 0x44, 0x89, 0x20, 0x00, 0x00,
    0x49, 0x52, 0xa0, 0x00, 0x00, 0x4b, 0x56, 0xa0, 0x00, 0x0f, 0x89, 0x52, 0xa0, 0x00, 0x30, 0x04,
    0x89, 0x10, 0x00, 0x40, 0x03, 0x06, 0x08, 0x00, 0x80, 0x00, 0x00, 0x08, 0x01, 0x00, 0x00, 0xf8,
    0x08, 0x01, 0x02, 0x00, 0x70, 0x10, 0x01, 0x02, 0x00, 0x70, 0x60, 0x00, 0x82, 0x00, 0x01, 0x80,
    0x00, 0x84, 0x01, 0x06, 0x00, 0x01, 0x18, 0x09, 0x3a, 0x00, 0x02, 0x2b, 0xf9, 0xca, 0x00, 0x04,
    0x49, 0x09, 0x0a, 0x00, 0x04, 0x3c, 0xc8, 0x89, 0x80, 0x03, 0x02, 0x24, 0x44, 0x40, 0x00, 0xff,
    0xc3, 0x83, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00
  },

  { // 'jump_08', 40x24px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x8f, 0x00, 0x00, 0x00, 0x10, 0x50, 0x80, 0x00,
    0x00, 0x20, 0x20, 0x40, 0x00, 0x00, 0x43, 0x06, 0x20, 0x00, 0x00, 0x44, 0x89, 0x20, 0x00, 0x00,
    0x49, 0x52, 0xa0, 0x00, 0x00, 0x4b, 0x56, 0xa0, 0x00, 0x0f, 0x89, 0x52, 0xa0, 0x00, 0x30, 0x04,
    0x89, 0x10, 0x00, 0x40, 0x03, 0x06, 0x08, 0x00, 0x80, 0x00, 0x00, 0x08, 0x01, 0x00, 0x00, 0xf8,
    0x08, 0x01, 0x00, 0x00, 0x70, 0x10, 0x01, 0x02, 0x00, 0x70, 0x60, 0x01, 0x04, 0x00, 0x01, 0x80,
    0x02, 0x08, 0x01, 0x06, 0x00, 0x04, 0x30, 0x09, 0x3a, 0x00, 0x08, 0x53, 0xf9, 0xca, 0x00, 0x08,
    0x89, 0x09, 0x0a, 0x00, 0x08, 0x52, 0x09, 0x09, 0x00, 0x06, 0x39, 0x84, 0x84, 0x80, 0x01, 0x84,
    0x42, 0x42, 0x40, 0x00, 0x7b, 0x81, 0x81, 0x80
  },

  { // 'jump_09', 40x24px
    0x00, 0x00, 0x0f, 0x8f, 0x00, 0x00, 0x00, 0x10, 0x50, 0x80, 0x00, 0x00, 0x20, 0x20, 0x40, 0x00,
    0x00, 0x43, 0x06, 0x20, 0x00, 0x00, 0x44, 0x89, 0x20, 0x00, 0x00, 0x49, 0x52, 0xa0, 0x00, 0x00,
    0x4b, 0x56, 0xa0, 0x00, 0x0f, 0x89, 0x52, 0xa0, 0x00, 0x30, 0x04, 0x89, 0x10, 0x00, 0x40, 0x03,
    0x06, 0x08, 0x00, 0x80, 0x00, 0x00, 0x08, 0x01, 0x00, 0x00, 0xf8, 0x08, 0x01, 0x00, 0x00, 0x70,
    0x10, 0x01, 0x02, 0x00, 0x70, 0x60, 0x01, 0x04, 0x00, 0x01, 0x80, 0x02, 0x08, 0x01, 0x06, 0x00,
    0x04, 0x30, 0x09, 0x3a, 0x00, 0x08, 0x53, 0xf9, 0xca, 0x00, 0x10, 0x89, 0x09, 0x0a, 0x00, 0x21,
    0x12, 0x09, 0x0a, 0x00, 0x21, 0x24, 0x09, 0x0a, 0x00, 0x23, 0xa6, 0x09, 0x09, 0x00, 0x18, 0x51,
    0x04, 0x84, 0x80, 0x07, 0x8e, 0x03, 0x03, 0x00
  },

  { // 'jump_10', 40x24px
    0x00, 0x00, 0x0f, 0x8f, 0x00, 0x00, 0x00, 0x10, 0x50, 0x80, 0x00, 0x00, 0x20, 0x20, 0x40, 0x00,
    0x00, 0x43, 0x06, 0x20, 0x00, 0x00, 0x44, 0x89, 0x20, 0x00, 0x00, 0x49, 0x52, 0xa0, 0x00, 0x00,
    0x4b, 0x56, 0xa0, 0x00, 0x0f, 0x89, 0x52, 0xa0, 0x00, 0x30, 0x04, 0x89, 0x10, 0x00, 0x40, 0x03,
    0x06, 0x08, 0x00, 0x80, 0x00, 0x00, 0x08, 0x00, 0x80, 0x00, 0xf8, 0x08, 0x01, 0x00, 0x00, 0x70,
    0x10, 0x02, 0x04, 0x00, 0x70, 0x60, 0x02, 0x08, 0x00, 0x01, 0x80, 0x04, 0x30, 0x01, 0x06, 0x00,
    0x08, 0x50, 0x09, 0x3a, 0x00, 0x10, 0x93, 0xf9, 0xca, 0x00, 0x21, 0x12, 0x09, 0x0a, 0x00, 0x42,
    0x24, 0x09, 0x0a, 0x00, 0x44, 0x48, 0x09, 0x0a, 0x00, 0x47, 0x4c, 0x09, 0x09, 0x00, 0x30, 0xa2,
    0x04, 0x84, 0x80, 0x0f, 0x1c, 0x03, 0x03, 0x00
  },

  { // 'jump_11', 40x24px
    0x00, 0x00, 0x0f, 0x8f, 0x00, 0x00, 0x00, 0x10, 0x50, 0x80, 0x00, 0x00, 0x20, 0x20, 0x40, 0x00,
    0x00, 0x43, 0x06, 0x20, 0x00, 0x00, 0x44, 0x89, 0x20, 0x00, 0x00, 0x49, 0x52, 0xa0, 0x00, 0x00,
    0x4b, 0x56, 0xa0, 0x00, 0x0f, 0x89, 0x52, 0xa0, 0x00, 0x30, 0x04, 0x89, 0x10, 0x00, 0x40, 0x03,
    0x06, 0x08, 0x00, 0x80, 0x00, 0x00, 0x08, 0x00, 0x80, 0x00, 0xf8, 0x08, 0x01, 0x00, 0x00, 0x70,
    0x10, 0x02, 0x04, 0x00, 0x70, 0x60, 0x02, 0x08, 0x00, 0x01, 0x80, 0x04, 0x30, 0x01, 0x06, 0x00,
    0x08, 0x50, 0x09, 0x3a, 0x00, 0x10, 0x93, 0xf9, 0xca, 0x00, 0x21, 0x12, 0x09, 0x0a, 0x00, 0x42,
    0x24, 0x09, 0x0a, 0x00, 0x44, 0x48, 0x09, 0x0a, 0x00, 0x4e, 0x48, 0x09, 0x09, 0x00, 0x21, 0x44,
    0x04, 0x84, 0x80, 0x1e, 0x38, 0x03, 0x03, 0x00
  },

  { // 'jump_12', 40x24px
    0x00, 0x00, 0x0f, 0x8f, 0x00, 0x00, 0x00, 0x10, 0x50, 0x80, 0x00, 0x00, 0x20, 0x20, 0x40, 0x00,
    0x00, 0x43, 0x06, 0x20, 0x00, 0x00, 0x44, 0x89, 0x20, 0x00, 0x00, 0x49, 0x52, 0xa0, 0x00, 0x00,
    0x4b, 0x56, 0xa0, 0x00, 0x0f, 0x89, 0x52, 0xa0, 0x00, 0x30, 0x04, 0x89, 0x10, 0x00, 0x40, 0x03,
    0x06, 0x08, 0x00, 0x80, 0x00, 0x00, 0x08, 0x00, 0x80, 0x00, 0xf8, 0x08, 0x01, 0x00, 0x00, 0x70,
    0x10, 0x02, 0x04, 0x00, 0x70, 0x60, 0x02, 0x08, 0x00, 0x01, 0x80, 0x04, 0x30, 0x01, 0x06, 0x00,
    0x08, 0x50, 0x09, 0x3a, 0x00, 0x10, 0x93, 0xf9, 0xca, 0x00, 0x21, 0x12, 0x09, 0x0a, 0x00, 0x42,
    0x24, 0x04, 0x85, 0x00, 0x44, 0x48, 0x04, 0x85, 0x00, 0x4c, 0x48, 0x04, 0x84, 0x80, 0x42, 0x44,
    0x02, 0x42, 0x40, 0x3c, 0x38, 0x01, 0x81, 0x80
  },

  { // 'jump_13', 40x24px
    0x00, 0x00, 0x0f, 0x8f, 0x00, 0x00, 0x00, 0x10, 0x50, 0x80, 0x00, 0x00, 0x20, 0x20, 0x40, 0x00,
    0x00, 0x43, 0x06, 0x20, 0x00, 0x00, 0x44, 0x89, 0x20, 0x00, 0x00, 0x49, 0x52, 0xa0, 0x00, 0x00,
    0x4b, 0x56, 0xa0, 0x00, 0x0f, 0x89, 0x52, 0xa0, 0x00, 0x30, 0x04, 0x89, 0x10, 0x00, 0x40, 0x03,
    0x06, 0x08, 0x00, 0x80, 0x00, 0x00, 0x08, 0x00, 0x80, 0x00, 0xf8, 0x08, 0x01, 0x00, 0x00, 0x70,
    0x10, 0x02, 0x04, 0x00, 0x70, 0x60, 0x02, 0x08, 0x00, 0x01, 0x80, 0x04, 0x30, 0x01, 0x06, 0x00,
    0x08, 0x50, 0x09, 0x3a, 0x00, 0x10, 0x93, 0xf9, 0xca, 0x00, 0x21, 0x12, 0x09, 0x0a, 0x00, 0x42,
    0x24, 0x04, 0x85, 0x00, 0x44, 0x48, 0x04, 0x85, 0x00, 0x88, 0x90, 0x04, 0x84, 0x80, 0x84, 0x88,
    0x02, 0x42, 0x40, 0x78, 0x70, 0x01, 0x81, 0x80
  },

  { // 'jump_14', 40x24px
    0x00, 0x00, 0x0f, 0x8f, 0x00, 0x00, 0x00, 0x10, 0x50, 0x80, 0x00, 0x00, 0x20, 0x20, 0x40, 0x00,
    0x00, 0x43, 0x06, 0x20, 0x00, 0x00, 0x44, 0x89, 0x20, 0x00, 0x00, 0x49, 0x52, 0xa0, 0x00, 0x00,
    0x4b, 0x56, 0xa0, 0x00, 0x0f, 0x89, 0x52, 0xa0, 0x00, 0x30, 0x04, 0x89, 0x10, 0x00, 0x40, 0x03,
    0x06, 0x08, 0x00, 0x80, 0x00, 0x00, 0x08, 0x00, 0x80, 0x00, 0xf8, 0x08, 0x01, 0x00, 0x00, 0x70,
    0x10, 0x02, 0x04, 0x00, 0x70, 0x60, 0x02, 0x08, 0x00, 0x01, 0x80, 0x04, 0x30, 0x01, 0x06, 0x00,
    0x08, 0x50, 0x09, 0x3a, 0x00, 0x10, 0x93, 0xf9, 0xca, 0x00, 0x21, 0x24, 0x04, 0x85, 0x00, 0x42,
    0x48, 0x02, 0x42, 0x80, 0x44, 0x90, 0x02, 0x42, 0x80, 0x89, 0x20, 0x02, 0x42, 0x40, 0x85, 0x10,
    0x01, 0x21, 0x20, 0x78, 0xe0, 0x00, 0xc0, 0xc0
  },

  { // 'jump_15', 40x24px
    0x00, 0x00, 0x0f, 0x8f, 0x00, 0x00, 0x00, 0x10, 0x50, 0x80, 0x00, 0x00, 0x20, 0x20, 0x40, 0x00,
    0x00, 0x43, 0x06, 0x20, 0x00, 0x00, 0x44, 0x89, 0x20, 0x00, 0x00, 0x49, 0x52, 0xa0, 0x00, 0x00,
    0x4b, 0x56, 0xa0, 0x00, 0x0f, 0x89, 0x52, 0xa0, 0x00, 0x30, 0x04, 0x89, 0x10, 0x00, 0x40, 0x03,
    0x06, 0x08, 0x00, 0x80, 0x00, 0x00, 0x08, 0x00, 0x80, 0x00, 0xf8, 0x08, 0x01, 0x00, 0x00, 0x70,
    0x10, 0x02, 0x04, 0x00, 0x70, 0x60, 0x04, 0x38, 0x00, 0x01, 0x80, 0x08, 0x50, 0x01, 0x06, 0x00,
    0x10, 0x90, 0x09, 0x3a, 0x00, 0x21, 0x27, 0xf9, 0xca, 0x00, 0x42, 0x48, 0x04, 0x85, 0x00, 0x44,
    0x90, 0x02, 0x42, 0x80, 0x89, 0x20, 0x02, 0x42, 0x80, 0x85, 0x10, 0x02, 0x42, 0x40, 0x78, 0xe0,
    0x01, 0x21, 0x20, 0x00, 0x00, 0x00, 0xc0, 0xc0
  },

  { // 'jump_16', 40x24px
    0x00, 0x00, 0x0f, 0x8f, 0x00, 0x00, 0x00, 0x10, 0x50, 0x80, 0x00, 0x00, 0x20, 0x20, 0x40, 0x00,
    0x00, 0x43, 0x06, 0x20, 0x00, 0x00, 0x44, 0x89, 0x20, 0x00, 0x00, 0x49, 0x52, 0xa0, 0x00, 0x0f,
    0xcb, 0x56, 0xa0, 0x00, 0x30, 0x09, 0x52, 0xa0, 0x00, 0x40, 0x04, 0x89, 0x10, 0x00, 0x80, 0x03,
    0x06, 0x08, 0x01, 0x80, 0x00, 0x00, 0x08, 0x02, 0x00, 0x00, 0xf8, 0x08, 0x04, 0x3c, 0x00, 0x70,
    0x10, 0x08, 0x50, 0x00, 0x70, 0x60, 0x10, 0x90, 0x00, 0x01, 0x80, 0x21, 0x20, 0x01, 0x06, 0x00,
    0x42, 0x4f, 0x89, 0x3a, 0x00, 0x44, 0x90, 0x79, 0xca, 0x00, 0x89, 0x20, 0x04, 0x85, 0x00, 0x85,
    0x10, 0x02, 0x42, 0x80, 0x78, 0xe0, 0x01, 0x21, 0x40, 0x00, 0x00, 0x01, 0x21, 0x20, 0x00, 0x00,
    0x00, 0x90, 0x90, 0x00, 0x00, 0x00, 0x60, 0x60
  },

  { // 'jump_17', 40x24px
    0x00, 0x00, 0x0f, 0x8f, 0x00, 0x00, 0x00, 0x10, 0x50, 0x80, 0x00, 0x00, 0x20, 0x20, 0x40, 0x00,
    0x00, 0x43, 0x06, 0x20, 0x00, 0x00, 0x44, 0x89, 0x20, 0x00, 0x00, 0x49, 0x52, 0xa0, 0x00, 0x0f,
    0xcb, 0x56, 0xa0, 0x00, 0x30, 0x09, 0x52, 0xa0, 0x00, 0x40, 0x04, 0x89, 0x10, 0x00, 0x80, 0x03,
    0x06, 0x08, 0x01, 0x80, 0x00, 0x00, 0x08, 0x02, 0x00, 0x00, 0xf8, 0x08, 0x04, 0x3c, 0x00, 0x70,
    0x10, 0x08, 0x50, 0x00, 0x70, 0x60, 0x10, 0x90, 0x00, 0x01, 0x80, 0x21, 0x20, 0x01, 0x06, 0x00,
    0x42, 0x4f, 0x89, 0x3a, 0x00, 0x44, 0x90, 0x79, 0xca, 0x00, 0x89, 0x20, 0x04, 0x85, 0x00, 0x85,
    0x10, 0x04, 0x85, 0x00, 0x78, 0xe0, 0x04, 0x85, 0x00, 0x00, 0x00, 0x04, 0x84, 0x80, 0x00, 0x00,
    0x02, 0x42, 0x40, 0x00, 0x00, 0x01, 0x81, 0x80
  },

  { // 'jump_18', 40x24px
    0x00, 0x00, 0x0f, 0x8f, 0x00, 0x00, 0x00, 0x10, 0x50, 0x80, 0x00, 0x00, 0x20, 0x20, 0x40, 0x00,
    0x00, 0x43, 0x06, 0x20, 0x00, 0x00, 0x44, 0x89, 0x20, 0x00, 0x00, 0x49, 0x52, 0xa0, 0x00, 0x0f,
    0xcb, 0x56, 0xa0, 0x00, 0x30, 0x09, 0x52, 0xa0, 0x00, 0x40, 0x04, 0x89, 0x10, 0x00, 0x80, 0x03,
    0x06, 0x08, 0x01, 0x80, 0x00, 0x00, 0x08, 0x02, 0x00, 0x00, 0xf8, 0x08, 0x04, 0x3c, 0x00, 0x70,
    0x10, 0x08, 0x50, 0x00, 0x70, 0x60, 0x10, 0x90, 0x00, 0x01, 0x80, 0x21, 0x20, 0x01, 0x06, 0x00,
    0x42, 0x4f, 0x89, 0x3a, 0x00, 0x44, 0x90, 0x79, 0xca, 0x00, 0x89, 0x20, 0x09, 0x0a, 0x00, 0x85,
    0x10, 0x09, 0x0a, 0x00, 0x78, 0xe0, 0x09, 0x0a, 0x00, 0x00, 0x00, 0x09, 0x09, 0x00, 0x00, 0x00,
    0x04, 0x84, 0x80, 0x00, 0x00, 0x03, 0x03, 0x00
  },

  { // 'jump_19', 40x24px
    0x00, 0x00, 0x0f, 0x8f, 0x00, 0x00, 0x00, 0x10, 0x50, 0x80, 0x00, 0x00, 0x20, 0x20, 0x40, 0x00,
    0x00, 0x43, 0x06, 0x20, 0x00, 0x00, 0x44, 0x89, 0x20, 0x00, 0x00, 0x49, 0x52, 0xa0, 0x00, 0x00,
    0x4b, 0x56, 0xa0, 0x00, 0x0f, 0x89, 0x52, 0xa0, 0x00, 0x30, 0x04, 0x89, 0x10, 0x00, 0x40, 0x03,
    0x06, 0x08, 0x00, 0x80, 0x00, 0x00, 0x08, 0x00, 0x80, 0x00, 0xf8, 0x08, 0x01, 0x00, 0x00, 0x70,
    0x10, 0x02, 0x04, 0x00, 0x70, 0x60, 0x02, 0x08, 0x00, 0x01, 0x80, 0x04, 0x30, 0x01, 0x06, 0x00,
    0x08, 0x50, 0x09, 0x3a, 0x00, 0x10, 0x93, 0xf9, 0xca, 0x00, 0x21, 0x12, 0x09, 0x0a, 0x00, 0x42,
    0x24, 0x09, 0x0a, 0x00, 0x44, 0x48, 0x09, 0x0a, 0x00, 0x47, 0x4c, 0x09, 0x09, 0x00, 0x30, 0xa2,
    0x04, 0x84, 0x80, 0x0f, 0x1c, 0x03, 0x03, 0x00
  },

  { // 'jump_20', 40x24px
    0x00, 0x00, 0x0f, 0x8f, 0x00, 0x00, 0x00, 0x10, 0x50, 0x80, 0x00, 0x00, 0x20, 0x20, 0x40, 0x00,
    0x00, 0x43, 0x06, 0x20, 0x00, 0x00, 0x44, 0x89, 0x20, 0x00, 0x00, 0x49, 0x52, 0xa0, 0x00, 0x00,
    0x4b, 0x56, 0xa0, 0x00, 0x0f, 0x89, 0x52, 0xa0, 0x00, 0x30, 0x04, 0x89, 0x10, 0x00, 0x40, 0x03,
    0x06, 0x08, 0x00, 0x80, 0x00, 0x00, 0x08, 0x01, 0x00, 0x00, 0xf8, 0x08, 0x01, 0x00, 0x00, 0x70,
    0x10, 0x01, 0x02, 0x00, 0x70, 0x60, 0x01, 0x04, 0x00, 0x01, 0x80, 0x02, 0x08, 0x01, 0x06, 0x00,
    0x04, 0x30, 0x09, 0x3a, 0x00, 0x08, 0x53, 0xf9, 0xca, 0x00, 0x10, 0x89, 0x09, 0x0a, 0x00, 0x21,
    0x12, 0x09, 0x0a, 0x00, 0x21, 0x24, 0x09, 0x0a, 0x00, 0x11, 0xd3, 0x09, 0x09, 0x00, 0x0c, 0x28,
    0x84, 0x84, 0x80, 0x03, 0xc7, 0x03, 0x03, 0x00
  },

  { // 'jump_21', 40x24px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x8f, 0x00, 0x00, 0x00, 0x10, 0x50, 0x80, 0x00,
    0x00, 0x20, 0x20, 0x40, 0x00, 0x00, 0x43, 0x06, 0x20, 0x00, 0x00, 0x44, 0x89, 0x20, 0x00, 0x00,
    0x49, 0x52, 0xa0, 0x00, 0x00, 0x4b, 0x56, 0xa0, 0x00, 0x0f, 0x89, 0x52, 0xa0, 0x00, 0x30, 0x04,
    0x89, 0x10, 0x00, 0x40, 0x03, 0x06, 0x08, 0x00, 0x80, 0x00, 0x00, 0x08, 0x01, 0x00, 0x00, 0xf8,
    0x08, 0x01, 0x00, 0x00, 0x70, 0x10, 0x01, 0x02, 0x00, 0x70, 0x60, 0x01, 0x04, 0x00, 0x01, 0x80,
    0x02, 0x08, 0x01, 0x06, 0x00, 0x04, 0x30, 0x09, 0x3a, 0x00, 0x08, 0x53, 0xf9, 0xca, 0x00, 0x08,
    0x89, 0x09, 0x0a, 0x00, 0x08, 0x52, 0x09, 0x09, 0x00, 0x06, 0x39, 0x84, 0x84, 0x80, 0x01, 0x84,
    0x42, 0x42, 0x40, 0x00, 0x7b, 0x81, 0x81, 0x80
  },

  { // 'jump_22', 40x24px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x8f, 0x00, 0x00, 0x00, 0x10, 0x50, 0x80, 0x00,
    0x00, 0x20, 0x20, 0x40, 0x00, 0x00, 0x43, 0x06, 0x20, 0x00, 0x00, 0x44, 0x89, 0x20, 0x00, 0x00,
    0x49, 0x52, 0xa0, 0x00, 0x07, 0xcb, 0x56, 0xa0, 0x00, 0x08, 0x49, 0x52, 0xa0, 0x00, 0x30, 0x04,
    0x89, 0x10, 0x00, 0x40, 0x03, 0x06, 0x08, 0x00, 0x80, 0x00, 0x00, 0x08, 0x01, 0x00, 0x01, 0xfc,
    0x08, 0x01, 0x02, 0x00, 0xf8, 0x10, 0x01, 0x01, 0x00, 0x00, 0x60, 0x00, 0x81, 0x00, 0x01, 0x80,
    0x00, 0x42, 0x01, 0x06, 0x00, 0x00, 0x84, 0x09, 0x3a, 0x00, 0x01, 0x0c, 0x19, 0xca, 0x00, 0x01,
    0x13, 0xe9, 0x09, 0x00, 0x01, 0x0f, 0x24, 0xc4, 0xc0, 0x00, 0xc0, 0x92, 0x22, 0x20, 0x00, 0x3f,
    0xe1, 0xc1, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00
  }
};

void setup() {
  Serial.begin(9600);

  // Initialize OLED with I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Set pinmode for all buttons
  for (int i = 0; i < 4; i++) {
    pinMode(btns[i], INPUT);
  }
}

void loop() {

  boolean inputData[4];
  readInput(inputData);

  // Actions based on inputData, only one button will be handled per loop
  if (inputData[1]) { // Left button
    if (menuSelection == 0) {
      // Move to last item from first
      menuSelection = MENU_ITEM_COUNT - 1;
    } else {
      // Move to previous item in list
      menuSelection--;
    }
  } else if (inputData[2]) { // Right button
    if (menuSelection == MENU_ITEM_COUNT - 1) {
      // Move to first item from last
      menuSelection = 0;
    } else {
      // Move to previous item in list
      menuSelection++;
    }
  } else if (inputData[0]) { // Green button/select
    
  } else if (inputData[3]) { // Red button/deselect
    
  }

  // Get rid of the last loop's drawn graphics
  display.clearDisplay();

  drawMenu();
  drawPetIdle();

  //Ground
  display.drawLine(0, 63, 128, 63, SSD1306_WHITE);

  // Show this loop's graphics on the screen
  display.display();

}
