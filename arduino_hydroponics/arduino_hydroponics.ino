// loading libraries
#include <Wire.h>
#include <DIYables_LCD_I2C.h> 
#include <OneWire.h>
#include <DallasTemperature.h>

## connect pins
#define TDS_PIN A0          
#define ONE_WIRE_BUS 2      

// display setup
DIYables_LCD_I2C lcd(0x27, 16, 2);

// temp sensor setup
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensors(&oneWire);

## reference voltage and sample buffer lenght
#define VREF 5.0       
#define SCOUNT 30          
int analogBuffer[SCOUNT];
int analogBufferIndex = 0;

void setup() {
  Serial.begin(9600);
  // initialize display
  lcd.init();
  lcd.backlight();
  lcd.clear();

  // initialize temp sensor
  tempSensors.begin();
  
  pinMode(TDS_PIN, INPUT);
}
  // sample every 40 ms
  if (millis() - sampleTime > 40) {
    sampleTime = millis();
    analogBuffer[analogBufferIndex] = analogRead(TDS_PIN);
    analogBufferIndex = (analogBufferIndex + 1) % SCOUNT;
  }

  // update display every second
  if (millis() - displayTime > 1000) {
    displayTime = millis();
