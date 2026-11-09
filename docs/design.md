# Essential Code

## #include <stdio.h>
## #include <unistd.h>
## #include <pigpio.h>
## #define PIN 17
## int main(int argc, char* argv[])
## {
##   gpioInitialise();
##   gpioSetMode(PIN, PI_OUTPUT);
##   gpioWrite(PIN,1);// LED ON
##   getchar();// waits for enter key
##   gpioWrite(PIN,0);// LED off
##   getchar();//waits for enter key
##   gpioTerminate();
##   return 0;
## }

File handling will also be used in the code to store the values input by the user and then it will compare those values with a conditional.
If the temps trigger a warning then it will trigger the light to turn on otherwise the light will not turn on.
Using the values in the file the code will calculate the average by reading them and then adding all values together before dividing them by how many there are to get an average.
This code will flag by default temps outside of the range which is 68F-76F.
