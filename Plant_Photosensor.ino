
/* Plant System

Checks Temperature/Humidity/Moist/Light
Activates light when needed/plays sound when Dry soil

TODO: Upload to SQL server and website!
2012/10/7
 Code by Conrad Chamerski
*/

#include "DHT.h"
#include "pitches.h"
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE);

//variables
unsigned long elapsed;
float hours,minutes,seconds,ms;
unsigned long over;
int fanRelay = 6;
int lightRelay = 7; 
int moistPin = 4;



void setup() {
  Serial.begin(9600);   
    Serial.println("Program Start!");
  dht.begin();
  pinMode(fanRelay, OUTPUT);     
  pinMode(lightRelay, OUTPUT);
}


int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };

int photocellPin = 0;     // the cell and 10K pulldown are connected to a0  ANALOG
int photocellReading;     // the analog reading from the sensor divider

void loop() {
  
  photocellReading = analogRead(photocellPin);  
  Serial.print("Analog reading = ");
  Serial.println(photocellReading);     // the raw analog reading
 
  delay(100);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C");
  }
  
  int moistSensor;
  moistSensor = analogRead(moistPin);
  Serial.print("Moist reading = ");
  Serial.println(moistSensor); 

   elapsed=millis();
  hours=int(elapsed/3600000);
  over=elapsed%3600000;
  minutes=int(over/60000);
  over=over%60000;
  seconds=int(over/1000);
  ms=over%1000;
  
    if ((int)minutes%30==0 && (int)minutes!= 0)
  {
         digitalWrite(fanRelay, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
    if ((int)minutes%35==0 && (int)minutes!= 0)
  {
  digitalWrite(fanRelay, LOW);    // turn the LED off by making the voltage LOW
  }
  
  /*

  if (moistSensor < 850 && (int)minutes%5==0 && (int)minutes!= 0)  // Change to Good Value
  {
   for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000/noteDurations[thisNote];
    tone(8, melody[thisNote],noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(8);
   }
  }
  */
  
  
  if ( photocellReading > 600 )
  {
    digitalWrite(lightRelay, HIGH);
  }
  else
  {
    digitalWrite(lightRelay, LOW);
  }
  
 if( (int)hours%18 == 0 && hours != 0 )
 {
     digitalWrite(lightRelay, HIGH);
 }
 if( (int)hours%23 == 0 && hours != 0 )
 {
     digitalWrite(lightRelay, LOW);
 }
  

  
}
