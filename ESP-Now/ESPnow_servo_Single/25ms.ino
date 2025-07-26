void every25ms() {
  long starttime = millis();
  // code to be repeated every 25ms

  if (setPos != actualPos) {
    actualPos = 20;  //set position to undefined
    if (0 == setPos) {
      anglePos--;
    }
    if (1 == setPos) {
      anglePos++;
    }
    points1.write(anglePos);
  }
  if (0 == anglePos) {
    actualPos = 0;
    points1.detach();
  }
  if (180 == anglePos) {
    actualPos = 1;
    points1.detach();
  }
}
