#include <ApConfigurator.h>

#if (defined(ESP32))
#include <apConfigurator_ESP32.h>
#elif (defined(ESP8266))
#include <apConfigurator_ESP8266.h>
#else
#error This code is intended to run only on the ESP32 board ! Please check your Tools->Board setting.
#endif
#include <vector>
// SSID and PW for Config Portal
//String ssid = "stonks_" + String(ESP_getChipId(), HEX);
//const char* password = "tothemoon";

// SSID and PW for your Router
String Router_SSID;
String Router_Pass;

#define MIN_AP_PASSWORD_SIZE 8

#define SSID_MAX_LEN 32
//From v1.0.10, WPA2 passwords can be up to 63 characters long.
#define PASS_MAX_LEN 64
#define API_MAX_LEN 32
#define TICKER_MAX_LEN 6
typedef struct
{
	char wifi_ssid[SSID_MAX_LEN];
	char wifi_pw[PASS_MAX_LEN];
} WiFi_Credentials;

typedef struct
{
	String wifi_ssid;
	String wifi_pw;
} WiFi_Credentials_String;

#define NUM_WIFI_CREDENTIALS 2


typedef struct
{
  WiFi_Credentials  WiFi_Creds [NUM_WIFI_CREDENTIALS];
  char api_key[API_MAX_LEN];
  char ticker_symbol[TICKER_MAX_LEN];
} WM_Config;
WM_Config         WM_config;

#define CONFIG_FILENAME F("/wifi_cred.dat")
//////

// Use false if you don't like to display Available Pages in Information Page of Config Portal
// Comment out or use true to display Available Pages in Information Page of Config Portal
// Must be placed before #include <ESP_WiFiManager.h>
#define USE_AVAILABLE_PAGES false

// From v1.0.10 to permit disable/enable StaticIP configuration in Config Portal from sketch. Valid only if DHCP is used.
// You'll loose the feature of dynamically changing from DHCP to static IP, or vice versa
// You have to explicitly specify false to disable the feature.
#define USE_STATIC_IP_CONFIG_IN_CP          false

// Use false to disable NTP config. Advisable when using Cellphone, Tablet to access Config Portal.
// See Issue 23: On Android phone ConfigPortal is unresponsive (https://github.com/khoih-prog/ESP_WiFiManager/issues/23)
#define USE_ESP_WIFIMANAGER_NTP false

// Use true to enable CloudFlare NTP service. System can hang if you don't have Internet access while accessing CloudFlare
// See Issue #21: CloudFlare link in the default portal (https://github.com/khoih-prog/ESP_WiFiManager/issues/21)
#define USE_CLOUDFLARE_NTP false

#define USE_DHCP_IP true
#define USING_CORS_FEATURE true

#define WIFICHECK_INTERVAL 1000L
#define HEARTBEAT_INTERVAL 10000L
#define WIFI_MULTI_CONNECT_WAITING_MS 100L


#include <ESP_WiFiManager.h> //https://github.com/khoih-prog/ESP_WiFiManager

// SSID and PW for Config Portal
String ssid = "stonks_" + String(ESP_getChipId(), HEX);
const char *password = "tothemoon";
// Indicates whether ESP has WiFi credentials saved from previous session
bool initialConfig = false;

#warning Using DHCP IP
IPAddress stationIP = IPAddress(0, 0, 0, 0);
IPAddress gatewayIP = IPAddress(192, 168, 2, 1);
IPAddress netMask = IPAddress(255, 255, 255, 0);

#define USE_CONFIGURABLE_DNS true

IPAddress dns1IP = gatewayIP;
IPAddress dns2IP = IPAddress(8, 8, 8, 8);

ApConfigurator::ApConfigurator()
{
}

ApConfigurator::~ApConfigurator()
{
}

void ApConfigurator::begin()
{
	setupApConfigurator();
}

void ApConfigurator::heartBeatPrint(void)
{
	static int num = 1;

	if (WiFi.status() == WL_CONNECTED)
		Serial.print("H"); // H means connected to WiFi
	else
		Serial.print("F"); // F means not connected to WiFi

	if (num == 80)
	{
		Serial.println();
		num = 1;
	}
	else if (num++ % 10 == 0)
	{
		Serial.print(" ");
	}
}

uint8_t ApConfigurator::check_WiFi(void)
{
	if ((WiFi.status() != WL_CONNECTED))
	{
		Serial.println("\nWiFi lost. Call connectMultiWiFi in loop");
		return connectMultiWiFi();
	}
	return WL_CONNECTED;
}

