// loading libraries
#include <Wire.h>
#include <DIYables_LCD_I2C.h> 
#include <OneWire.h>
#include <DallasTemperature.h>

// connect pins
#define TDS_PIN A0          
#define ONE_WIRE_BUS 2      

// display setup
DIYables_LCD_I2C lcd(0x27, 16, 2);

// temp sensor setup
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensors(&oneWire);

// reference voltage and sample buffer length
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

void loop() {
  static unsigned long sampleTime = millis();
  static unsigned long displayTime = millis();

  // sample every 40 ms
  if (millis() - sampleTime > 40) {
    sampleTime = millis();
    analogBuffer[analogBufferIndex] = analogRead(TDS_PIN);
    analogBufferIndex = (analogBufferIndex + 1) % SCOUNT;
  }

  // update display every second
  if (millis() - displayTime > 1000) {
    displayTime = millis();
    
    // read temp
    tempSensors.requestTemperatures();
    float currentTemp = tempSensors.getTempCByIndex(0);

    // average buffer
    long sum = 0;
    for (int i = 0; i < SCOUNT; i++) {
      sum += analogBuffer[i];
    }
    float averageAnalog = sum / (float)SCOUNT;

    // convert to voltage
    float averageVoltage = averageAnalog * (float)VREF / 1024.0;

    // temp compensation factor
    float compensationCoefficient = 1.0 + 0.02 * (currentTemp - 25.0);
    float compensationVoltage = averageVoltage / compensationCoefficient;

    // convert voltage to TDS value
    float tdsValue = (133.42 * compensationVoltage * compensationVoltage * compensationVoltage 
                     - 255.86 * compensationVoltage * compensationVoltage 
                     + 857.39 * compensationVoltage) * 0.5;

    // print values to LCD
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("temp: ");
    lcd.print(currentTemp, 1);
    lcd.write(223); // Degree symbol (°)
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("cond: ");
    lcd.print((int)tdsValue);
    lcd.print(" ppm");
  }
}
