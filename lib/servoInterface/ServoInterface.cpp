#include <ServoInterface.h>

ServoInterface::ServoInterface(/* args */)
{
    if(!servo.attached())
    {
        servo.attach(servo_pin);
    }
}

ServoInterface::~ServoInterface()
{
    if(servo.attached())
    {
        servo.detach();
    }
}

void ServoInterface::updateServoOnPercentage(int percentage)
{

    if(servo.attached())
    {   
        //  approximate sigmoid as in https://gitlab.com/prefrontalvortex/bit-tricks/blob/4f30cc2e998cd589fb2340e2c6deb07007a67141/sigmoid_hax.c
        //using approximate sigmoid
        percentage = percentage * 1024/100;
        servo.write(fastsig_i32(percentage)*180/1024);
         
       //direct conversion
       //servo.write(percentage*180/100);
    }
}

int ServoInterface::fastsig_i32(int x) {
    // as in https://gitlab.com/prefrontalvortex/bit-tricks/blob/4f30cc2e998cd589fb2340e2c6deb07007a67141/sigmoid_hax.c
    /*  Using integers as fixed-point fractions, this function uses a Taylor series to approximate a sigmoid function
     * e.g. 1/(1 + exp(-x)).
     * The cubed term can't exceed 2^31, so that gives an upper bound of 2^10 = 1024
     */
    if (x > 1024)  return 1024;
    if (x < -1024)  return -1024;
    return ( (3*x) - ((x*x*x)>>20) ) >> 1;
}
