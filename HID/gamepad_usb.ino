#include <HID-Project.h>
#include <HID-Settings.h>
#include <inttypes.h>

#include "HID.h"

#define COMM_BAUD 230400
#define USBS_BAUD 9600

typedef struct __attribute__((__packed__)) {
  byte cyclic_x_h, cyclic_x_l;      // x-axis
  byte cyclic_y_h, cyclic_y_l;      // y-axis
  byte collective_h, collective_l;  // rx-axis
  byte rudder_h, rudder_l;          // ry-axis
  byte throttle;                    // z-axis
} Controller;

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

int convert(const char *str, int *n) {
    int value = 0;
    if (str == NULL)
        return 0;
    while (*str) {
        if (isdigit((unsigned char)*str)) {
            value = value * 10 + *str++ - '0';
        } else {
            return 0;
        }
    }
    *n = value;
    return 1;
}

void loop() {
  if (Serial1.available() > 0) {
    String res = Serial1.readStringUntil('\n');
    Serial.println(res);
    Serial.println(res.length());
    int len = res.length();
    
    char buff[len];
    strcpy(&buff, `
    /*
    char buff[res.length() + 1];
    res.toCharArray(buff, res.length());
    Serial.println(buff);

    int16_t cyclic_x; 
    char cyclic_y[6], collective[6], rudder[6], throttle[4];
    sscanf(buff, "X:%"SCNd16",Y:%s,%C:%s,R:%s,T:%s", &cyclic_x, &cyclic_y, &collective, &rudder, &throttle);

    Serial.println(cyclic_x);*/
    /*
    Gamepad.xAxis(cyclic_x);
    Gamepad.yAxis(cyclic_y);
    Gamepad.rxAxis(collective);
    Gamepad.ryAxis(rudder);
    Gamepad.zAxis(throttle);
    Gamepad.write();*/
  }
}
