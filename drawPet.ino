void drawPet() {

  drawJumpingRightPet();

}

void drawJumpingRightPet() {
  if (jumpCount == 22) { // Move through jump animation frames
    jumpCount = 0;
  } else {
    jumpCount++;
  }

  if (xPos >= 128) { // Reset jump animation once pet is offscreen
    xPos = -24;
    yPos = 40;
    jumpCount = 0;
  } else { // Calculate xPos based on jump animation frame
    if (jumpCount > 4 && jumpCount < 17) {
      xPos += 2;
    } else if (jumpCount > 3 && jumpCount < 22) {
      xPos++;
    }
  }

  if (jumpCount > 7 && jumpCount < 15) { // Calculate yPos based on jump animation frame
    yPos--;
  } else if (jumpCount > 15 && jumpCount < 18) {
    yPos++;
  } else if (jumpCount == 19) {
    yPos += 3;
  } else if (jumpCount == 20) {
    yPos += 2;
  } 

  display.drawBitmap(xPos, yPos, jumpBmp[jumpCount], 40, 24, SSD1306_WHITE);
  display.drawLine(0, 63, 128, 63, SSD1306_WHITE);
}
