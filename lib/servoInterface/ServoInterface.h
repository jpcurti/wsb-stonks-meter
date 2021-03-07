#ifndef SERVOINTERFACE_H
#define SERVOINTERFACE_H
#include <Servo.h>

 class ServoInterface
{
private:
    /* data */
    Servo servo;
    int servo_pin = D4;  // for ESP8266 microcontroller
    int fastsig_i32(int x);
public:
    ServoInterface(/* args */);
    ~ServoInterface();
    void updateServoOnPercentage(float percentage);
};





#endif