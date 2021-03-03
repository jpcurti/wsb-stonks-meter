#ifndef APCONFIGURATOR_ESP8266_H
#define APCONFIGURATOR_ESP8266_H
   // Use from 0 to 4. Higher number, more debugging messages and memory usage.
   #define _WIFIMGR_LOGLEVEL_    3
   #include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
   //needed for library
   #include <DNSServer.h>
   #include <ESP8266WebServer.h>

   // From v1.1.0
   #include <ESP8266WiFiMulti.h>
   ESP8266WiFiMulti wifiMulti;


   #include <LittleFS.h>
   FS* filesystem = &LittleFS;
   #define FileFS    LittleFS
   #define FS_Name       "LittleFS"


   #define ESP_getChipId()   (ESP.getChipId())

   #define LED_ON      LOW
   #define LED_OFF     HIGH

   //PIN_D0 can't be used for PWM/I2C
   #define PIN_D0            16        // Pin D0 mapped to pin GPIO16/USER/WAKE of ESP8266. This pin is also used for Onboard-Blue LED. PIN_D0 = 0 => LED ON
   #define PIN_D1            5         // Pin D1 mapped to pin GPIO5 of ESP8266
   #define PIN_D2            4         // Pin D2 mapped to pin GPIO4 of ESP8266
   #define PIN_D3            0         // Pin D3 mapped to pin GPIO0/FLASH of ESP8266
   #define PIN_D4            2         // Pin D4 mapped to pin GPIO2/TXD1 of ESP8266
   #define PIN_LED           2         // Pin D4 mapped to pin GPIO2/TXD1 of ESP8266, NodeMCU and WeMoS, control on-board LED
   #define PIN_D5            14        // Pin D5 mapped to pin GPIO14/HSCLK of ESP8266
   #define PIN_D6            12        // Pin D6 mapped to pin GPIO12/HMISO of ESP8266
   #define PIN_D7            13        // Pin D7 mapped to pin GPIO13/RXD2/HMOSI of ESP8266
   #define PIN_D8            15        // Pin D8 mapped to pin GPIO15/TXD2/HCS of ESP8266

   //Don't use pins GPIO6 to GPIO11 as already connected to flash, etc. Use them can crash the program
   //GPIO9(D11/SD2) and GPIO11 can be used only if flash in DIO mode ( not the default QIO mode)
   #define PIN_D11           9         // Pin D11/SD2 mapped to pin GPIO9/SDD2 of ESP8266
   #define PIN_D12           10        // Pin D12/SD3 mapped to pin GPIO10/SDD3 of ESP8266
   #define PIN_SD2           9         // Pin SD2 mapped to pin GPIO9/SDD2 of ESP8266
   #define PIN_SD3           10        // Pin SD3 mapped to pin GPIO10/SDD3 of ESP8266

   #define PIN_D9            3         // Pin D9 /RX mapped to pin GPIO3/RXD0 of ESP8266
   #define PIN_D10           1         // Pin D10/TX mapped to pin GPIO1/TXD0 of ESP8266
   #define PIN_RX            3         // Pin RX mapped to pin GPIO3/RXD0 of ESP8266
   #define PIN_TX            1         // Pin RX mapped to pin GPIO1/TXD0 of ESP8266

   #define LED_PIN           16        // Pin D0 mapped to pin GPIO16 of ESP8266. This pin is also used for Onboard-Blue LED. PIN_D0 = 0 => LED ON

   #define WIFI_MULTI_1ST_CONNECT_WAITING_MS       2200L

   /* Trigger for inititating config mode is Pin D3 and also flash button on NodeMCU
      Flash button is convenient to use but if it is pressed it will stuff up the serial port device driver
      until the computer is rebooted on windows machines.
   */
   #define TRIGGER_PIN  PIN_D3 // D3 on NodeMCU and WeMos.
   /*
      Alternative trigger pin. Needs to be connected to a button to use this pin. It must be a momentary connection
      not connected permanently to ground. Either trigger pin will work.
   */
   #define TRIGGER_PIN2  PIN_D7 // D7 on NodeMCU and WeMos.
#endif //APCONFIGURATOR_ESP8266_H
