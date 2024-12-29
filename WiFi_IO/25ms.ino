void every25ms() {

  // code to be repeated every 25ms
  for (int r = 1; r < 9; r++)
  {
    if (setPos[r] == 1)
    {
      // to 1 position (Output on)
      digitalWrite(IOpin[r], HIGH);
      setPos[r] = 2;
    }
    //from 1 to 0 position (Output off)
    if (setPos[r] == 0)
    {
      digitalWrite(IOpin[r], LOW);
      setPos[r] = 2;
    }
  }
}
