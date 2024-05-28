#ifndef mqtt_h
#define mqtt_h
/****************** Includes*********************************/
#include "WiFi.h"
#include "Adafruit_MQTT_Client.h"
#include "Adafruit_MQTT.h"

/***************************** Macros *********************************/


/**** Adafruit.io Setup ****/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    ""
#define AIO_KEY         ""

/*********************************** extern MQTT Objects *********************************************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
extern WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
extern Adafruit_MQTT_Client mqtt;

// MQTT Feeds

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
extern Adafruit_MQTT_Publish BootloaderReply;

// Setup a feed called 'BootloaderCommand' for subscribing to changes.
extern Adafruit_MQTT_Subscribe BootloaderCommand;

/*********************************** Global Functions Prototypes *********************************************/
void MQTT_connect() ;


#endif