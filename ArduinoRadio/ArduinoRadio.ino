#include <Wire.h>
#include <radio.h>
#include <RDA5807M.h>
#include <TM1637Display.h>
#include <EEPROM.h>

#define FIX_BAND     RADIO_BAND_FM
#define FIX_VOLUME   5
#define CLK 11
#define DIO 12

int lastTime;

RDA5807M radio; 

TM1637Display display(CLK, DIO);

int f;

void setup() {
  Serial.begin(9600);
  delay(200);
  radio.init();  
  //radio.debugEnable();
  
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  radio.setVolume(FIX_VOLUME);
  radio.setMono(false);
  radio.setMute(false);

  EEPROM.get(0, f);
  f -= 10;
  display.setBrightness(0x0f);
}

void loop() {
  int change = getEncoderTurn();
  if (change != 0) {
    int d = millis() - lastTime;
    lastTime = millis();
    if (d > 150) d = 150;
    
    int m = 150 / d;
    if (m < 0) m = 1;
    Serial.print(m);
    Serial.print("  --  ");
    
    f += change * 10 * m; 
    if (change > 0 && f > 10800) {
      f = 10800;
    } else if (change < 0 && f < 8800) {
      f = 8800;
    }
    
    EEPROM.put(0, f);

    Serial.println(f);
    display.showNumberDecEx(f / 10, 0x20, false);
    
    if (f == 9590) {
      f = 9580;
    }
    radio.setBandFrequency(FIX_BAND, f);
  }

  delay(1);
}

int getEncoderTurn() {
  // -1,0,+1의 값중 하나를 반환합니다.
  static int oldA = LOW;
  static int oldB = LOW;
  int result = 0;
  int newA = digitalRead(2);
  int newB = digitalRead(3);
  if (newA != oldA || newB != oldB) {
    // 바뀐 값이 있을 때
    if (oldA == LOW && newA == HIGH) {
      result = -(oldB * 2 - 1);
    }
  }
  oldA = newA;
  oldB = newB;
  
  return result;
} 
