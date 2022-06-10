#include "mbed.h"
#include "bbcar.h"
BufferedSerial pc(USBTX, USBRX);

Ticker servo_ticker;
PwmOut pin5(D10), pin6(D11);
DigitalInOut pin10(D9);
BBCar car(pin5, pin6, servo_ticker);
double last = 0;
double initial;
double w1, w2;
// main() runs in its own thread in the OS
int main()
{
    parallax_ping  ping1(pin10);
    initial = last = (float)ping1;
    ThisThread::sleep_for(100ms);
    while(1){
        car.turn(30, 0.6);
        printf("last = %f \n",last);
        if ((float)ping1 > 1.5 *last){
            printf("turn \n");
            w1 = sqrt(((int)last*(int)last) -(((int)initial * (int)initial)));
            printf("w1 length: %f \n", w1);
            car.turn(-30, 0.6);
            ThisThread::sleep_for(3s);
            while(1){
                car.turn(-30, 0.6);
                printf("last = %f \n",last);
                if ((float)ping1 > 1.5 *last){
                    car.stop();
                    w2 = sqrt(((int)last*(int)last) -(((int)initial * (int)initial)));
                    printf("w2 length: %f \n", w2);
                    break;
                }
                wait_us(1000);
                last = (float)ping1;
                wait_us(1000);
            }
        break;
        }
    wait_us(1000);
    last = (float)ping1;
    wait_us(1000);
    }
    printf("w length: %f \n", w1 + w2);
}


