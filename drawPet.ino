void drawPet() {

  drawIdlePet();
  
}

void drawIdlePet() {
  if (jumpCount == 22){
    jumpCount = 0;
  } else {
    jumpCount++;
  }

  if (xPos >= 128){
    xPos = -24;
  } else {
    if(jumpCount > 5 && jumpCount < 17) {
      xPos += 3;
    } else if (jumpCount > 5 && jumpCount < 22){
      xPos++;
    }
  }

  int yPos = 30;
  display.drawBitmap(xPos, yPos, jumpBmp[jumpCount], 40, 24, SSD1306_WHITE);
}