void ApConfigurator::check_status(void)
{
	static ulong checkstatus_timeout = 0;
	static ulong checkwifi_timeout = 0;

	static ulong current_millis;

	current_millis = millis();

	// Check WiFi every WIFICHECK_INTERVAL (1) seconds.
	if ((current_millis > checkwifi_timeout) || (checkwifi_timeout == 0))
	{
		check_WiFi();
		checkwifi_timeout = current_millis + WIFICHECK_INTERVAL;
	}

	// Print hearbeat every HEARTBEAT_INTERVAL (10) seconds.
	if ((current_millis > checkstatus_timeout) || (checkstatus_timeout == 0))
	{
		heartBeatPrint();
		checkstatus_timeout = current_millis + HEARTBEAT_INTERVAL;
	}
}

void ApConfigurator::loadConfigData(void)
{
	File file = FileFS.open(CONFIG_FILENAME, "r");
	LOGERROR(F("LoadWiFiCfgFile "));

	if (file)
	{
		file.readBytes((char *)&WM_config, sizeof(WM_config));
		file.close();
		LOGERROR(F("OK"));
	}
	else
	{
		LOGERROR(F("failed"));
	}
}

void ApConfigurator::saveConfigData()
{
	File file = FileFS.open(CONFIG_FILENAME, "w");
	LOGERROR(F("SaveWiFiCfgFile "));

	if (file)
	{
		file.write((uint8_t *)&WM_config, sizeof(WM_config));

		file.close();
		LOGERROR(F("OK"));
	}
	else
	{
		LOGERROR(F("failed"));
	}
}

uint8_t ApConfigurator::connectMultiWiFi(void)
{

	uint8_t status;

	LOGERROR(F("ConnectMultiWiFi with :"));

	if ((Router_SSID != "") && (Router_Pass != ""))
	{
		LOGERROR3(F("* Flash-stored Router_SSID = "), Router_SSID, F(", Router_Pass = "), Router_Pass);
	}

	for (uint8_t i = 0; i < NUM_WIFI_CREDENTIALS; i++)
	{
		// Don't permit NULL SSID and password len < MIN_AP_PASSWORD_SIZE (8)
		if ((String(WM_config.WiFi_Creds[i].wifi_ssid) != "") && (strlen(WM_config.WiFi_Creds[i].wifi_pw) >= MIN_AP_PASSWORD_SIZE))
		{
			LOGERROR3(F("* Additional SSID = "), WM_config.WiFi_Creds[i].wifi_ssid, F(", PW = "), WM_config.WiFi_Creds[i].wifi_pw);
		}
	}

	LOGERROR(F("Connecting MultiWifi..."));

	WiFi.mode(WIFI_STA);

	int i = 0;
	status = wifiMulti.run();
	delay(WIFI_MULTI_1ST_CONNECT_WAITING_MS);

	while ((i++ < 10) && (status != WL_CONNECTED))
	{
		status = wifiMulti.run();

		if (status == WL_CONNECTED)
			break;
		else
			delay(WIFI_MULTI_CONNECT_WAITING_MS);
	}

	if (status == WL_CONNECTED)
	{
		LOGERROR1(F("WiFi connected after time: "), i);
		LOGERROR3(F("SSID:"), WiFi.SSID(), F(",RSSI="), WiFi.RSSI());
		LOGERROR3(F("Channel:"), WiFi.channel(), F(",IP address:"), WiFi.localIP());
	}
	else
		LOGERROR(F("WiFi not connected"));

	return status;
}

