void every25ms() {
  //long starttime = millis();
  // code to be repeated every 25ms

  if (setPos1 != actualPos1) {
    if (actualPos1 < setPos1) actualPos1++;
    if (actualPos1 > setPos1) actualPos1--;
    Door1.write(actualPos1);
    Serial.println(actualPos1);
  }
  //***************************************
  if (setPos2 != actualPos2) {
    if (actualPos2 < setPos2) actualPos2++;
    if (actualPos2 > setPos2) actualPos2--;
    Door2.write(actualPos2);
  }
  if (setPos3 != actualPos3) {
    if (actualPos3 < setPos3) actualPos3++;
    if (actualPos3 > setPos3) actualPos3--;
    Door3.write(actualPos3);
  }
  if (setPos4 != actualPos4) {
    if (actualPos4 < setPos4) actualPos4++;
    if (actualPos4 > setPos4) actualPos4--;
    Door4.write(actualPos4);
  }
  if (setPos5 != actualPos5) {
    if (actualPos5 < setPos5) actualPos5++;
    if (actualPos5 > setPos5) actualPos5--;
    Door5.write(actualPos5);
  }
  if (setPos1 == actualPos1) Door1.detach();
  if (setPos2 == actualPos2) Door2.detach();
  if (setPos3 == actualPos3) Door3.detach();
  if (setPos4 == actualPos4) Door4.detach();
  if (setPos5 == actualPos5) Door5.detach();
}
