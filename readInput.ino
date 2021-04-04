// Takes readings of all the buttons and updates all related values accordingly

void readInput(boolean input[4]) {
  // Read button values
  for (int i = 0; i < 4; i++) {
    btnReads[i] = digitalRead(btns[i]);
    input[i] = btnReads[i] > prevBtnReads[i];
    prevBtnReads[i] = btnReads[i];
  }
}

// Helpful function for checking any of the button array values in serial
// delay() leaves enough time between loops to allow serial to be read

void logButtons(int btnArr[], String title) {
  Serial.println(title);
  Serial.print("Green button: ");
  Serial.println(btnArr[0]);
  Serial.print("Left button: ");
  Serial.println(btnArr[1]);
  Serial.print("Right button: ");
  Serial.println(btnArr[2]);
  Serial.print("Red button: ");
  Serial.println(btnArr[3]);
  Serial.println("");
  delay(500);
}
