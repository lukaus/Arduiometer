// Speedometer
// Luke Stanley; 1-13-2013
// theoretically reads the number of times a wheel rotates per second,
// and displays that number converted to miles per hour based on wheel radius

//pin stuffs
int inputPin=8;       // pin to read hits
double lastHit=0;        // stores last hit (ms)
double thisHit=0;        //this hit (ms)
int pinState=0;       //reads input pin
int totalHits=0;

//mathing
double mph=0;                   // Miles Per Hours; displayed
double tireRadius=12.5;      //tire radius in inches (12.5 inches in my case)
double tireCircumference= (double) 2.0 * 3.14159265358979323846264338327950 * tireRadius; //calculates tire circumference
double hps=0;
double inches=0;


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
  pinState=digitalRead(inputPin);
  
  if(pinState==HIGH && (millis() - lastHit) >=100)
  {
      thisHit = millis() - lastHit;   //compares current time in milliseconds to the last time this was triggered to get the time between in milliseconds, which is then converted      // makes sure another signal isn't coming in too soon 
      
      lastHit=thisHit; //sets this signal time in ms to the one to compare to next time
      totalHits+=1;    //counts number of revolutions total, for debugging
      convert((double)thisHit);  //converst the time into MPH
      
  }
}

int convert(double hitMillis)      // converts millisecond since last hit to mph
{
//  hitMillis=500.0;
  
  hps = (double) 1000.0 / hitMillis;

  inches = (double) hps * tireCircumference;
  
  mph = (double) inches * (5.0/88.0); //convert hits per second to miles per hour
  Serial.println(mph);
  return mph;
}
