#include <OneWire.h>
#include <Dallas_Temperature.h>


//引脚定义
#define ONE_WIRE_BUS D2

//设置分辨率
#define TEMPERATURE_PRECISION 9

OneWire oneWire(ONE_WIRE_BUS);

Dallas_Temperature sensors(&oneWire);

//保存设备地址
DeviceAddress insideThermometer, outsideThermometer;


//打印设备地址
void printAddress(DeviceAddress deviceAddress)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        // zero pad the address if necessary
        if (deviceAddress[i] < 16) Serial.print("0");
        Serial.print(deviceAddress[i], HEX);
    }
}

//打印温度值
void printTemperature(DeviceAddress deviceAddress)
{
    float tempC = sensors.getTempC(deviceAddress);
    Serial.print("Temp C: ");
    Serial.print(tempC);
    Serial.print(" Temp F: ");
    Serial.print(Dallas_Temperature::toFahrenheit(tempC));
}

//获取设备分辨率
void printResolution(DeviceAddress deviceAddress)
{
    Serial.print("Resolution: ");
    Serial.print(sensors.getResolution(deviceAddress));
    Serial.println();
}

//打印设备信息
void printData(DeviceAddress deviceAddress)
{
    Serial.print("Device Address: ");
    printAddress(deviceAddress);
    Serial.print(" ");
    printTemperature(deviceAddress);
    Serial.println();
}

void setup(void)
{
    Serial.begin(115200);
    Serial.println("Dallas Temperature IC Control Library Demo");

    //开始运行
    sensors.begin();

    // locate devices on the bus
    Serial.print("Locating devices...");
    Serial.print("Found ");
    Serial.print(sensors.getDeviceCount(), DEC);
    Serial.println(" devices.");

    //电源模式
    Serial.print("Parasite power is: ");
    if (sensors.isParasitePowerMode()) Serial.println("ON");
    else Serial.println("OFF");


    //搜寻设备
    if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0");
    if (!sensors.getAddress(outsideThermometer, 1)) Serial.println("Unable to find address for Device 1");

    //打印寻找到的设备信息
    Serial.print("Device 0 Address: ");
    printAddress(insideThermometer);
    Serial.println();

    Serial.print("Device 1 Address: ");
    printAddress(outsideThermometer);
    Serial.println();

    //设置9bit的分辨率
    sensors.setResolution(insideThermometer, TEMPERATURE_PRECISION);
    sensors.setResolution(outsideThermometer, TEMPERATURE_PRECISION);

    Serial.print("Device 0 Resolution: ");
    Serial.print(sensors.getResolution(insideThermometer), DEC);
    Serial.println();

    Serial.print("Device 1 Resolution: ");
    Serial.print(sensors.getResolution(outsideThermometer), DEC);
    Serial.println();
}

void loop(void)
{
    //获取温度
    Serial.print("Requesting temperatures...");
    sensors.requestTemperatures();
    Serial.println("DONE");

    printData(insideThermometer);
    printData(outsideThermometer);
}
