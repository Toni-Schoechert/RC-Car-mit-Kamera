#include <stdio.h>
#include "lwip/apps/httpd.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "pico/cyw43_arch.h"
#include "lwipopts.h"
#include "cgi.h"
#include "hm01b0.h"
#include <stdint.h>

// WIFI Credentials - take care if pushing to github!
const char WIFI_SSID[] = "Wifi_Name";
const char WIFI_PASSWORD[] = "Passwort";

//definition Kamera
const struct hm01b0_config hm01b0_config = {
    .i2c           = PICO_DEFAULT_I2C_INSTANCE,
    .sda_pin       = PICO_DEFAULT_I2C_SDA_PIN,
    .scl_pin       = PICO_DEFAULT_I2C_SCL_PIN,
    .vsync_pin     = 6,
    .hsync_pin     = 7,
    .pclk_pin      = 8,
    .data_pin_base = 9,
    .data_bits     = 1,
    .pio           = pio0,
    .pio_sm        = 0,
    .reset_pin     = -1,
    .mclk_pin      = -1,
    .width         = 160,
    .height        = 120,
};


int main() {
    stdio_init_all();

    cyw43_arch_init();

    cyw43_arch_enable_sta_mode();

    //fehler bei der kamera verbindun Led blinkt 2 mal
    if (hm01b0_init(&hm01b0_config) != 0) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(250);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(250);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(250);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    }

    
    //PWM
    //set GPIO Pins 0 und 1 to PMW
    gpio_set_function(0, GPIO_FUNC_PWM);
    gpio_set_function(1, GPIO_FUNC_PWM);
    //PWM slice detecting for GPIO Pins
    uint slice_num = pwm_gpio_to_slice_num(0);
    //Set Period : 1/freq*Clockfreq Pico: 125.000.000hz/Period(now 62500)=(now 2000 Hz)
    pwm_set_wrap(slice_num, 62499);
    //Set Duty cycle %(Here 75) *Periode /100
    uint16_t duty_cycle = 75*62500/100;
    //set channel A  und B (entspricht GPIO 1/0) output to 70%
    pwm_set_chan_level(slice_num, PWM_CHAN_A, duty_cycle);
    pwm_set_chan_level(slice_num, PWM_CHAN_B, duty_cycle);
    //set PWM running
    pwm_set_enabled(slice_num, true);
    //ende PWM setup

    // Connect to the WiFI network - loop until connected
    while(cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000) != 0){}
    // Print a success message once connected and turn led on
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    
    // Initialise web server
    httpd_init();

    // Configure CGI handler
    cgi_init();
    
    // Infinite loop
     while(1) {
        //auslesen der Kamera daten QQvga
        uint8_t pixels[160 * 120];
        hm01b0_read_frame(pixels, sizeof(pixels));

        // Bilddaten über die serielle Verbindung senden
        printf("%s", pixels);
    }

}
