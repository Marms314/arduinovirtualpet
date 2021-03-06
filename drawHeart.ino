void drawHeart(int xPos, int yPos, heartType type) {
  switch (type) {
    case 1:
      display.drawBitmap(xPos, yPos, full_heart_half_bmp, HEART_HALF_WIDTH, HEART_HEIGHT, SSD1306_WHITE);
      drawBitmapMirrored(xPos + HEART_HALF_WIDTH, yPos, full_heart_half_bmp, HEART_HALF_WIDTH, HEART_HEIGHT, SSD1306_WHITE);
      break;
    case 2:
      display.drawBitmap(xPos, yPos, empty_heart_half_bmp, HEART_HALF_WIDTH, HEART_HEIGHT, SSD1306_WHITE);
      drawBitmapMirrored(xPos + HEART_HALF_WIDTH, yPos, full_heart_half_bmp, HEART_HALF_WIDTH, HEART_HEIGHT, SSD1306_WHITE);
      break;
    case 3:
      display.drawBitmap(xPos, yPos, full_heart_half_bmp, HEART_HALF_WIDTH, HEART_HEIGHT, SSD1306_WHITE);
      drawBitmapMirrored(xPos + HEART_HALF_WIDTH, yPos, empty_heart_half_bmp, HEART_HALF_WIDTH, HEART_HEIGHT, SSD1306_WHITE);
      break;
    default:
      display.drawBitmap(xPos, yPos, empty_heart_half_bmp, HEART_HALF_WIDTH, HEART_HEIGHT, SSD1306_WHITE);
      drawBitmapMirrored(xPos + HEART_HALF_WIDTH, yPos, empty_heart_half_bmp, HEART_HALF_WIDTH, HEART_HEIGHT, SSD1306_WHITE);
      break;
  }
}
