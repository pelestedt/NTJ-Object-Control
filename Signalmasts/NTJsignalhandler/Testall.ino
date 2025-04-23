void Testall(){
//Serial.print("Testar alla dioder, buslength  ");
//Serial.println(Buslength);
int delaytime=10;
for (int a=0; a<Buslength ; a++){
  pixels.setPixelColor(a, pixels.Color(0,0,0));
}
pixels.show();   
for (int a=0; a<Buslength ; a++){ 
  pixels.setPixelColor(a, pixels.Color(50,50,50));
  pixels.show();
  delay(delaytime);
}
pixels.show();   
for (int a=0; a<Buslength ; a++){
  pixels.setPixelColor(a, pixels.Color(50,00,00));
  pixels.show();
  delay(delaytime);
}
pixels.show();   
for (int a=0; a<Buslength ; a++){
  pixels.setPixelColor(a, pixels.Color(00,50,00));
  pixels.show();
  delay(delaytime);
}
pixels.show();   
for (int a=0; a<Buslength ; a++){
  pixels.setPixelColor(a, pixels.Color(00,00,50));
  pixels.show();
  delay(delaytime);
}
delay(500);
for (int a=0; a<Buslength ; a++){
  pixels.setPixelColor(a, pixels.Color(0,0,0));
  }
  pixels.show();
delay(delaytime);
//Serial.println("Test av alla dioder klar");
}
