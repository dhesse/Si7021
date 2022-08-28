#include "Adafruit_Si7021.h"
#include "ujson.hpp"
#define MAIN_DEBUG 1

Adafruit_Si7021 sensor = Adafruit_Si7021();

void setup()
{
  Wire.begin();
}

void loop()
{
  JSON json;
  json.push("temperature", sensor.readTemperature());
  json.push("humidity", sensor.readHumidity());
  json.push("voltage", (float)(analogRead(BATT)*0.0011224));
  char res[120];
  json.format(res);
#ifdef MAIN_DEBUG
  Serial.println(res);
#endif
  Particle.publish("ambience/cigarbox", res, PRIVATE);
  SystemSleepConfiguration config;
  config.mode(SystemSleepMode::STOP)
        .duration(2h);
  System.sleep(config);
}