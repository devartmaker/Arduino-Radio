#include <TM1637Display.h>

#define CLK 11
#define DIO 12

TM1637Display display(CLK, DIO);

void setup()
{
  display.setBrightness(0x0f);
}

void loop()
{
  display.showNumberDecEx(891, 0x20, false);
  delay(1000);
  display.showNumberDecEx(1070, 0x20, false);
  delay(1000);
}
