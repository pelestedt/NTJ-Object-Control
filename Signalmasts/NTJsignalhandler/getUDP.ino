void getUDP() {
  //Check if there is UDP message to process
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    int n = Udp.read(UDPincoming, 20);
    UDPincoming[n] = 0;
    Serial.println(UDPincoming);
    char inledning = UDPincoming[0];
    String Inledning(inledning);
    if (Inledning != "S") {
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
    //testa om inkomen adress är till signal på denna dekoder
    for (int t = 0; t < 32; t++) {
      if (gAddresses[t].address == inadress) {
        gAddresses[t].Signalaspect = indata;
        Serial.print("Signal ");
        Serial.print(inadress);
        Serial.print(" Satt till ");
        Serial.println(indata);
        inadress = 0;
        indata = 0;
        Sid = "";
        Asp = "";
        goto bailout1;
      }
    }
  }
bailout1:
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
    Seq = "";
  }
}
