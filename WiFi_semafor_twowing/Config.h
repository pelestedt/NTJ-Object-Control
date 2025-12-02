
/*
   Config.h
*/

//Define the outpust on the Arduino that controls the outputs setting the points
#define UpperWing D1              //Digital output to control servo
#define LowerWing D2              //Digital output to control servo
#define InitialDCCaddress 999  //DCC address assigned to controller by default
#define UpperStop 65
#define UpperGo 0
#define LowerSlow 120
#define LowerFull 175
/*
#define UpperStop 70
#define UpperGo 0
#define LowerSlow 90
#define LowerFull 70
*/

String STASSID = "NTJ";        //Your network name (SSID)
String STAPSK = "NTJNTJ01";    //Network password
const char* OTApassword = "NTJNTJ01";     //Password to update software OTA




const char* PARAM_INPUT_1 = "DCCaddress";

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
    DCC address: <input type="text" name="DCCaddress">
   <input type="submit" value="Submit">
  </form><br>
   </body></html>)rawliteral";

//void notFound(AsyncWebServerRequest* request) {   request->send(404, "text/plain", "Not found");}
//Node configuration

//#define VxID  999  //DCC address 
int SigID;
String HostID;



int packetSize = 0;
String Configstring = "";  // a String to hold incoming data
boolean configmode = false;
int Inaddr;
String Configuration;


//getUDPdata declarations
unsigned int localPort = 8888;  // local port to listen on
String inputString = "";        // a String to hold incoming data

// buffer for sending data
//char packetBuffer[20 + 1];  //buffer to hold incoming packet,
char UDPincoming[20 + 1];   //buffer to hold incoming packet,
//boolean UDPavailable;
WiFiUDP Udp;

int port = 44;

//Main loop declarationsInitialDCCaddress
unsigned long last25run = 0;
int id = 9999;
String Sid = "256";
int pos = 0;
//String Spos = "0";
String Saspekt= "0";

bool stringComplete = false;  // whether the string is complete
byte SignalID = SigID;
byte setupperwingpos;
byte actualupperwingPos;
byte setlowerwingpos;
byte actuallowerwingPos;
byte aspekt = 0;

unsigned long answer = 0;
String Seq;

WiFiServer server(44);
WiFiClient client;



 
