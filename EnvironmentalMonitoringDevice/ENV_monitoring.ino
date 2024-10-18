#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>


#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)
#define BUTTON_PIN A1

LiquidCrystal_I2C lcd(0x27,16,2);
Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);
 


int buttonValue;
int preButtonValue;
int buttonState;

void setup() {

  pinMode(A1, INPUT);
  buttonValue = 1;
  buttonState = 0;
  preButtonValue = 0;
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  while ( !Serial ) delay(100);
  unsigned status;
  
  status = bmp.begin();
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

}

void loop() {

if(buttonState == 4)
{
  buttonState = 0;
}
if(analogRead(BUTTON_PIN) > 500)
  buttonValue = 0;
else
  buttonValue = 1;

if(preButtonValue == 0)
{
  if(buttonValue == 1)
  {
    buttonState++;
  }

}

//Serial.println(buttonState);
preButtonValue = buttonValue;

    switch(buttonState)
    {
      case 0:
      lcd.setCursor(0, 0);
      lcd.print("    Pressure                 ");
      lcd.setCursor(0, 1);
      lcd.print("    ");
      lcd.print(bmp.readTemperature());
      lcd.print(" Pa                 ");
           Serial.println("Pa");
      break;

      case 1:
      lcd.setCursor(0, 0);
      lcd.print("Approx altitude               ");
      lcd.setCursor(0, 1);
      lcd.print("     ");
      lcd.print(bmp.readAltitude(1017.25));
      lcd.print(" m                ");
           Serial.println("m");
      break;

      case 2:
      lcd.setCursor(0, 0);
      lcd.print("  Temperature      ");
      lcd.setCursor(0, 1);
      lcd.print("    ");
      lcd.print(bmp.readTemperature());
      lcd.print(" *C          ");
           Serial.println("C");
      break;

      case 3:
      int sensorValue = analogRead(A0);
      float voltage = sensorValue * (5.0 / 1023.0);
  
      lcd.setCursor(0, 0);
      lcd.print("  UV index       ");
      lcd.setCursor(0, 1);
      lcd.print("          ");
      lcd.print(voltage/0.1);
      lcd.print("       ");
      Serial.println("UV");
      break;
    }



} 
