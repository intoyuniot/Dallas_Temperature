#include <OneWire.h>
#include <Dallas_Temperature.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);

Dallas_Temperature sensors(&oneWire);

//保存设备地址
DeviceAddress insideThermometer;

//打印设备地址
void printAddress(DeviceAddress deviceAddress)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        if (deviceAddress[i] < 16) Serial.print("0");
        Serial.print(deviceAddress[i], HEX);
    }
}


void setup(void)
{

    Serial.begin(115200);
    Serial.println("Dallas Temperature IC Control Library Demo");

    Serial.print("Locating devices...");
    sensors.begin();
    Serial.print("Found ");
    Serial.print(sensors.getDeviceCount(), DEC); //打印设备数据
    Serial.println(" devices.");

    //报告电源状态
    Serial.print("Parasite power is: ");
    if (sensors.isParasitePowerMode()) Serial.println("ON");
    else Serial.println("OFF");

    if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0");

    //显示找到的设备地址
    Serial.print("Device 0 Address: ");
    printAddress(insideThermometer);
    Serial.println();

    //设置9bit分辨率
    sensors.setResolution(insideThermometer, 9);

    Serial.print("Device 0 Resolution: ");
    Serial.print(sensors.getResolution(insideThermometer), DEC);
    Serial.println();
}

//打印温度值
void printTemperature(DeviceAddress deviceAddress)
{
    float tempC = sensors.getTempC(deviceAddress);
    Serial.print("Temp C: ");
    Serial.print(tempC);
    Serial.print(" Temp F: ");
    Serial.println(Dallas_Temperature::toFahrenheit(tempC)); // Converts tempC to Fahrenheit
}

void loop(void)
{
    Serial.print("Requesting temperatures...");
    sensors.requestTemperatures(); //获取温度
    Serial.println("DONE");

    printTemperature(insideThermometer);
}
