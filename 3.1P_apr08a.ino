#include "arduino_secrets.h"
// hp_BH1750 - Version: Latest 
#include <hp_BH1750.h>



/* 
  Sketch generated by the Arduino IoT Cloud Thing "Untitled 2"
  https://create.arduino.cc/cloud/things/8fcec49e-f29d-4f25-9020-76d18137d1b8 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  int lightIntensity;
  bool sunlight;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
hp_BH1750 lightMeter;
long suntime = 3000;
long shadetime = 6000;
long current_time = 0;
int intensity = 0;
bool notification = false;
void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(115200);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 
  bool avail = lightMeter.begin(BH1750_TO_GROUND);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  if (sunlight == false)
  {
    ReadLight(suntime);
  }
  else
  {
    ReadLight(shadetime);
  }
  
}
void ReadLight(long time){
  lightMeter.start();
  delay(1000);
  int lux = lightMeter.getLux();
  int val = 50;
  if (time == shadetime){
    int temp = val;
    val = lux;
    lux = temp;
  }

  if(lux < val){
    if (current_time >= time){
      current_time = 0;
      if (time == suntime){
        sunlight = true;
      }
      if (time == shadetime){
        sunlight = false;
      }
      notification = false;
      Serial.println("Lighting changed");
      
    }
    else{
      current_time = current_time;
    }
  }
  else{  
    if (current_time >= time){
      if(notification == false)
      {        
        Serial.println("Change lighting");
        notification = true;
      }
    }
    else{
      current_time += 1000;
    }
  }
}
/*
  Since LightIntensity is READ_WRITE variable, onLightIntensityChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLightIntensityChange()  {
}

/*
  Since Sunlight is READ_WRITE variable, onSunlightChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onSunlightChange()  {
}