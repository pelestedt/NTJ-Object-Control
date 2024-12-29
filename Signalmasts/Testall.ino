void Testall(){
Serial.print("Testar alla dioder, buslength  ");
Serial.println(Buslength);
for (int a=0; a<Buslength ; a++){
  pixels.setPixelColor(a, pixels.Color(0,0,0));
}
pixels.show();   
for (int a=0; a<Buslength ; a++){ 
  pixels.setPixelColor(a, pixels.Color(50,50,50));
  pixels.show();
  delay(10);
}
pixels.show();   
for (int a=0; a<Buslength ; a++){
  pixels.setPixelColor(a, pixels.Color(50,00,00));
  pixels.show();
  delay(10);
}
pixels.show();   
for (int a=0; a<Buslength ; a++){
  pixels.setPixelColor(a, pixels.Color(00,50,00));
  pixels.show();
  delay(10);
}
pixels.show();   
for (int a=0; a<Buslength ; a++){
  pixels.setPixelColor(a, pixels.Color(00,00,50));
  pixels.show();
  delay(10);
}
delay(500);
for (int a=0; a<Buslength ; a++){
  pixels.setPixelColor(a, pixels.Color(0,0,0));
  }
  pixels.show();
delay(10);
Serial.println("Test av alla dioder klar");
}
