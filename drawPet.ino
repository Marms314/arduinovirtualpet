void drawPet() {

  drawIdlePet();

}

void drawIdlePet() {
  // Reset jump animation once pet is offscreen
  if (xPos >= 129 && isGoingRight) { //Set up to go to the right
    xPos = 128;
    yPos = 40;
    jumpCount = 0;
    isGoingRight = false;
  } else if (xPos <= -40 && !isGoingRight) { //Set up to go to the left
    xPos = -38;
    yPos = 40;
    jumpCount = 0;
    isGoingRight = true;
  }

  if (!isGoingRight) {
    drawJumpingLeftPet();
  } else if (isGoingRight) {
    drawJumpingRightPet();
  }
}

void drawJumpingRightPet() {
  if (jumpCount == 22) { // Move through jump animation frames
    jumpCount = 0;
  } else {
    jumpCount++;
  }

  if (jumpCount > 4 && jumpCount < 17) {
    xPos += 2;
  } else if (jumpCount > 3 && jumpCount < 22) {
    xPos++;
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

void drawJumpingLeftPet() {
  if (jumpCount == 22) { // Move through jump animation frames
    jumpCount = 0;
  } else {
    jumpCount++;
  }

  if (jumpCount > 4 && jumpCount < 17) {
    xPos -= 2;
  } else if (jumpCount > 3 && jumpCount < 22) {
    xPos--;
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

  drawBitmapMirrored(xPos, yPos, jumpBmp[jumpCount], 40, 24, SSD1306_WHITE);
  display.drawLine(0, 63, 128, 63, SSD1306_WHITE);
}
