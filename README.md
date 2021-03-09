# Stocks monitor 
A monitor of your favorite stock using an ESP8266 (or ESP32), a display and a servo motor indication to indicate when you to the moon.


<a href="Stonksmeter"><img src="images/stonksmeter.gif" align="center"  width="300" ></a>

## Motivation
This started as a weekend project for myself after I saw [this reddit post](https://www.reddit.com/r/wallstreetbets/comments/lfkprt/finished_my_diy_project_just_in_time_for_gme_to/). However checking the comments I decided to make it public and configurable so that anybody with at least an ESP board and a generid SSD1306 display can make your own.

## How to use?
In the first boot if no password was stored (Or if you press the secondary/flash button from the board), an access point called STONKS_*ESPMACADDRESS* will be created.

<a href="Access point created by the ESP"><img src="images/access_point.jpeg" align="center"  width="300" ></a>


After connecting to it, a configuration portal should open.

<a href="Initial page from config portal"><img src="images/configuration_portal_1.jpeg" align="center"  width="300" ></a>

Then, select your wifi network(s) and insert the password(s), your personal finnhub API key and the [ticker symbol](https://en.wikipedia.org/wiki/Ticker_symbol).

<a href="Configuration portal"><img src="images/configuration_portal_2.jpeg" align="center"  width="300" ></a>

After this, the ESP will make the request to the finnhub API and fetch, every minute, the current stock price and close price from previous day. Then, the ESP will display the value, difference and difference in percentage for the day in the display and turn the servo motor according to the day gain in %.

## How to build, run and assembly.

###### What do you need:
  - [An ESP8266 / ESP 32 board](https://www.espressif.com/en/products/devkits). I used a **NodeMCU Lolin V3** but the case was designed for a (WEMOS D1)[https://de.aliexpress.com/item/32681374223.html?spm=a2g0s.9042311.0.0.27424c4dkVELIS]
  - A generic OLED 0.96" 128x64 Display based on the chip SSD1306. I used a [generic display from aliexpress](https://de.aliexpress.com/item/32639731302.html?spm=a2g0s.9042311.0.0.27424c4dvVaQDI).
  - A 9g Micro Servo. I used a [generic servo from Aliexpress](https://de.aliexpress.com/item/1005001500679701.html?spm=a2g0s.9042311.0.0.39204c4dSB1oh6)
  - A 3d Printer for the [housing](https://www.thingiverse.com/thing:4756562) or just use any 3D print service.
  - Some wire jumpers or some wire to solder.
 
###### Housing (3D-Printer Files)
Located on the [Thingiverse page](https://www.thingiverse.com/thing:4756562).


## Tech/framework used
<b>Built with</b>
- [VS Code](https://code.visualstudio.com/) and [PlatformIO](https://platformio.org/). 


## Credits
Original idea from [this reddit post](https://www.reddit.com/r/wallstreetbets/comments/lfkprt/). Special thanks to [@khoih-prog](https://github.com/khoih-prog) for providing the [library for wifi management on ESP](https://github.com/khoih-prog/ESP_WiFiManager) and [Stefan Ries](https://www.thingiverse.com/smily77/designs) that provided [3d printed housing](https://www.thingiverse.com/thing:857858) for the ESP that I remixed for this project.


## License
A short snippet describing the license (MIT, Apache etc)

GPL-3.0 License © [JpCurti](https://github.com/jpcurti)
