
#include <Arduino.h>
#include "Connect_Wifi.h"
#include "driver/periph_ctrl.h"
#include "Bootloader_Host.h"

#define RX2 16
#define TX2 17

void bootloaderCommandCallback(uint32_t data) 
{
  memset(BL_Host_Buffer,0,BL_HOST_BUFFER_TX_LENGTH);
  while (Serial2.available())
  {
    Serial2.read();
  }
  switch (data)
  {
    case CBL_GET_VER_CMD:
      Serial.println("\nRequest the bootloader version");
      BL_Host_Get_Version();
      break;
    case CBL_GET_CID_CMD:
      Serial.println("\nRead the MCU chip identification number");
      BL_Host_Get_Chip_ID();
      break;
    case CBL_GET_RDP_STATUS_CMD:
      Serial.println("\nRead the FLASH Read Protection level");
      BL_Host_Get_RDP();
      break;
    case CBL_FLASH_ERASE_CMD:
      Serial.println("\nErase Applcation command");
      BL_Host_Erase_Application();
      break;
    case CBL_MEM_WRITE_CMD:
      Serial.println("\nFlash Application command");
      BL_Host_Flash_Application();
      break;
    case CBL_GO_TO_MAIN_APP_CMD:
      Serial.println("\nJump to Main Application command");
      BL_Host_Jump_To_Application();
      break;
    default:
      Serial.println("\nInvalid Command");
      break;
  }
}
void setup() {
  Serial.begin(230400);
  Serial2.begin(230400, SERIAL_8N1, RX2, TX2);
  Serial.printf("\n\n\n");
  Connect_Wifi(SSID, PASSWORD);
  BootloaderCommand.setCallback(bootloaderCommandCallback);
  mqtt.subscribe(&BootloaderCommand);
  FireBase_Init();
}

void loop() {
MQTT_connect();
mqtt.processPackets(10000);


}

