// Speedometer
// Luke Stanley; 1-13-2013
// theoretically reads the number of times a wheel rotates per second,
// and displays that number converted to miles per hour based on wheel radius

//pin stuffs
int inputPin=8;       // pin to read hits
int lastHit=0;        // stores last hit (ms)
int thisHit=0;        //this hit (ms)
int pinState=0;       //reads input pin
int totalHits=0;

//mathing
int mph=0;                   // Miles Per Hours; displayed
double tireRadius=12.5;      //tire radius in inches (12.5 inches in my case)
double tireCircumference= 2 * 3.14159265358979323846264338327950 * tireRadius; //calculates tire circumference
int inchPerSec=0;            //for calculating MPH

//more math and ?debouncing? hopefully maybe
long previousMillis = 0;    //for counting seconds with interval
long interval = 999;        // not quite a second, to compensate for LED blink

void setup()
{
  pinMode(inputPin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  
  unsigned long currentMillis = millis();
  pinState=digitalRead(inputPin);
  if(pinState==HIGH)
  {
    thisHit = currentMillis - lastHit;
    lastHit=thisHit;
    totalHits+=1;
    convert(thisHit);
  }
  Serial.println(mph);
  delay(1);
}

int convert(int hitMillis)      // converts millisecond since last hit to mph
{
  double hps = 1000/hitMillis;
  double inches = hps * tireCircumference;
  mph = inches * (5/88); //convert hits per second to miles per hour
}
