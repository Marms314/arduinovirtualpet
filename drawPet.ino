void drawPet() {

  drawPetIdle();

}

// Draws pet jumping from one side of the screen to the other
void drawPetIdle() {
  // Reset jump animation once pet is offscreen
  if (xPos >= 129 && isGoingRight) { //Set up to go to the right
    xPos = 128;
    yPos = 40;
    jumpFrame = 0;
    isGoingRight = false;
  } else if (xPos <= -40 && !isGoingRight) { //Set up to go to the left
    xPos = -38;
    yPos = 40;
    jumpFrame = 0;
    isGoingRight = true;
  }

  // Allow pet to rest between jumps
  if (petIdleCount == 0 || petIdleCount == 1 || petIdleCount == 12 || petIdleCount == 25) {
    drawPetJump();
  } else {
    drawPetRest();
  }

  // Each idle animation returns to frame 0 when done
  // Use reaching frame 0 as the time to move to the next animation
  if (jumpFrame == 0) {
    petIdleCount++;
  }

  // Resets idle 
  if (petIdleCount == 30) {
      petIdleCount = 0;
    }
}

// Draws pet standing still, but moving slightly up and down to emulate breathing
void drawPetRest() {

  if (petRestCount == 2) { // Slows down the rest animation
    petRestCount = 0;
    if (jumpFrame == 2) { // Move through the first few jump animation frames
      jumpFrame = 0;
    } else {
      jumpFrame++;
    }
  } else {
    petRestCount++;
  }
  
  // Match current movement direction
  if (isGoingRight) {
    display.drawBitmap(xPos, yPos, jumpBmp[jumpFrame], 37, 24, SSD1306_WHITE);
  } else if (!isGoingRight) {
    drawBitmapMirrored(xPos, yPos, jumpBmp[jumpFrame], 37, 24, SSD1306_WHITE);
  }
}

// Makes pet jump and moves their position
void drawPetJump() {
  if (jumpFrame == 22) { // Move through jump animation frames
    jumpFrame = 0;
  } else {
    jumpFrame++;
  }

  // Calculate yPos based on jump animation frame
  if (jumpFrame > 7 && jumpFrame < 15) {
    yPos--;
  } else if (jumpFrame > 15 && jumpFrame < 18) {
    yPos++;
  } else if (jumpFrame == 19) {
    yPos += 3;
  } else if (jumpFrame == 20) {
    yPos += 2;
  }

  // Match current movement direction
  if (isGoingRight) {
    if (jumpFrame > 4 && jumpFrame < 17) { // Move frog to the right
      xPos += 2;
    } else if (jumpFrame > 3 && jumpFrame < 22) {
      xPos++;
    }
    display.drawBitmap(xPos, yPos, jumpBmp[jumpFrame], 37, 24, SSD1306_WHITE);
  } else {
    if (jumpFrame > 4 && jumpFrame < 17) { // Move frog to the left
      xPos -= 2;
    } else if (jumpFrame > 3 && jumpFrame < 22) {
      xPos--;
    }
    drawBitmapMirrored(xPos, yPos, jumpBmp[jumpFrame], 37, 24, SSD1306_WHITE);
  }
}
