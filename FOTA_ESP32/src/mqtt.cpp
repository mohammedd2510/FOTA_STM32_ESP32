#include "mqtt.h"

/*********************************** Define MQTT Objects *********************************************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// MQTT Feeds

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
 Adafruit_MQTT_Publish BootloaderReply = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/BootloaderReply");

// Setup a feed called 'BootloaderCommand' for subscribing to changes.
 Adafruit_MQTT_Subscribe BootloaderCommand = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/BootloaderCommand", MQTT_QOS_1);


/*********************************** Global Functions Definition *********************************************/
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) 
  {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}