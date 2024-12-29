/*
   Config.h
*/

String Configstring = "";         // a String to hold incoming data
boolean configmode = false;
int Inaddr;
String Configuration;

//getUDPdata declarations

String STASSID = "NTJ";
String STAPSK =  "NTJNTJ01";
int packetSize=0;

unsigned int localPort = 8888;      // local port to listen on
String inputString = "";         // a String to hold incoming data

// buffer for sending data
char packetBuffer[20 + 1]; //buffer to hold incoming packet,
char UDPincoming[20 + 1]; //buffer to hold incoming packet,
boolean UDPavailable;
WiFiUDP Udp;

int port = 44;


//define points ID in DCC++EX, the number that represents the points on this controller
#define Out1  1
#define Out2  2
#define Out3  3
#define Out4  4
#define Out5  5
#define Out6  6
#define Out7  7
#define Out8  8

//Define the outpust on the Arduino that controls the outputs setting the points
#define Outp1  D0
#define Outp2  D1
#define Outp3  D2
#define Outp4  D3
#define Outp5  D4
#define Outp6  D5
#define Outp7  D6
#define Outp8  D7
