
/*
   Config.h
*/

//Define the outpust on the Arduino that controls the outputs setting the points

String STASSID = "NTJ";        //Your network name (SSID)
String STAPSK = "NTJNTJ01";    //Network password
const char* OTApassword = "NTJNTJ01";     //Password to update software OTA

byte sensorport[9]={A0,D1,D2,D3,D4,D5,D6,D7,D8};
byte SensorID[9]={0,1,2,3,4,5,6,7,8};
byte currentstatus[9];
IPAddress bCast;



const char* PARAM_INPUT_1 = "IDsensor1";
const char* PARAM_INPUT_2 = "IDsensor2";
const char* PARAM_INPUT_3 = "IDsensor3";
const char* PARAM_INPUT_4 = "IDsensor4";
const char* PARAM_INPUT_5 = "IDsensor5";
const char* PARAM_INPUT_6 = "IDsensor6";
const char* PARAM_INPUT_7 = "IDsensor7";
const char* PARAM_INPUT_8 = "IDsensor8";

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
    D1, ID Sensor 1, nuvarande ID %ID1%: <input type="text" name="IDsensor1">
   <input type="submit" value="Submit">
  </form><br>
<form action="/get">
    D2, ID Sensor 2, nuvarande ID %ID2%: <input type="text" name="IDsensor2">
   <input type="submit" value="Submit">
  </form><br>
<form action="/get">
    D3, ID Sensor 3, nuvarande ID %ID3%: <input type="text" name="IDsensor3">
   <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    D4, ID Sensor 4, nuvarande ID %ID4%: <input type="text" name="IDsensor4">
   <input type="submit" value="Submit">
  </form><br>
   <form action="/get">
    D5, ID Sensor 5, nuvarande ID %ID5%, <input type="text" name="IDsensor5">
   <input type="submit" value="Submit">
  </form><br>
<form action="/get">
    D6, ID Sensor 6, nuvarande ID %ID6%: <input type="text" name="IDsensor6">
   <input type="submit" value="Submit">
  </form><br>
<form action="/get">
    D7, ID Sensor 7, nuvarande ID %ID7%: <input type="text" name="IDsensor7">
   <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    D8, ID Sensor 8, nuvarande ID %ID8%: <input type="text" name="IDsensor8">
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

bool stringComplete = false;  // whether the string is complete

unsigned long answer = 0;
String Seq;

WiFiServer server(44);
WiFiClient client;


// Replaces placeholder with stored values
String processor(const String& var) {
  //ersätt A1 med aktuell tid
  String parameter = "12";  
  String presentid;
  //String nutid = String(Year) ;
  if (var == "ID1") {
    parameter = String(SensorID[1]);
    return parameter;
  }
  if (var == "ID2") {
    parameter = String(SensorID[2]);
    return parameter;
  }
  if (var == "ID3") {
    parameter = String(SensorID[3]);
    return parameter;
  }
  if (var == "ID4") {
    parameter = String(SensorID[4]);
    return parameter;
  }
   if (var == "ID5") {
    parameter = String(SensorID[5]);
    return parameter;
  }
  if (var == "ID6") {
    parameter = String(SensorID[6]);
    return parameter;
  }
  if (var == "ID7") {
    parameter = String(SensorID[7]);
    return parameter;
  }
  if (var == "ID8") {
    parameter = String(SensorID[8]);
    return parameter;
  }

  return String();
}
 
