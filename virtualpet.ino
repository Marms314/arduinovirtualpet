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
#define MENU_ITEM_COUNT 4

// Heart graphics size values
#define HEART_HEIGHT 13
#define HEART_HALF_WIDTH 8

// Enums for use with drawHeart function
enum heartType {
  FULL = 1,
  LEFT_EMPTY = 2,
  RIGHT_EMPTY = 3,
  EMPTY = 4
};

// Create button arrays. Order is: green, left, right, red
int btns[] = {2, 3, 4, 5};
int btnReads[] = {0, 0, 0, 0};
int prevBtnReads[] = {0, 0, 0, 0};
int menuSelection = 0;
boolean isYes[] = {false, false, false, false, false, false, false, false};


// Bitmaps for graphics
static const unsigned char PROGMEM empty_heart_left_bmp[] =
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

static const unsigned char PROGMEM empty_heart_right_bmp[] =
{ B00011100,
  B00100010,
  B01000001,
  B10000001,
  B00000001,
  B00000001,
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B10000000
};

static const unsigned char PROGMEM full_heart_left_bmp[] =
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

static const unsigned char PROGMEM full_heart_right_bmp[] =
{ B00011100,
  B00111110,
  B01111111,
  B11111111,
  B11111111,
  B11111111,
  B11111110,
  B11111100,
  B11111000,
  B11110000,
  B11100000,
  B11000000,
  B10000000
};

static const unsigned char PROGMEM apple_bmp[] =
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

static const unsigned char PROGMEM eye_look_right_bmp[] =
{ B00001100,
  B00010010,
  B00100101,
  B00101101,
  B00100101,
  B00010010,
  B00001100
};

static const unsigned char PROGMEM eye_look_left_bmp[] =
{ B00001100,
  B00010010,
  B00101001,
  B00101101,
  B00101001,
  B00010010,
  B00001100
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
      menuSelection = MENU_ITEM_COUNT;
    } else {
      // Move to previous item in list
      menuSelection--;
    }
  } else if (inputData[2]) { // Right button
    if (menuSelection == MENU_ITEM_COUNT) {
      // Move to first item from last
      menuSelection = 0;
    } else {
      // Move to previous item in list
      menuSelection++;
    }
  } else if (inputData[0]) { // Green button/select
    isYes[menuSelection] = true;
  } else if (inputData[3]) { // Red button/deselect
    isYes[menuSelection] = false;
  }

  // Get rid of the last loop's drawn graphics
  display.clearDisplay();
  
  drawMenu();

  drawPet(50, 20, "left");
  drawPet(50, 30, "right");

  // Show this loop's graphics on the screen
  display.display();

}
