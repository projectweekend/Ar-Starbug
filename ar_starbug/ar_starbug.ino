#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_HTU21DF.h>


typedef struct SensorData
{
    float tempF;
    float tempC;
    float humidity;
    float pressure;
};

// Set some global variables
SensorData sd;
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);
Adafruit_HTU21DF htu = Adafruit_HTU21DF();


void setup(void)
{
    Serial.begin(9600);

    if(!bmp.begin()) {
        Serial.println("ERROR: Check BMP180 wiring");
        while(1);
    }

    if (!htu.begin()) {
        Serial.println("ERROR: Check HTU21DF wiring");
        while (1);
    }
}


void loop(void)
{
    if(Serial.available() > 0) {
        if(Serial.read() == 82) {
            readBMP180(&sd);
            readHTU21DF(&sd);
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


void readHTU21DF(struct SensorData *sd)
{
    sd->humidity = htu.readHumidity();
}


void sendSensorDataToSerial(void)
{
    Serial.print("temp_f:");
    Serial.print(sd.tempF);
    Serial.print("|");
    Serial.print("temp_c:");
    Serial.print(sd.tempC);
    Serial.print("|");
    Serial.print("humidity:");
    Serial.print(sd.humidity);
    Serial.print("|");
    Serial.print("pressure:");
    Serial.println(sd.pressure);
}
