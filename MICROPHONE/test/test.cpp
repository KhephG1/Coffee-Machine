#include <I2S.h>
#include <Arduino.h>
#define SAMPLE_RATE     (44100)
#define I2S_SCK_IO      (25)
#define I2S_WS_IO       (16)
#define I2S_DI_IO       (26)
#define DATA_BIT        (16)
#define MODE_PIN        (4)


char i2sReadrawBuff[100];
void setup() {
  Serial.begin(115200);
 
  if(!I2S.begin(I2S_PHILIPS_MODE, 44100, 16)){ // controller device
  
  }
  Serial.println("I2S init success");
  
}

void loop() {
  I2S.read(i2sReadrawBuff,100);
  //Output Right Channel Data
  //Serial.println((int16_t)(i2sReadrawBuff[2]|i2sReadrawBuff[3]<<8));
  //Output Left Channel Data
  Serial.println((int16_t)(i2sReadrawBuff[0]|i2sReadrawBuff[1]<<8));
}