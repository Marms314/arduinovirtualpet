void drawMenu() {
  for (int i = 0; i < MENU_ITEM_COUNT ; i++) {
    int xPos = i * MENU_ITEM_WIDTH;
    if (isYes[i]) {
      drawHeart(xPos, 0, RIGHT_EMPTY);
    } else {
      drawHeart(xPos, 0, LEFT_EMPTY);
    }
  }

  // Underlines the current selection in the menu
  display.drawLine(menuSelection * MENU_ITEM_WIDTH, 15, menuSelection * MENU_ITEM_WIDTH + MENU_ITEM_WIDTH - 1, 15, SSD1306_WHITE);
}

void drawApple(int xPos, int yPos) {
  display.drawBitmap(xPos, yPos, apple_bmp, MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT, SSD1306_WHITE);
}
