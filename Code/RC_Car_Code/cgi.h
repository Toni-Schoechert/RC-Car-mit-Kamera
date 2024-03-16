#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

// CGI handler which is run when a request for /led.cgi is detected
const char * cgi_movement_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{

    //GPIO Pins von In1-4 Motortreiber als GPIO Outputs setzen
    //IN1
    gpio_init(20);
    gpio_set_dir(20, GPIO_OUT);
    //IN2
    gpio_init(21);
    gpio_set_dir(21, GPIO_OUT);
    //IN3
    gpio_init(26);
    gpio_set_dir(26, GPIO_OUT);
    //IN4
    gpio_init(27);
    gpio_set_dir(27, GPIO_OUT);

    // Check if an request for Movment has been made (/movment.cgi?movement=x)
    if (strcmp(pcParam[0] , "movement") == 0){
        // Look at the argument to check which movment to do (turn on the coresponding IN Motordriver)
        if(strcmp(pcValue[0], "1") == 0){ //Forward
            gpio_put(20, 1);
            gpio_put(21, 0);
            gpio_put(26, 1);
            gpio_put(27, 0);
        }else if(strcmp(pcValue[0], "2") == 0){//Backward
            gpio_put(20, 0);
            gpio_put(21, 1);
            gpio_put(26, 0);
            gpio_put(27, 1);   
        }else if(strcmp(pcValue[0], "3") == 0){//Stop
            gpio_put(20, 0);
            gpio_put(21, 0);
            gpio_put(26, 0);
            gpio_put(27, 0);
        }else if(strcmp(pcValue[0], "4") == 0){//left
            gpio_put(20, 1);
            gpio_put(21, 0);
            gpio_put(26, 0);
            gpio_put(27, 0);
        }else if(strcmp(pcValue[0], "5") == 0){//right
            gpio_put(20, 0);
            gpio_put(21, 0);
            gpio_put(26, 1);
            gpio_put(27, 0);
        }
    }
    
    // Send the index page back to the user
    return "/index.shtml";
}

// tCGI Struct
// Fill this with all of the CGI requests and their respective handlers
static const tCGI cgi_handlers[] = {
    {
        // Html request for "movement.cgi" triggers cgi_handler
        "/movement.cgi", cgi_movement_handler
    },
};

void cgi_init(void)
{
    http_set_cgi_handlers(cgi_handlers, 1);
}