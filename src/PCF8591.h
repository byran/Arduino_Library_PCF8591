#ifndef PCF8591_H
#define PCF8591_H

#include "Arduino.h"

class PCF8591
{
public:
  static const size_t numberOfInputs = 4;

private:
  uint8_t data[numberOfInputs];

public:
  PCF8591();
  PCF8591(int sda, int scl);
  void begin(int sda, int scl) const;
  void InitialiseDevice() const;

  bool UpdateReadings();
  uint8_t Data(size_t index) const;
};

#endif // #ifndef PCF8591_H
