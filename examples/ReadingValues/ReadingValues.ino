#include <PCF8591.h>

PCF8591 a2d;

void setup()
{
  Serial.begin(115200);
  a2d.begin(0, 2);
}

void loop()
{
  if(a2d.UpdateReadings())
  {
    Serial.println(a2d.Data(0));
  }
}
