
byte motorpolaritet=1;
//byte currentdir=0;


#define PolarityA A7    //Relay for track polarity 
#define PolarityB  A1   //Relay for track polarity 
#define PWM    6      //Output for motor speed on 
#define Directionp 4   //Relay for motor direction 
#define Directionn A3   //Relay for motor direction 


byte minpwm = 10; //lägsta värde för motorutstyrning
int lo=0;
byte seekzero=0;
long prelcount = 0;
byte standstill=0;
/*Map till EEPROM

   50-51    DCC adress för vändskiva
   60-61    Helvarvsvärde
   90-150   Encodervärden för spårpositioner
   160-190  Spårpolariteter

   200-201  DCC adress till portar
   240-260  Servovinklar

   230      Motorpolaritet
   231      Minpwm

*/
#define baddr_V_DCC 50 //Basadresser för minnespositioner i EEPROM
#define baddr_V_VARV 60
#define baddr_V_POS 90
#define baddr_V_POL 220

#define baddr_D_DCC 230
#define baddr_D_POS 240

#define Motorpolaritet 300
#define Minpwm 310
#define Padel 320


String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
volatile long master_count = 0; // universal count
//volatile byte INTFLAG1 = 0; // interrupt status flag
byte Zeroset = 0;
unsigned long new_tablepos = 0;
unsigned long set_tablepos = 0;
byte set_polarity = 0;
unsigned long tablepos = 0;
byte sampletime=50;
int lastcurrentspeed;
unsigned long lastinc;
byte Save = 0;
volatile unsigned long lastpulse = 0;
volatile unsigned long pulsetime = 0;
volatile unsigned long lastpulsetime = 0;
unsigned long lasttic = 0;
unsigned long fullturn = 10692; //Pulses for one rev of turntable, is gear ratio * 10692 (10692 is #pulses for one rev of motor)
//11 pulsesunsigned int fullturn=0; per rev gear ratio 1:972 == 11*972 pulses per output axle rev.

unsigned long currentspeed;
int setspeed;

//long currentpos = 0;
int pwm; //styrvärde för motorspänning

long hastighet;
long sethastighet;
long lastcount;
byte  kalibreringsfas = 0;
int adjustm=350;

unsigned long lastsamp;
long newposition;
long newaddress;
long neworientation;

