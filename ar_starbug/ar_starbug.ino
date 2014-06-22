#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>


typedef struct SensorData
{
    float tempF;
    float tempC;
    float pressure;
};

// Set some global variables
SensorData sd;
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);


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
    if(Serial.available() > 0) {
        if(Serial.read() == 82) {
            readBMP180(&sd);
            sendSensorDataToSerial();
        }
    }
}


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


void sendSensorDataToSerial(void)
{
    Serial.print("temp_f:");
    Serial.print(sd.tempF);
    Serial.print("|");
    Serial.print("temp_c:");
    Serial.print(sd.tempC);
    Serial.print("|");
    Serial.print("pressure:");
    Serial.println(sd.pressure);
}
