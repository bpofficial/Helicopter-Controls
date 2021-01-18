#include <HID-Project.h>
#include <HID-Settings.h>
#include <inttypes.h>

#include "HID.h"

#define COMM_BAUD 230400
#define USBS_BAUD 9600

void setup() {
  // Start the Serial1 which is connected with the IO MCU.
  // Make sure both baud rates are the same
  // you can go up to 2000000 for very fast data transmission.
  Serial1.begin(COMM_BAUD);

  // Start the gamepad
  Gamepad.begin();
  
  // Start the USB Serial for debugging
  Serial.begin(USBS_BAUD);
}

void loop() {
  if (Serial1.available() > 0) {
    String res = Serial1.readStringUntil('\n');
    //Serial.println(res);
    //Serial.println(res.length());
    int len = res.length();
    
    char* buff = (char *)malloc(sizeof(char)* 45);
    strcpy(buff, res.c_str());
    Serial.println(buff);
    free(buff);
    
    int cyclic_x, cyclic_y; 
    //sscanf(buff, "X:%d,", &cyclic_x);
    //sscanf(buff, "Y:%d,", &cyclic_y);
    //char cyclic_y[6], collective[6], rudder[6], throttle[4];
    //sscanf(buff, "X:%d,Y:%s,%C:%s,R:%s,T:%s", &cyclic_x, &cyclic_y, &collective, &rudder, &throttle);

    //Serial.println(buff);
    //Serial.println(cyclic_x);
    //Serial.println(cyclic_y);
    //Serial.println();
    /*
    Gamepad.xAxis(cyclic_x);
    Gamepad.yAxis(cyclic_y);
    Gamepad.rxAxis(collective);
    Gamepad.ryAxis(rudder);
    Gamepad.zAxis(throttle);
    Gamepad.write();*/
    delay(5);
  }
}
