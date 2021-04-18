// Draws pet jumping from one side of the screen to the other
// Allows the buttons and menu to still be used
void drawPetIdle() {
  // Reset jump animation once pet is offscreen
  if (xPosPet >= 129 && isFacingRightPet) { //Set up to go to the right
    xPosPet = 128;
    yPosPet = 40;
    jumpFramePet = 0;
    isFacingRightPet = false;
  } else if (xPosPet <= -40 && !isFacingRightPet) { //Set up to go to the left
    xPosPet = -38;
    yPosPet = 40;
    jumpFramePet = 0;
    isFacingRightPet = true;
  }

  // Allow pet to rest between jumps
  if (petIdleCount == 0 || petIdleCount == 1 || petIdleCount == 12 || petIdleCount == 25) {
    drawPetJump();
  } else {
    drawPetRest();
  }

  // Each idle animation returns to frame 0 when done
  // Use reaching frame 0 as the time to move to the next animation
  if (jumpFramePet == 0) {
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
    if (jumpFramePet == 2) { // Move through the first few jump animation frames
      jumpFramePet = 0;
    } else {
      jumpFramePet++;
    }
  } else {
    petRestCount++;
  }
  
  // Match current movement direction
  if (isFacingRightPet) {
    display.drawBitmap(xPosPet, yPosPet, jumpBmp[jumpFramePet], 37, 24, SSD1306_WHITE);
  } else if (!isFacingRightPet) {
    drawBitmapMirrored(xPosPet, yPosPet, jumpBmp[jumpFramePet], 37, 24, SSD1306_WHITE);
  }
}

// Makes pet jump and moves their position
void drawPetJump() {
  if (jumpFramePet == 22) { // Move through jump animation frames
    jumpFramePet = 0;
  } else {
    jumpFramePet++;
  }

  // Calculate yPosPet based on jump animation frame
  if (jumpFramePet > 7 && jumpFramePet < 15) {
    yPosPet--;
  } else if (jumpFramePet > 15 && jumpFramePet < 18) {
    yPosPet++;
  } else if (jumpFramePet == 19) {
    yPosPet += 3;
  } else if (jumpFramePet == 20) {
    yPosPet += 2;
  }

  // Match current movement direction
  if (isFacingRightPet) {
    if (jumpFramePet > 4 && jumpFramePet < 17) { // Move frog to the right
      xPosPet += 2;
    } else if (jumpFramePet > 3 && jumpFramePet < 22) {
      xPosPet++;
    }
    display.drawBitmap(xPosPet, yPosPet, jumpBmp[jumpFramePet], 37, 24, SSD1306_WHITE);
  } else {
    if (jumpFramePet > 4 && jumpFramePet < 17) { // Move frog to the left
      xPosPet -= 2;
    } else if (jumpFramePet > 3 && jumpFramePet < 22) {
      xPosPet--;
    }
    drawBitmapMirrored(xPosPet, yPosPet, jumpBmp[jumpFramePet], 37, 24, SSD1306_WHITE);
  }
}