void ApConfigurator::setupApConfigurator(void)
{

	// put your setup code here, to run once:
	// initialize the LED digital pin as an output.
	pinMode(PIN_LED, OUTPUT);
	pinMode(TRIGGER_PIN, INPUT_PULLUP);
	pinMode(TRIGGER_PIN2, INPUT_PULLUP);
	if (!Serial)
		Serial.begin(115200);
	while (!Serial)
		;

	Serial.print("\nStarting ConfigOnSwitch using " + String(FS_Name));
	Serial.println(" on " + String(ARDUINO_BOARD));
	Serial.println("ESP_WiFiManager Version " + String(ESP_WIFIMANAGER_VERSION));

	Serial.setDebugOutput(false);

// Format FileFS if not yet
#ifdef ESP32
	if (!FileFS.begin(true))
	{
		Serial.print(FS_Name);
		Serial.println(F(" failed! AutoFormatting."));
	}
#else
	if (!FileFS.begin())
	{
		Serial.print(FS_Name);
		Serial.println(F(" failed! AutoFormatting."));
		FileFS.format();
	}
#endif

	unsigned long startedAt = millis();

	//Local intialization. Once its business is done, there is no need to keep it around
	// Use this to default DHCP hostname to ESP8266-XXXXXX or ESP32-XXXXXX
	//ESP_WiFiManager ESP_wifiManager;
	// Use this to personalize DHCP hostname (RFC952 conformed)
	ESP_WiFiManager ESP_wifiManager("StonksMeter");

	ESP_wifiManager.setDebugOutput(true);

	ESP_wifiManager.setMinimumSignalQuality(-1);

	ESP_wifiManager.setConfigPortalChannel(0);

	ESP_wifiManager.setCORSHeader("Your Access-Control-Allow-Origin");

	// We can't use WiFi.SSID() in ESP32as it's only valid after connected.
	// SSID and Password stored in ESP32 wifi_ap_record_t and wifi_config_t are also cleared in reboot
	// Have to create a new function to store in EEPROM/SPIFFS for this purpose
	Router_SSID = ESP_wifiManager.WiFi_SSID();
	Router_Pass = ESP_wifiManager.WiFi_Pass();

	//Remove this line if you do not want to see WiFi password printed
	Serial.println("Stored: SSID = " + Router_SSID + ", Pass = " + Router_Pass);


	// SSID to uppercase
	ssid.toUpperCase();

	// From v1.1.0, Don't permit NULL password
	if ((Router_SSID != "") && (Router_Pass != ""))
	{
		LOGERROR3(F("* Add SSID = "), Router_SSID, F(", PW = "), Router_Pass);
		wifiMulti.addAP(Router_SSID.c_str(), Router_Pass.c_str());

		ESP_wifiManager.setConfigPortalTimeout(120); //If no access point name has been previously entered disable timeout.
		Serial.println("Got stored Credentials. Timeout 120s for Config Portal");
	}
	else
	{
		Serial.println("Open Config Portal without Timeout: No stored Credentials.");
		initialConfig = true;
	}

	if (initialConfig)
	{
		startConfigurationPortal();
	}

	startedAt = millis();

	if (!initialConfig)
	{
		// Load stored data, the addAP ready for MultiWiFi reconnection
		loadConfigData();

		Serial.print("Loaded from WM_Config - API: ");
		Serial.print(WM_config.api_key);
		Serial.print(" - Ticker: ");
		Serial.println(WM_config.ticker_symbol);

		for (uint8_t i = 0; i < NUM_WIFI_CREDENTIALS; i++)
		{
			// Don't permit NULL SSID and password len < MIN_AP_PASSWORD_SIZE (8)
			if ((String(WM_config.WiFi_Creds[i].wifi_ssid) != "") && (strlen(WM_config.WiFi_Creds[i].wifi_pw) >= MIN_AP_PASSWORD_SIZE))
			{
				LOGERROR3(F("* Add SSID = "), WM_config.WiFi_Creds[i].wifi_ssid, F(", PW = "), WM_config.WiFi_Creds[i].wifi_pw);
				wifiMulti.addAP(WM_config.WiFi_Creds[i].wifi_ssid, WM_config.WiFi_Creds[i].wifi_pw);
			}
		}

		if (WiFi.status() != WL_CONNECTED)
		{
			Serial.println("ConnectMultiWiFi in setup");

			connectMultiWiFi();
		}
	}

	Serial.print("After waiting ");
	Serial.print((float)(millis() - startedAt) / 1000L);
	Serial.print(" secs more in setup(), connection result is ");

	if (WiFi.status() == WL_CONNECTED)
	{
		Serial.print("connected. Local IP: ");
		Serial.println(WiFi.localIP());
	}
	else
	{
		Serial.println(ESP_wifiManager.getStatus(WiFi.status()));
	}
}

bool ApConfigurator::checkRequestConfigurationPortal(void)
{
	// is configuration portal requested?
	if ((digitalRead(TRIGGER_PIN) == LOW) || (digitalRead(TRIGGER_PIN2) == LOW))
	{
		startConfigurationPortal();
		return true;
	}
	return false;
}

