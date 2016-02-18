#include "PCF8591.h"
#include "Arduino.h"
#include "Wire.h"

namespace
{
  const uint8_t PCF8591_ADDRESS                                     = 0x48;

  const uint8_t PCF8591_CONTROL_ANALOGUE_OUTPUT_ENABLE              = 0x40;
  const uint8_t PCF8591_CONTROL_FOUR_SINGLE_ENDED_INPUTS            = 0x00;
  const uint8_t PCF8591_CONTROL_THREE_DIFFERENTIAL_INPUTS           = 0x10;
  const uint8_t PCF8591_CONTROL_SINGLE_ENDED_AND_DIFFERENTIAL_MIXED = 0x20;
  const uint8_t PCF8591_CONTROL_TWO_DIFFERENTIAL_INPUTS             = 0x30;

  const uint8_t PCF8591_CONTROL_AUTO_INCREMENT                      = 0x04;
  const uint8_t PCF8591_CONTROL_CHANNEL_MASK                        = 0x03;
}

PCF8591::PCF8591()
  : data{0}
{
}

PCF8591::PCF8591(int sda, int scl)
  : data{0}
{
  begin(sda, scl);
}

void PCF8591::begin(int sda, int scl) const
{
  Wire.begin(sda, scl);
  InitialiseDevice();
}

void PCF8591::InitialiseDevice() const
{
  Wire.beginTransmission(PCF8591_ADDRESS);
  Wire.write(PCF8591_CONTROL_FOUR_SINGLE_ENDED_INPUTS |
             PCF8591_CONTROL_AUTO_INCREMENT |
             (0x00 & PCF8591_CONTROL_CHANNEL_MASK));
  Wire.endTransmission();
}

bool PCF8591::UpdateReadings()
{
  Wire.requestFrom(PCF8591_ADDRESS, numberOfInputs);

  if(Wire.available() >= 4)
  {
    for(uint8_t i = 0; i < numberOfInputs; ++i)
    {
      data[i] = Wire.read();
    }
    return true;
  }
  return false;
}

uint8_t PCF8591::Data(size_t index) const
{
  if(index < numberOfInputs)
  {
    return data[index];
  }
  return 0;
}
