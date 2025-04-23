#include "Arduino.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Defines and structures
//

#define Neopixelbus D4
#define Maxpixels 100
//boolean Night=false;
byte Aspect = 0;
byte intensityphase = 0;
unsigned long lastrun = millis();
byte Buslength = 0;
byte LEDserial = 0;
byte LEDcolor[Maxpixels];
byte newLEDcolor[Maxpixels];
byte LEDstate[Maxpixels];
byte setLED = 0;
byte currentstatus[Maxpixels];
byte Signalqty = 0;
int Fadevalue = 0;
byte go2off = 0;
int Blinkfrq = 5000;
byte Dayintensity = 15;
byte Nightintensity = 5;

String DCCaddress = "X12345,1";
String DCCdata = "1";
byte Blinkoff = 62;
byte Blinkramp = 33;
byte stepcount = 0;
int stepsteg = 1;
unsigned long last_intensity_check = 0;
byte set_intensity = 1;
//byte Brightness=Nightintensity;
int Intensityaddr = 0;
byte intensity = 20;
byte setIntensity = 20;
unsigned long lastintensitycheck = 0;

typedef struct
{
  int address;        // Address to respond to
  byte Signalaspect;  // State of output 1=on, 0=off
  byte Signaltype;    // Signal board type
  boolean Rotated;    // true=turned 180 deg, false=not rotated.

} DCCAccessoryAddress;
DCCAccessoryAddress gAddresses[32];


//Message decoding
String Data_from_decoder = "B00000,0";
int indata = 0;
int inadress = 0;
int lastindata;
int lastinadress;
String nyDCCdata;
String STASSID = "NTJ";
String STAPSK =  "NTJNTJ01";
unsigned int localPort = 8888;      // local port to listen on
//String inputString = "";         // a String to hold incoming data

// buffer for sending data
char packetBuffer[20 + 1]; //buffer to hold incoming packet,
char UDPincoming[20 + 1]; //buffer to hold incoming packet,
boolean UDPavailable;
//WiFiUDP Udp;

int port = 44;

byte msgno = 0;
//int basadress;
int Signaladress = 0;
byte Aspekt = 0;
byte nyaspekt = 0;
int rampupstart = 0;
int rampupend = 0;
int rampdownstart = 0;
int rampdownend = 0;
unsigned long timebetweensteps = 0;
#define fadesteps 100  //antalet steg i intensitet under en cykel
//#define bittimeout 5500 //min time between new signal aspect bit value

//Added for config from PC to EEPROM
#define adr_dayintensity 250
#define adr_nightintensity 251
#define adr_DCChigh 252
#define adr_DCClow 253
#define adr_periodhigh 254
#define adr_periodlow 255
#define adr_dark 256
#define adr_ramp 257
#define RGB_baseaddr 300
#define Aspects_baseaddr 100

String inputString = "PA11,12345,11,1$aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";  // a String to hold incoming data
String DCCdatainputString = "";
bool stringComplete = false;  // whether the string is complete
bool DCCdata_finns = false;
int Inaddr;
//int baseaddr[32];
byte configmode = 3;
unsigned long lastupdate = 0;

void (*resetFunc)(void) = 0;  // declare reset fuction at address 0

int parameter1;
int parameter2;
int parameter3;
int parameter4;

String in = "";

byte vitR;
byte vitG;
byte vitB;
byte redR;
byte redG;
byte redB;
byte greenR;
byte greenG;
byte greenB;
byte orangeR;
byte orangeG;
byte orangeB;

unsigned long starttime;
unsigned long endtime;
int ticlength;
int Calibrationtime;
int Calibrationdata;
int ticspersec = 1000;
byte newaspect[100];
byte setaspect[100];
#define startrampup 0
#define fullintensity 52
#define startrampdown 99
#define endrampdown 153

String Sid;
String Asp;
String Seq;
unsigned int answer;
int mastID[33]; 
int id;
byte setAsp[33];
byte asp;
unsigned intSeq;
