#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>


Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);


typedef struct SensorData
{
    float tempF;
    float tempC;
    float pressure;
};


float celsiusToFahrenheit(float celsius)
{
    return (1.8 * celsius) + 32;
}


void readBMP180(struct SensorData *sd)
{
    sensors_event_t event;
    bmp.getEvent(&event);

    float tempC;
    bmp.getTemperature(&tempC);

    sd->pressure = event.pressure;
    sd->tempC = tempC;
    sd->tempF = celsiusToFahrenheit(tempC);
}


void setup(void)
{
    Serial.begin(9600);

    if(!bmp.begin()) {
        Serial.println("ERROR: Check BMP180 wiring");
        while(1);
    }
}


void loop(void)
{
    SensorData sd;
    readBMP180(&sd);

    Serial.print("Pressure: ");
    Serial.println(sd.pressure);
    Serial.println("");

    Serial.print("Temp (F): ");
    Serial.println(sd.tempF);
    Serial.println("");

    Serial.print("Temp (C): ");
    Serial.println(sd.tempC);
    Serial.println("");

    delay(3000);
}
