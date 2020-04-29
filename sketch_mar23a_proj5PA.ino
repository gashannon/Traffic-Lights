//Garrett Shannon Project 5
#define westButton 3
#define eastButton 13
#define westRed 2
#define westYellow 1
#define westGreen 0
#define eastRed 12
#define eastYellow 11
#define eastGreen 10
#define eastpedlightBlue 9
#define eastpedlightGreen 8
#define westpedlightBlue 7
#define westpedlightGreen 6

#define yellowBlinkTime 500
boolean trafficWest = true;  // west = true, east = false w
boolean trafficPed = false; //west = true, east = false
int  flowTime  = 10000; // amount of time to let traffic flow x
int changeDelay = 2000;

void setup() {

  // setup digital I/O pins
  pinMode(westButton, INPUT);
  pinMode(eastButton, INPUT);
  pinMode(westRed, OUTPUT);
  pinMode(westYellow, OUTPUT);
  pinMode(westGreen, OUTPUT);
  pinMode(eastRed, OUTPUT);
  pinMode(eastYellow, OUTPUT);
  pinMode(eastGreen, OUTPUT);
  pinMode(eastpedlightBlue, OUTPUT);
  pinMode(westpedlightGreen, OUTPUT);
  pinMode(eastpedlightGreen, OUTPUT);
  pinMode(westpedlightBlue, OUTPUT);

  // set initial state for lights - west side is green first
  digitalWrite(westRed,  LOW);
  digitalWrite(westYellow, LOW);
  digitalWrite(westGreen, HIGH);
  digitalWrite(eastRed, HIGH);
  digitalWrite(eastYellow, LOW);
  digitalWrite(eastGreen, LOW);
  digitalWrite(eastpedlightBlue, HIGH);
  digitalWrite(westpedlightGreen, HIGH);
  digitalWrite(eastpedlightGreen, LOW);
  digitalWrite(westpedlightBlue, LOW);
}

void blinkYellowLight(int yellowLED)
{
  for ( int i = 0 ; i < 5 ; i++ ) // blink yellow light
  {
    digitalWrite(yellowLED, LOW);
    delay(yellowBlinkTime);
    digitalWrite(yellowLED, HIGH);
    delay(yellowBlinkTime);
  }
}

void greenToYellow(int green, int yellow)
{
  digitalWrite(green, LOW); //change east-facing lights from green to yellow to red
  digitalWrite(yellow, HIGH);
  delay(changeDelay);
}

void yellowToRed(int yellow, int red )
{
  digitalWrite(yellow, LOW);
  digitalWrite(red, HIGH);
  delay(changeDelay);
}
void redToGreen(int yellow, int red, int green)
{
  digitalWrite(yellow, LOW);
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
}
void pedestrianReadyToGo(int greenOn, int blueOff, int blueOn, int greenOff)
{
  digitalWrite(greenOn, HIGH);
  digitalWrite(blueOff, LOW);
  digitalWrite(blueOn, HIGH);
  digitalWrite(greenOff, LOW);
}
void loop()
{
  if ( digitalRead(westButton) == HIGH ) // request west>east traffic flow
  {
    if ( trafficWest != true )
      // only continue if traffic flowing in the opposite (east) direction
    {
      trafficWest = true; // change traffic flow flag to west>east
      delay(flowTime);  // give time for traffic to flow

      greenToYellow(eastGreen, eastYellow);

      yellowToRed(eastYellow, eastRed);

      blinkYellowLight(westYellow);
      /*
        digitalWrite(westYellow, LOW);
        digitalWrite(westRed, LOW); // change west-facing lights from red to green
        digitalWrite(westGreen, HIGH);*/
      redToGreen(westYellow, westRed, westGreen);

      //digitalWrite(westpedlightGreen, HIGH); //west ped go
      //digitalWrite(westpedlightBlue, LOW);

      //digitalWrite(eastpedlightBlue, HIGH); //east ped stopped
      //digitalWrite(eastpedlightGreen, LOW);
      pedestrianReadyToGo(westpedlightGreen, westpedlightBlue, eastpedlightBlue, eastpedlightGreen);
    }
  }

  if ( digitalRead(eastButton) == HIGH ) // request east>west traffic flow
  {
    if ( trafficWest == true )
    {
      trafficWest = false; // change traffic flow flag to east>west
      delay(flowTime);  // give time for traffic to flow

      greenToYellow(westGreen, westYellow);

      yellowToRed(westYellow, westRed);

      blinkYellowLight(eastYellow);
      redToGreen(eastYellow, eastRed, eastGreen);
      /*digitalWrite(eastYellow, LOW);
        digitalWrite(eastRed, LOW); // change east-facing lights from red to green
        digitalWrite(eastGreen, HIGH);*/

      /*digitalWrite(westpedlightGreen, LOW); //west ped go
        digitalWrite(westpedlightBlue, HIGH);

        digitalWrite(eastpedlightBlue, LOW); //east ped stopped
        digitalWrite(eastpedlightGreen, HIGH);*/
      pedestrianReadyToGo(eastpedlightGreen, eastpedlightBlue, westpedlightBlue, westpedlightGreen);
    }
  }
}
