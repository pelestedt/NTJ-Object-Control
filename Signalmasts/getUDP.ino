void getUDP() {

  //Check if there is UDP message to process
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    int n = Udp.read(UDPincoming, 20);
    UDPincoming[n] = 0;
    char inledning = UDPincoming[0];
    String Inledning(inledning);
    if (Inledning != "M") {
      goto bailout1;  // skip if invalid message
    }
    //Separate out id, pos and seq
    Sid = "";
    int t = 1;
    for (int c = 1; c < 9; c++) {
      Sid = Sid + UDPincoming[t];
      t++;
      if (UDPincoming[t] == 'A') {
        goto aspect;
      }
    }
aspect:
    t = t + 1;
    Asp = UDPincoming[t];
    Seq = "";
    t = t + 2;
    for (int c = 1; c < 9; c++) {
      Seq = Seq + UDPincoming[t];
      //Serial.println(Seq);
      t++;
      if (UDPincoming[t] == 0) {
        //Serial.println("null hittat");
        goto qend;
      }
    }
qend:
    inadress = Sid.toInt();
    indata = Asp.toInt();
  }
bailout1:
  answer = 0;
  for (int c = 1; c < 33; c++) {  //scan all IDs on this controler to see if it is here
    if (mastID[c] == id) {
      setAsp[c] = asp;
      answer = Seq.toInt();

      if (answer > 0) {
        // IPAddress broadCast = WiFi.localIP();
        // broadCast[3] = 255;
        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
        //Udp.beginPacket(broadCast, 8888);
        Udp.print(answer);
        Udp.endPacket();
        Serial.print("Skickat svar: ");
        Serial.println(answer);
        answer = 0;
        id = 0;
      }
    }
  }
}