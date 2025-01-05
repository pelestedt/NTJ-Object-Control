/*
   Config.h
*/
const char* PARAM_INPUT_1 = "Track";
const char* PARAM_INPUT_2 = "DCCaddress";
const char* PARAM_INPUT_3 = "pos0";
const char* PARAM_INPUT_4 = "pos1";

// HTML web page to handle 2 input fields

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <br>
  <br>
  <br>
  <br>
  <form action="/get">
    Track: <input type="text" name="Track">
     <br>
     <br>
    DCC address: <input type="text" name="DCCaddress">
     <br>
      <br>
    Encodervalue pos 0: <input type="text" name="pos0">
      <br>
      <br>
    Encodervalue pos 1 <input type="text" name="pos1">
    <br>
    <br>
   <input type="submit" value="Lagra">
  </form><br>
</body></html>)rawliteral";

/*

//https://htmlreference.io/element/form/

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <br>
  <br>
  <br>
  <br>
  <form action="/get">
    Track: <input type="text" name="Track">
   <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    DCC address: <input type="text" name="DCCaddress">
   <input type="submit" value="Submit">
  </form><br>
   <form action="/get">
    Encodervalue pos 0: <input type="text" name="pos0">
   <input type="submit" value="Submit">
  </form><br>
   <form action="/get">
    Encodervalue pos 1 <input type="text" name="pos1">
   <input type="submit" value="Submit">
  </form><br>
</body></html>)rawliteral";
*/





//void notFound(AsyncWebServerRequest* request) {   request->send(404, "text/plain", "Not found");}
//Node configuration

//#define VxID  999  //DCC address
int VxID;
String HostID;

String STASSID = "NTJ";
String STAPSK = "NTJNTJ01";

int packetSize = 0;
String Configstring = "";  // a String to hold incoming data
boolean configmode = false;
int Inaddr;
String Configuration;
byte CurveDirection = 0;
int padellength=162;

//getUDPdata declarations
unsigned int localPort = 8888;  // local port to listen on
String inputString = "";        // a String to hold incoming data

// buffer for sending data
char packetBuffer[20 + 1];  //buffer to hold incoming packet,
char UDPincoming[20 + 1];   //buffer to hold incoming packet,
boolean UDPavailable;
WiFiUDP Udp;

int port = 44;


//define points ID in DCC++EX, the number that represents the points on this controller


//Define the outputs on the Arduino that controls the outputs setting the points
#define FWD D6
#define REW D7
//#define CHA D1  //Encoder channel A Encoder channel B A6 and A7 på Nano fungerar inte som dig in.
//#define CHB D2  //Encoder channel B

#define CHA D2  //Encoder channel A Encoder channel B A6 and A7 på Nano fungerar inte som dig in.
#define CHB D1  //Encoder channel B



#define Zeropos D4
#define creepspeed 6000  //micro seconds between pulses
#define slowspeed 4000
#define halfspeed 3000
#define mediumspeed 2000
#define fullspeed 500
#define Medurs 1
#define Moturs 0
#define Pos 1
#define Neg 0
#define Adjust 315

volatile unsigned long lastpulse = 0;
volatile unsigned long pulsetime = 0;
volatile unsigned long lastpulsetime = 0;
volatile long master_count = 0;  // universal count
int pwm;
int setspeed = slowspeed;
byte Direction;
int currentspeed;
byte seekzero = 0;
long new_tablepos = 0;
long set_tablepos = 0;
byte sampletime = 50;
unsigned long lastsamp;
long lastcount;
byte standstill = 0;
byte minpwm = 70;  //lägsta värde för motorutstyrning
byte currentdir = 0;
long prelcount = 0;
//long fullturn = 10692; //Pulses for one rev of turntable, is gear ratio * 10692 (10692 is #pulses for one rev of motor)
long fullturn = 10652; //Pulses for one rev of turntable, is gear ratio * 10692 (10692 is #pulses for one rev of motor)
//int paddlelength;
long distance;
long halfturn = 5346;
byte Rotation;
byte Lastrotation;
int adjustm=0;
//long position[10][10][10];


//Main loop declarationsInitialDCCaddress

int id = 9999;
String Sid = "256";
int pos = 0;
String Spos = "0";

bool stringComplete = false;  // whether the string is complete
unsigned long answer = 0;
unsigned long attstarttime;
String Seq;

WiFiServer server(44);
WiFiClient client;

byte kalibreringsfas;

int Track = 0;

const PROGMEM long position[10][3] = 
{
  { 100, 200, 5546 },
  { 101, 1336, 6682 },
  { 102, 2673, 8019 },
  { 103, 3118, 8464 },
  { 104, 3564, 8910 },
  { 105, 4009, 9355 },
  { 106, 4455, 9801 },
  { 107, 4900, 10246 },
  { 108, 5346, 1 },
  { 109, 5791, 445 },
};
