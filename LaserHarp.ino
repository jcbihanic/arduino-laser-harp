int lightPin = 0;
int speakerPin = 2;
int threshold = 80;
boolean plucked = true;
int duration = 200;
int note = 1915;

const int trigPin = 5;
const int echoPin = 6;

int ledPin = 9;


void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); //sets the led pin to output
  pinMode(speakerPin, OUTPUT);
}


void loop()
{
  long dur, inches, cm;
  
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  dur = pulseIn(echoPin, HIGH);
 
  // convert the time into a distance
  inches = microsecondsToInches(dur);
  cm = microsecondsToCentimeters(dur);
  
  note = cm * 50;
  
  
  int lightLevel = analogRead(lightPin); //Read the lightlevel
  lightLevel = map(lightLevel, 0, 900, 0, 255);
  Serial.println(lightLevel); //adjust the value 0 to 900 to span 0 to 255
  if (lightLevel > threshold){
    if (!plucked){
      for (long i = 0; i < duration * 1000L; i += note * 2) {
        digitalWrite(speakerPin, HIGH);
        delayMicroseconds(note);
        digitalWrite(speakerPin, LOW);
        delayMicroseconds(note);
      }
      plucked = true;
    }
    digitalWrite(ledPin, HIGH);
  }else {
    plucked = false;
    digitalWrite(ledPin, LOW);
  }
}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}
 
long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
