void drawPet(int xPos, int yPos, String leftOrRight) {
  if (leftOrRight == "left") {
    drawEyes(xPos, yPos, true);
    drawEyes(xPos + 10, yPos, true);
  } else {
    drawEyes(xPos, yPos, false);
    drawEyes(xPos + 10, yPos, false);
  }
}

void drawEyes(int xPos, int yPos, boolean isLookingLeft) {
  if (isLookingLeft) {
    display.drawBitmap(xPos, yPos, eye_look_left_bmp, 8, 7, SSD1306_WHITE);
  } else {
    display.drawBitmap(xPos, yPos, eye_look_right_bmp, 8, 7, SSD1306_WHITE);
  }
}
