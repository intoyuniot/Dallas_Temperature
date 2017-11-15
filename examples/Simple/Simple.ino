#include <OneWire.h>
#include <Dallas_Temperature.h>

#define ONE_WIRE_BUS D2

OneWire oneWire(ONE_WIRE_BUS);

Dallas_Temperature sensors(&oneWire);

void setup(void)
{
    Serial.begin(115200);
    Serial.println("Dallas Temperature IC Control Library Demo");
    sensors.begin();
}

void loop(void)
{
    Serial.print("Requesting temperatures...");
    sensors.requestTemperatures(); //发送命令获取温度
    Serial.println("DONE");

    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(sensors.getTempCByIndex(0));
}
