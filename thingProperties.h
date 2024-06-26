// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char SSID[]     = SECRET_SSID;    // Network SSID (name)
const char PASS[]     = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)

void onLightIntensityChange();
void onSunlightChange();

int lightIntensity;
bool sunlight;

void initProperties(){

  ArduinoCloud.addProperty(lightIntensity, READWRITE, ON_CHANGE, onLightIntensityChange);
  ArduinoCloud.addProperty(sunlight, READWRITE, ON_CHANGE, onSunlightChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
