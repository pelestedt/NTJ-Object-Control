void every25ms() {
  long starttime = millis();
  // code to be repeated every 25ms
  if (setupperwingpos != actualupperwingPos) {
    if (actualupperwingPos > setupperwingpos) {
      actualupperwingPos--;
    }
    if (actualupperwingPos < setupperwingpos) {
      actualupperwingPos++;
    }
    wing1.write(actualupperwingPos);
      }
  if (setupperwingpos == actualupperwingPos) {
    wing1.detach();
  }

if (setlowerwingpos != actuallowerwingPos) {
    if (actualupperwingPos > setupperwingpos) {
      actuallowerwingPos--;
    }
    if (actuallowerwingPos < setlowerwingpos) {
      actuallowerwingPos++;
    }
    wing2.write(actuallowerwingPos);
  }
  if (setlowerwingpos == actuallowerwingPos) {
    wing2.detach();
  }

}
