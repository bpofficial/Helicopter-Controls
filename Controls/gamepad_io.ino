#include <stdio.h>
#include <inttypes.h>

#define CYCLIC_X_PIN   14
#define CYCLIC_Y_PIN   15
#define COLLECTIVE_PIN 16
#define THROTTLE_PIN   17
#define RUDDER_PIN     18

#define SERIAL_BAUD 230400
#define DEBUG 0

typedef struct Controller {
  int16_t cyclic_x;   // x-axis
  int16_t cyclic_y;   // y-axis
  int16_t collective; // rx-axis
  int16_t rudder;     // ry-axis
  int8_t  throttle;   // z-axis
} Controller;

Controller ctrl = {0, 0, 0, 0, 0};

void setup() {
  pinMode(CYCLIC_X_PIN,   INPUT);
  pinMode(CYCLIC_Y_PIN,   INPUT);
  pinMode(COLLECTIVE_PIN, INPUT);
  pinMode(THROTTLE_PIN,   INPUT);
  pinMode(RUDDER_PIN,     INPUT);
  
  Serial.begin(SERIAL_BAUD);
}

// Map 10bit integer to a 16bit integer
int16_t map_range_highres(int pin) {
  delay(0.15);
  return map(analogRead(pin), 0, 1023, -10000, 9999);
}  

// Map 10bit integer to an 8bit integer
int8_t map_range_lowres(int pin) {
  return map(analogRead(pin), 0, 1023, -100, 99);
} 

void create_data_str(char* buff) {
  int n = 0;
  int temp;
  
  if ((temp = sprintf(&buff[n], "X:%d,", ctrl.cyclic_x)) > 0) {
    n += temp;
  } else {
    strcpy(buff, "X,X,X,X,X");
    return;
  }
  
  if ((temp = sprintf(&buff[n], "Y:%d,", ctrl.cyclic_y)) > 0) {
    n += temp; 
  } else {
    strcpy(buff, "X,X,X,X,X");
    return;
  }
  
  if ((temp = sprintf(&buff[n], "C:%d,", ctrl.collective)) > 0) {
    n += temp; 
  } else {
    strcpy(buff, "X,X,X,X,X");
    return;
  }
  
  if ((temp = sprintf(&buff[n], "R:%d,", ctrl.rudder)) > 0) {
    n += temp; 
  } else {
    strcpy(buff, "X,X,X,X,X");
    return;
  }
  
  if ((temp = sprintf(&buff[n], "T:%d\n", ctrl.throttle)) > 0) {
    n += temp; 
  } else {
    strcpy(buff, "X,X,X,X,X");
    return;
  }
}

void loop() {
  ctrl.cyclic_x    = map_range_highres(CYCLIC_X_PIN);
  ctrl.cyclic_y    = map_range_highres(CYCLIC_Y_PIN);
  ctrl.collective  = map_range_highres(COLLECTIVE_PIN);
  ctrl.rudder      = map_range_highres(RUDDER_PIN);
  
  // Only low res (8bit), throttle doesn't require high sensitivity.
  ctrl.throttle    = map_range_lowres(THROTTLE_PIN);

  char* str = (char *)malloc(sizeof(char) * 32);
  create_data_str(str);
  
  Serial.write((char *)str, strlen(str));
  free(str);

  Serial.flush();
  delay(2);
}
