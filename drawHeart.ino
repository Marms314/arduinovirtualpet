void drawHeart(byte xPosHeart, byte yPosHeart, byte type) {
  switch (type) {
    case 1: // Full heart
      display.drawBitmap(xPosHeart, yPosHeart, full_heart_half_bmp, HEART_HALF_WIDTH, HEART_HEIGHT, SSD1306_WHITE);
      drawBitmapMirrored(xPosHeart + HEART_HALF_WIDTH, yPosHeart, full_heart_half_bmp, HEART_HALF_WIDTH, HEART_HEIGHT, SSD1306_WHITE);
      break;
    case 2: // Left empty heart
      display.drawBitmap(xPosHeart, yPosHeart, empty_heart_half_bmp, HEART_HALF_WIDTH, HEART_HEIGHT, SSD1306_WHITE);
      drawBitmapMirrored(xPosHeart + HEART_HALF_WIDTH, yPosHeart, full_heart_half_bmp, HEART_HALF_WIDTH, HEART_HEIGHT, SSD1306_WHITE);
      break;
    case 3: // Right empty heart
      display.drawBitmap(xPosHeart, yPosHeart, full_heart_half_bmp, HEART_HALF_WIDTH, HEART_HEIGHT, SSD1306_WHITE);
      drawBitmapMirrored(xPosHeart + HEART_HALF_WIDTH, yPosHeart, empty_heart_half_bmp, HEART_HALF_WIDTH, HEART_HEIGHT, SSD1306_WHITE);
      break;
    default: // Empty heart
      display.drawBitmap(xPosHeart, yPosHeart, empty_heart_half_bmp, HEART_HALF_WIDTH, HEART_HEIGHT, SSD1306_WHITE);
      drawBitmapMirrored(xPosHeart + HEART_HALF_WIDTH, yPosHeart, empty_heart_half_bmp, HEART_HALF_WIDTH, HEART_HEIGHT, SSD1306_WHITE);
      break;
  }
}