void ApConfigurator::startConfigurationPortal(void)
{
	Serial.println("\nConfiguration portal requested.");
	digitalWrite(PIN_LED, LED_ON); // turn the LED on by making the voltage LOW to tell us we are in configuration mode.

	//Local intialization. Once its business is done, there is no need to keep it around
	ESP_WiFiManager ESP_wifiManager("ConfigOnSwitch");
	
	ESP_WMParameter paramAPI("FinnhubAPI_Label", "Finnhub API Key", WM_config.api_key, API_MAX_LEN);
	ESP_WMParameter paramTicker("TickerSymbol_Label", "Ticker Symbol e.g GME", WM_config.ticker_symbol, TICKER_MAX_LEN);
	ESP_WMParameter p_hint("<small>*Hint: if you want to reuse the currently active WiFi credentials, leave SSID and Password fields empty</small>");
	

    //add all parameters here

    ESP_wifiManager.addParameter(&p_hint);
	ESP_wifiManager.addParameter(&paramAPI);
	ESP_wifiManager.addParameter(&paramTicker);

	ESP_wifiManager.setMinimumSignalQuality(-1);

	// Set config portal channel, default = 1. Use 0 => random channel from 1-13
	ESP_wifiManager.setConfigPortalChannel(0);
	ESP_wifiManager.setCORSHeader("Your Access-Control-Allow-Origin");

	//Check if there is stored WiFi router/password credentials.
	//If not found, device will remain in configuration mode until switched off via webserver.
	Serial.print("Opening configuration portal. ");
	Router_SSID = ESP_wifiManager.WiFi_SSID();
	Router_Pass = ESP_wifiManager.WiFi_Pass();

	// From v1.1.0, Don't permit NULL password
	if ((Router_SSID != "") && (Router_Pass != ""))
	{
		ESP_wifiManager.setConfigPortalTimeout(240); //If no access point name has been previously entered disable timeout.
		Serial.println("Got stored Credentials. Timeout 240s");
	}
	else
		Serial.println("No stored Credentials. No timeout");

	//Starts an access point
	//and goes into a blocking loop awaiting configuration
	if (!ESP_wifiManager.startConfigPortal((const char *)ssid.c_str(), password))
	{
		Serial.println("Not connected to WiFi but continuing anyway.");
	}
	else
	{
		//if you get here you have connected to the WiFi
		Serial.println("connected...");
		Serial.print("Local IP: ");
		Serial.println(WiFi.localIP());
	}

	// Only clear then save data if CP entered and with new valid Credentials
	// No CP => stored getSSID() = ""
	if (String(ESP_wifiManager.getSSID(0)) != "" && String(ESP_wifiManager.getSSID(1)) != "")
	{
		// Stored  for later usage, from v1.1.0, but clear first
		memset(&WM_config, 0, sizeof(WM_config));

		for (uint8_t i = 0; i < NUM_WIFI_CREDENTIALS; i++)
		{
			String tempSSID = ESP_wifiManager.getSSID(i);
			String tempPW = ESP_wifiManager.getPW(i);

			if (strlen(tempSSID.c_str()) < sizeof(WM_config.WiFi_Creds[i].wifi_ssid) - 1)
				strcpy(WM_config.WiFi_Creds[i].wifi_ssid, tempSSID.c_str());
			else
				strncpy(WM_config.WiFi_Creds[i].wifi_ssid, tempSSID.c_str(), sizeof(WM_config.WiFi_Creds[i].wifi_ssid) - 1);

			if (strlen(tempPW.c_str()) < sizeof(WM_config.WiFi_Creds[i].wifi_pw) - 1)
				strcpy(WM_config.WiFi_Creds[i].wifi_pw, tempPW.c_str());
			else
				strncpy(WM_config.WiFi_Creds[i].wifi_pw, tempPW.c_str(), sizeof(WM_config.WiFi_Creds[i].wifi_pw) - 1);

			// Don't permit NULL SSID and password len < MIN_AP_PASSWORD_SIZE (8)
			if ((String(WM_config.WiFi_Creds[i].wifi_ssid) != "") && (strlen(WM_config.WiFi_Creds[i].wifi_pw) >= MIN_AP_PASSWORD_SIZE))
			{
				LOGERROR3(F("* Add SSID = "), WM_config.WiFi_Creds[i].wifi_ssid, F(", PW = "), WM_config.WiFi_Creds[i].wifi_pw);
				wifiMulti.addAP(WM_config.WiFi_Creds[i].wifi_ssid, WM_config.WiFi_Creds[i].wifi_pw);
			}
		}

		if (strlen(paramAPI.getValue()) < sizeof(WM_config.api_key) - 1)
			strcpy(WM_config.api_key, paramAPI.getValue());
		else
			strncpy(WM_config.api_key, paramAPI.getValue(), sizeof(WM_config.api_key) - 1);
		if (strlen(paramTicker.getValue()) < sizeof(WM_config.ticker_symbol) - 1)
			strcpy(WM_config.ticker_symbol, paramTicker.getValue());
		else
			strncpy(WM_config.ticker_symbol, paramTicker.getValue(), sizeof(WM_config.ticker_symbol) - 1);
		
	

		Serial.print(WM_config.api_key);
		Serial.print(WM_config.ticker_symbol);

		saveConfigData();
	}

	digitalWrite(PIN_LED, LED_OFF); // Turn led off as we are not in configuration mode.
}
const char *ApConfigurator::api_key()
{	
	return WM_config.api_key;
}

const char *ApConfigurator::ticker()
{	
	return WM_config.ticker_symbol;
}