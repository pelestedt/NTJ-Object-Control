void every25ms() {
  long starttime = millis();
  // code to be repeated every 25ms


// hantera servo 1
  if (setPos1 != actualPos1) {
    actualPos1 = 20;  //set position to undefined
    if (0 == setPos1) {
      anglePos1--;
    }
    if (1 == setPos1) {
      anglePos1++;
    }
    points1.write(anglePos1);
  }
  if (0 == anglePos1) {
    actualPos1 = 0;
    points1.detach();
  }
  if (180 == anglePos1) {
    actualPos1 = 1;
    points1.detach();
  }

// hantera servo 2
  if (setPos2 != actualPos2) {
    actualPos2 = 20;  //set position to undefined
    if (0 == setPos2) {
      anglePos2--;
    }
    if (1 == setPos2) {
      anglePos2++;
    }
    points2.write(anglePos2);
  }
  if (0 == anglePos2) {
    actualPos2 = 0;
    points2.detach();
  }
  if (180 == anglePos2) {
    actualPos2 = 1;
    points2.detach();
  }

// hantera servo 3
  if (setPos3 != actualPos3) {
    actualPos3 = 20;  //set position to undefined
    if (0 == setPos3) {
      anglePos3--;
    }
    if (1 == setPos3) {
      anglePos3++;
    }
    points3.write(anglePos3);
  }
  if (0 == anglePos3) {
    actualPos3 = 0;
    points3.detach();
  }
  if (180 == anglePos3) {
    actualPos3 = 1;
    points3.detach();
  }

// hantera servo 4
  if (setPos4 != actualPos4) {
    actualPos4 = 20;  //set position to undefined
    if (0 == setPos2) {
      anglePos4--;
    }
    if (1 == setPos4) {
      anglePos4++;
    }
    points4.write(anglePos4);
  }
  if (0 == anglePos4) {
    actualPos4 = 0;
    points4.detach();
  }
  if (180 == anglePos4) {
    actualPos4 = 1;
    points4.detach();
  }


}
