#include <Servo.h>

#define LEFT_P 4
#define LEFT_N 3
#define LEFT 6
#define RIGHT_P 2
#define RIGHT_N 7
#define RIGHT 5

#define ECHO_PIN 12
#define TRIGGER_PIN 13

Servo servo;

int angle = 79;
unsigned int distanceFront = 0;
unsigned int distanceRight = 0;
bool isNewPath;
bool noRight = 0;
double timer;

void setup()
{
  pinMode(LEFT_P, OUTPUT);
  pinMode(LEFT_N, OUTPUT);
  pinMode(LEFT, OUTPUT);
  pinMode(RIGHT_P, OUTPUT);
  pinMode(RIGHT_N, OUTPUT);
  pinMode(RIGHT, OUTPUT);

  servo.attach(9);
  servo.write(angle);

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
  isNewPath = 1;
  timer = 0;
  stop();
}

void loop()
{
  if(isNewPath == 1)
  {
    noRight = 1;
    isNewPath = 0;
    stop();
    sensorFront();
    delay(500);
    distanceFront = measureDistance();
    sensorRight();
    delay(1000);
    go();
    timer = millis();

  }

  distanceRight = measureDistance();

  if(distanceRight > 20)
  {
      noRight = 0;
      isNewPath = 1;
      delay(2500);
      stop();
      right();
      go();
      delay(2000);
      stop();
  }

  if( noRight == 1 && (distanceFront - timeTravelled()*8.3 < 5))
  {
    isNewPath = 1;
    delay(300);
    stop();
    left();
  }


}

void sensorFront()
{
  for(angle = 79; angle < 174; angle++)  
  {                                  
    servo.write(angle);               
    delay(10);                   
  } 

}

void sensorRight()
{
   for(angle = 174; angle > 79; angle--)    
  {                                
    servo.write(angle);           
    delay(10);       
  }
}

void go()
{
  digitalWrite(LEFT_P, LOW);
  digitalWrite(LEFT_N, HIGH);
  digitalWrite(RIGHT_P, LOW);
  digitalWrite(RIGHT_N, HIGH);
  analogWrite(LEFT, 100);
  analogWrite(RIGHT, 100);
}
void back()
{
  digitalWrite(LEFT_P, HIGH);
  digitalWrite(LEFT_N, LOW);
  digitalWrite(RIGHT_P, HIGH);
  digitalWrite(RIGHT_N, LOW);
  analogWrite(LEFT, 100);
  analogWrite(RIGHT, 100);
}
void left()
{
  digitalWrite(LEFT_P, LOW);
  digitalWrite(LEFT_N, HIGH);
  digitalWrite(RIGHT_P, HIGH);
  digitalWrite(RIGHT_N, LOW);
  analogWrite(LEFT, 100);
  analogWrite(RIGHT, 100);
  delay(2150);
  analogWrite(LEFT, 0);
  analogWrite(RIGHT, 0);
}

void right()
{
  digitalWrite(LEFT_P, HIGH);
  digitalWrite(LEFT_N, LOW);
  digitalWrite(RIGHT_P, LOW);
  digitalWrite(RIGHT_N, HIGH);
  analogWrite(LEFT, 100);
  analogWrite(RIGHT, 100);
  delay(2050);
  analogWrite(LEFT, 0);
  analogWrite(RIGHT, 0);
}
void stop()
{
  analogWrite(LEFT, 0);
  analogWrite(RIGHT, 0);
}

unsigned int measureDistance()
{
  unsigned int duration, distance;
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2) / 29.1;
  delay(100);
  Serial.println(distance);
  return distance;
}

double timeTravelled()
{

  double timeMoved = millis() - timer;

  return timeMoved/1000;


}