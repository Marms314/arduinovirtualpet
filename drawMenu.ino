void drawMenu() {
  for (byte i = 0; i < MENU_ITEM_COUNT ; i++) {
    byte xPos = i * (MENU_ITEM_WIDTH + 1);

    switch (i) {
      case 0: // Print Apple for feed
        drawApple(xPos, 0);
        break;
      case 1: // Print glove for fight
        drawGlove(xPos, 0);
        break;
      case 2: // Print heart for stats
        drawHeart(xPos, 0, 1);
        break;
      //default: // Print Nothing
        //break;
    }
  }

  // Underlines the current selection in the menu
  display.drawLine(menuSelection * (MENU_ITEM_WIDTH + 1), 15, menuSelection * (MENU_ITEM_WIDTH + 1) + MENU_ITEM_WIDTH - 1, 15, SSD1306_WHITE);
}

void drawApple(byte xPosApple, byte yPosApple) {
  display.drawBitmap(xPosApple, yPosApple, apple_bmp, MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT, SSD1306_WHITE);
}

void drawGlove(byte xPosGlove, byte yPosGlove) {
  display.drawBitmap(xPosGlove, yPosGlove, boxing_glove_bmp, MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT, SSD1306_WHITE);
}
