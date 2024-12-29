//
//Definition of how many LEDs are in each aspect
//
const PROGMEM byte numleds[11] = {0, 2, 3, 2, 3, 4, 5, 4, 7, 3, 1}; //Signal board type 0 not used
//
// Signal board color definitions, LED 0 not used. LED 1 is the top (left to right) LED.
// color[aspect][LED]
//Color are defined as; 1== red, 2 == green, 3 == white, 0 = off, 4 == Bright yellow, 9 == Changes from red to green
// See document Signalaspekter definition v2.2.ppt for definitions of signals and aspects
#define off 0
#define red 1
#define green 2
#define white 3
#define yellow 4
#define red_green 9

//Stored in program memory to save RAM
const PROGMEM byte  color[11][8] = {
  {0, 0},                                           //använd ej
  {green, white},                                   //Signaltyp 1
  {green, white, green},                            //Signaltyp 2
  {green, red},                                     //Signaltyp 3
  {green, red, green},                              //Signaltyp 4
  {green, red, green, white},                       //Signaltyp 5
  {green, red, green, white, green},                //Signaltyp 6
  {white, white, white, white},                     //Signaltyp 7
  {red, white, white, white, white, green, green},  //Signaltyp 8
  {yellow, yellow, yellow},                         //Signaltyp 9
  {red_green}                                       //Signaltyp 10
};
//
// Aspect definitions for each signal board, aspect 0 the most restrictive according to NMRA standards
// in the order [board type] [aspect] [led] where the status of the led is 0=off, 1= on 2=blinking
// During operation there are also the statuses 3=being turned on and 4= being turned off to be
// able to syncronize fade in and out
//
#define off 0
#define on 1
#define blinking 2

const PROGMEM byte aspect[11][9][8]  =
{
  {
    {0, 0}            //Används ej
  },
  {                           //Aspekter för
    {blinking, off},                   //Signaltyp 1
    {off, blinking}
  },
  {
    {blinking, off, off},                //Signaltyp 2
    {off, blinking, off},
    {blinking, off, blinking}
  },
  {
    {off, on},                   //Signaltyp 3
    {on, off}
  },
  {
    {off, on, off},                //Signaltyp 4
    {on, off, off},
    {on, off, on}
  },
  {
    {off, on, off, off},             //Signaltyp 5
    {on, off, off, off},
    {on, off, on, off},
    {on, off, blinking, off},
    {on, off, off, blinking}
  },
  {
    {off, on, off, off, off},           //Signaltyp 6
    {on, off, off, off, off},
    {on, off, on, off, off},
    {on, off, blinking, off, off},
    {on, off, off, blinking, off},
    {on, off, blinking, off, blinking},
    {on, off, on, off, on}
  },
  {
    {off, off, on, on},              //Signaltyp 7
    {on, off, on, off},
    {off, on, on, off},
    {on, off, off, on}
  },
  {
    {on, off, off, on, on, off, off },    //Signaltyp 8
    {on, off, on, off, on, off, off },
    {on, on, off, off, on, off, off },
    {on, off, on, on, off, off, off },
    {off, off, on, off, on, off, on },
    {off, off, on, off, on, on, off },
    {off, off, on, off, on, off, blinking },
    {off, off, on, off, on, blinking, off }
  },
 {
    {off, on, on},                  //Signaltyp 9
    {on, off, on}
  },
{
    {on},                        //Signaltyp 10
    {on},
    {blinking}
  }
};
