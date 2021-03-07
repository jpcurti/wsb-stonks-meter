#include <ServoInterface.h>

ServoInterface::ServoInterface(/* args */)
{
   if(!servo.attached())
    {
        servo.attach(servo_pin);
    }
    servo.write(90);
    
    servo.detach();
}

ServoInterface::~ServoInterface()
{
   
}

void ServoInterface::updateServoOnPercentage(float percentage)
{   
    if(!servo.attached())
    {
        servo.attach(servo_pin);
    }
        //  approximate sigmoid as in https://gitlab.com/prefrontalvortex/bit-tricks/blob/4f30cc2e998cd589fb2340e2c6deb07007a67141/sigmoid_hax.c
        //using approximate sigmoid
        //percentage = percentage * 1024/100;
       // servo.write(fastsig_i32(percentage)*180/1024);

        //direct conversion
        if(percentage > 100) servo.write(180);
        else if (percentage < -100) servo.write(0);
        else{
            servo.write(percentage*0.9+90);
        }
       
        
        servo.detach();
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
