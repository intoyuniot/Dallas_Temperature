#include <OneWire.h>
#include <Dallas_Temperature.h>


#define ONE_WIRE_BUS D2

OneWire oneWire(ONE_WIRE_BUS);

Dallas_Temperature sensors(&oneWire);

void setup(void)
{
    Serial.begin(115200);
    Serial.println("Dallas Temperature Control Library - Async Demo");
    Serial.println("\nDemo shows the difference in length of the call\n\n");

    sensors.begin();
}

void loop(void)
{
    //请求温度转换
    Serial.println("Before blocking requestForConversion");
    unsigned long start = millis();

    sensors.requestTemperatures();

    unsigned long stop = millis();
    Serial.println("After blocking requestForConversion");
    Serial.print("Time used: ");
    Serial.println(stop - start);

    //获取温度
    Serial.print("Temperature: ");
    Serial.println(sensors.getTempCByIndex(0));
    Serial.println("\n");

    Serial.println("Before NON-blocking/async requestForConversion");
    start = millis();
    sensors.setWaitForConversion(false);
    sensors.requestTemperatures();
    sensors.setWaitForConversion(true);
    stop = millis();
    Serial.println("After NON-blocking/async requestForConversion");
    Serial.print("Time used: ");
    Serial.println(stop - start);


    int resolution = 9;
    delay(750/ (1 << (12-resolution)));

    Serial.print("Temperature: ");
    Serial.println(sensors.getTempCByIndex(0));
    Serial.println("\n\n\n\n");

    delay(5000);
}
