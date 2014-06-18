#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>


Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);


void setup()
{
    Serial.begin(9600);

    if(!bmp.begin()) {
        Serial.println("ERROR: Check BMP180 wiring");
        while(1);
    }
}


void loop()
{

}


struct SensorData {
    float tempF;
    float tempC;
    float pressure;
};


float celsiusToFahrenheit(float celsius)
{
    return ((9/5) * celsius) + 32;
}


void readBMP180(struct& sensorData)
{
    sensors_event_t event;
    bmp.getEvent(&event);

    float tempC;
    bmp.getTemperature(&tempC);

    sensorData.pressure = event.pressure;
    sensorData.tempC = tempC;
    sensorData.tempF = celsiusToFahrenheit(tempC);
}
