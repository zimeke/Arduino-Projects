#define SOUND_SENSOR A0
#define GREEN_LED 11
#define RED_LED 13
#define YELLOW_LED 12
#define LEFT_P 5
#define LEFT_N 4
#define LEFT 9
#define RIGHT_P 3
#define RIGHT_N 2
#define RIGHT 10


//SoundSensing variables
int currentValue;
int maxValue;
int minValue;
unsigned long timer;
int sampleSpan  = 200; 
int volume;


bool volumeState;
bool preVolumeState;
bool isStand;
int clapCount;
unsigned long clapTime;


void setup()
{
  pinMode(SOUND_SENSOR, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(LEFT_P, OUTPUT);
  pinMode(LEFT_N, OUTPUT);
  pinMode(LEFT, OUTPUT);
  pinMode(RIGHT_P, OUTPUT);
  pinMode(RIGHT_N, OUTPUT);
  pinMode(RIGHT, OUTPUT);
  Serial.begin(9600);
  resetValues();
  volumeState = 0;
  preVolumeState = 0;
  clapCount = 0;
  
  
  isStand = 1;
  digitalWrite(RED_LED, HIGH);
}

void loop()
{

  sensingSound();

  if(volume > 500)
  {
    Serial.println("LOUD");
    digitalWrite(YELLOW_LED, HIGH);
    if(preVolumeState == 0)
    {
      if(isStand == 0)
      {
        stop();
        isStand = 1;
        
      }
      else
      {
        if(clapCount == 0)
          clapTime = millis();
        clapCount++;
        
        
      }
      
    }
    volumeState = 1;
  }
  else
  {
    Serial.println("QIUET");
    digitalWrite(YELLOW_LED, LOW);
    Serial.println(clapCount);
    volumeState = 0;
  }
  
  if(((millis() - clapTime >= 2000) || clapCount == 3 ) && isStand == 1)
  {
    switch(clapCount)
      {
        case 0:
        stop();
        isStand = 1;
        break;
        case 1:
        right();
        isStand = 0; 
        break;
        case 2:
        left();
        isStand = 0; 
        break;
        default:
        go();
        isStand = 0; 
        break;
      }
    clapCount = 0;
    clapTime = millis();
    
  }

   preVolumeState = volumeState; 
}



//SoundSensing functions
void sensingSound()
{
    currentValue = analogRead(SOUND_SENSOR);

    if (currentValue < minValue) {
        minValue = currentValue;
    } 
    if (currentValue > maxValue) {
        maxValue = currentValue;
    }

    if (millis() - timer >= sampleSpan) {
        volume = maxValue - minValue;
        resetValues();
    }

}

void resetValues()
{
    maxValue = 0;
    minValue = 1024;
    timer = millis(); 
}

void stop()
{
  analogWrite(LEFT, 0);
  analogWrite(RIGHT, 0);
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);

}
void go()
{
  digitalWrite(LEFT_P, LOW);
  digitalWrite(LEFT_N, HIGH);
  digitalWrite(RIGHT_P, LOW);
  digitalWrite(RIGHT_N, HIGH);
  analogWrite(LEFT, 100);
  analogWrite(RIGHT, 100);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
}
void right()
{
  digitalWrite(LEFT_P, HIGH);
  digitalWrite(LEFT_N, LOW);
  digitalWrite(RIGHT_P, LOW);
  digitalWrite(RIGHT_N, HIGH);
  analogWrite(LEFT, 100);
  analogWrite(RIGHT, 100);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
}
void left()
{
  digitalWrite(LEFT_P, LOW);
  digitalWrite(LEFT_N, HIGH);
  digitalWrite(RIGHT_P, HIGH);
  digitalWrite(RIGHT_N, LOW);
  analogWrite(LEFT, 100);
  analogWrite(RIGHT, 100);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
}