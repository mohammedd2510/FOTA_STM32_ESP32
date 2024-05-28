/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Bootloader_Host.cpp
 *        Author: Mohamed Osama
 *		   Date:   5/27/2024
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Bootloader_Host.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
uint8_t BL_Host_Buffer[BL_HOST_BUFFER_TX_LENGTH];
uint8_t BL_Host_Receive_Buffer[BL_HOST_BUFFER_RX_LENGTH];
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
static uint32_t Calculate_CRC32(uint8_t *data, uint8_t length);
static void Send_Data_To_Bootloader(uint8_t* data, uint8_t length);
static void Recieve_Data_From_Bootloader(uint8_t length);
static void Process_CBL_GET_VER_CMD(void);
static void Process_CBL_GET_CID_CMD(void);
static void Process_CBL_GET_RDP_CMD(void);
static void Process_CBL_FLASH_ERASE_CMD(void);
static void Process_CBL_GO_TO_MAIN_APP_CMD(void);
static uint8_t Process_CBL_MEM_WRITE_CMD(void);
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
static uint32_t Calculate_CRC32(uint8_t *data, uint8_t length)
{
  uint32_t CRC_Value = 0xFFFFFFFF;
    for (uint32_t DataElemindex = 0; DataElemindex < length; DataElemindex++)
    {
        CRC_Value = CRC_Value ^ data[DataElemindex];
        for(uint8_t Databitlen = 0; Databitlen < 32; Databitlen++)
        {
            if(CRC_Value & 0x80000000)
                CRC_Value = (CRC_Value << 1) ^ 0x04C11DB7;
            else
                CRC_Value = (CRC_Value << 1);
        }      
    }
    return CRC_Value;
}
static void Send_Data_To_Bootloader(uint8_t* data, uint8_t length)
{
    for(uint8_t dataindex = 0; dataindex < length; dataindex++)
    {
         Serial.print("  ");
         Serial.printf("0x%x",data[dataindex]);
         Serial.print(" ");
         Serial2.write(data[dataindex]);
    }
}
static void Send_Data_To_Bootloader_Noprint(uint8_t* data, uint8_t length)
{
    for(uint8_t dataindex = 0; dataindex < length; dataindex++)
    {
         Serial2.write(data[dataindex]);
    }
}
static void Recieve_Data_From_Bootloader(uint8_t length){
    memset(BL_Host_Receive_Buffer,0,BL_HOST_BUFFER_RX_LENGTH);
    for(uint8_t dataindex = 0; dataindex < length; dataindex++)
    {
        while(!Serial2.available())
        {
           Serial.println("Waiting Replay from the Bootloader");
        }
        BL_Host_Receive_Buffer[dataindex] = Serial2.read();
    }
}
static void Recieve_Data_From_Bootloader_Noprint(uint8_t length){
    memset(BL_Host_Receive_Buffer,0,BL_HOST_BUFFER_RX_LENGTH);
    for(uint8_t dataindex = 0; dataindex < length; dataindex++)
    {
        while(!Serial2.available())
        {
           
        }
        BL_Host_Receive_Buffer[dataindex] = Serial2.read();
    }
}
static void Process_CBL_GET_VER_CMD(void)
{
    char BootloaderReply_str[100];
    sprintf(BootloaderReply_str,"Bootloader Vendor ID : %d \n Bootloader Version : %d . %d . %d",BL_Host_Receive_Buffer[0],BL_Host_Receive_Buffer[1],BL_Host_Receive_Buffer[2],BL_Host_Receive_Buffer[3]);
    BootloaderReply.publish(BootloaderReply_str);
    Serial.println();
    Serial.println(BootloaderReply_str);   
}
static void Process_CBL_GET_CID_CMD(void)
{
    char BootloaderReply_str[100];
    sprintf(BootloaderReply_str,"Bootloader Chip ID : 0x%x",*(uint16_t*)BL_Host_Receive_Buffer);
    BootloaderReply.publish(BootloaderReply_str);
    Serial.println();
    Serial.println(BootloaderReply_str);    
}
static void Process_CBL_GET_RDP_CMD(void)
{
   if(BL_Host_Receive_Buffer[0] == 0xAA)
   {
        BootloaderReply.publish("FLASH Protection : LEVEL 0"); 
        Serial.println("\nFLASH Protection : LEVEL 0"); 
   }
   else if(BL_Host_Receive_Buffer[0] == 0x55)
   {
        BootloaderReply.publish("FLASH Protection : LEVEL 1");  
        Serial.println("\nFLASH Protection : LEVEL 1");
   }
   else if(BL_Host_Receive_Buffer[0] == 0xCC)
   {
        BootloaderReply.publish("FLASH Protection : LEVEL 2");
        Serial.println("\nFLASH Protection : LEVEL 2");  
   }
}
static void Process_CBL_FLASH_ERASE_CMD(void)
{
    BootloaderReply.publish("Application Erased Successfully");
    Serial.println("\nApplication Erased Successfully");
}
static void Process_CBL_GO_TO_MAIN_APP_CMD(void)
{
    if(BL_Host_Receive_Buffer[0] == JUMP_SUCCESSFUL)
    {
        BootloaderReply.publish("   Jump Successful");
        Serial.println("\nJump Successful");
    }
    else if (BL_Host_Receive_Buffer[0] == JUMP_FAILED)
    {
        BootloaderReply.publish("   Jump Failed");
        Serial.println("\nJump Failed");
    }
    
}
static uint8_t Process_CBL_MEM_WRITE_CMD(void)
{
    if(BL_Host_Receive_Buffer[0] == FLASH_PAYLOAD_WRITE_FAILED)
    {
        BootloaderReply.publish("   Flash Write Failed");
    }
  return BL_Host_Receive_Buffer[0];   
}
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

void BL_Host_Get_Version(void)
{
    uint8_t CBL_GET_VER_CMD_Len = 6;
    uint32_t CRC32_Value =0;
    uint8_t Length_To_Follow = 0;
    BL_Host_Buffer[0] = CBL_GET_VER_CMD_Len - 1;
    BL_Host_Buffer[1] = CBL_GET_VER_CMD;
    CRC32_Value = Calculate_CRC32(BL_Host_Buffer, CBL_GET_VER_CMD_Len - 4);
    Serial.printf("Host CRC = 0x%x \n",CRC32_Value);
    BL_Host_Buffer[2] = (uint8_t)(CRC32_Value);
    BL_Host_Buffer[3] = (uint8_t)(CRC32_Value >> 8);
    BL_Host_Buffer[4] = (uint8_t)(CRC32_Value >> 16);
    BL_Host_Buffer[5] = (uint8_t)(CRC32_Value >> 24);
    Serial.printf("Sending Data to Bootloader : ");
    Send_Data_To_Bootloader(&BL_Host_Buffer[0], 1);
    Send_Data_To_Bootloader(&BL_Host_Buffer[1], CBL_GET_VER_CMD_Len - 1);
    Serial.printf("\n\n");
    Recieve_Data_From_Bootloader(2);
     if(BL_Host_Receive_Buffer[0] == CBL_SEND_ACK)
     {
        Serial.println("\nReceived Acknowledgement from Bootloader");
        Serial.println("\nCRC Verification Successful");
        Length_To_Follow = BL_Host_Receive_Buffer[1];
        Recieve_Data_From_Bootloader(Length_To_Follow);
        Process_CBL_GET_VER_CMD();
     }
     else if (BL_Host_Receive_Buffer[0] == CBL_SEND_NACK)
     {
        Serial.println("\n   Received Not-Acknowledgement from Bootloader");
        Serial.println("\n   CRC Verification Failed");
        BootloaderReply.publish("CRC Verification Failed");
     }     
}
void BL_Host_Get_Chip_ID(void)
{
    uint8_t CBL_GET_CID_CMD_Len = 6;
    uint32_t CRC32_Value =0;
    uint8_t Length_To_Follow = 0;
    BL_Host_Buffer[0] = CBL_GET_CID_CMD_Len - 1;
    BL_Host_Buffer[1] = CBL_GET_CID_CMD;
    CRC32_Value = Calculate_CRC32(BL_Host_Buffer, CBL_GET_CID_CMD_Len - 4);
    Serial.printf("Host CRC = 0x%x \n",CRC32_Value);
    BL_Host_Buffer[2] = (uint8_t)(CRC32_Value);
    BL_Host_Buffer[3] = (uint8_t)(CRC32_Value >> 8);
    BL_Host_Buffer[4] = (uint8_t)(CRC32_Value >> 16);
    BL_Host_Buffer[5] = (uint8_t)(CRC32_Value >> 24);
    Serial.printf("Sending Data to Bootloader : ");
    Send_Data_To_Bootloader(&BL_Host_Buffer[0], 1);
    Send_Data_To_Bootloader(&BL_Host_Buffer[1], CBL_GET_CID_CMD_Len - 1);
    Serial.printf("\n\n");
    Recieve_Data_From_Bootloader(2);
     if(BL_Host_Receive_Buffer[0] == CBL_SEND_ACK)
     {
        Serial.println("\nReceived Acknowledgement from Bootloader");
        Serial.println("\nCRC Verification Successful");
        Length_To_Follow = BL_Host_Receive_Buffer[1];
        Recieve_Data_From_Bootloader(Length_To_Follow);
        Process_CBL_GET_CID_CMD();
     }
     else if (BL_Host_Receive_Buffer[0] == CBL_SEND_NACK)
     {
        Serial.println("\n   Received Not-Acknowledgement from Bootloader");
        Serial.println("\n   CRC Verification Failed");
        BootloaderReply.publish("CRC Verification Failed");
     }      
}
void BL_Host_Get_RDP(void)
{
    uint8_t CBL_GET_RDP_STATUS_CMD_Len = 6;
    uint32_t CRC32_Value =0;
    uint8_t Length_To_Follow = 0;
    BL_Host_Buffer[0] = CBL_GET_RDP_STATUS_CMD_Len - 1;
    BL_Host_Buffer[1] = CBL_GET_RDP_STATUS_CMD;
    CRC32_Value = Calculate_CRC32(BL_Host_Buffer, CBL_GET_RDP_STATUS_CMD_Len - 4);
    Serial.printf("Host CRC = 0x%x \n",CRC32_Value);
    BL_Host_Buffer[2] = (uint8_t)(CRC32_Value);
    BL_Host_Buffer[3] = (uint8_t)(CRC32_Value >> 8);
    BL_Host_Buffer[4] = (uint8_t)(CRC32_Value >> 16);
    BL_Host_Buffer[5] = (uint8_t)(CRC32_Value >> 24);
    Serial.printf("Sending Data to Bootloader : ");
    Send_Data_To_Bootloader(&BL_Host_Buffer[0], 1);
    Send_Data_To_Bootloader(&BL_Host_Buffer[1], CBL_GET_RDP_STATUS_CMD_Len - 1);
    Serial.printf("\n\n");
    Recieve_Data_From_Bootloader(2);
     if(BL_Host_Receive_Buffer[0] == CBL_SEND_ACK)
     {
        Serial.println("\nReceived Acknowledgement from Bootloader");
        Serial.println("\nCRC Verification Successful");
        Length_To_Follow = BL_Host_Receive_Buffer[1];
        Recieve_Data_From_Bootloader(Length_To_Follow);
        Process_CBL_GET_RDP_CMD();
     }
     else if (BL_Host_Receive_Buffer[0] == CBL_SEND_NACK)
     {
        Serial.println("\n   Received Not-Acknowledgement from Bootloader");
        Serial.println("\n   CRC Verification Failed");
        BootloaderReply.publish("CRC Verification Failed");
     }     
}

void BL_Host_Erase_Application(void)
{
   uint8_t CBL_FLASH_ERASE_CMD_Len = 6;
    uint32_t CRC32_Value =0;
    uint8_t Length_To_Follow = 0;
    BL_Host_Buffer[0] = CBL_FLASH_ERASE_CMD_Len - 1;
    BL_Host_Buffer[1] = CBL_FLASH_ERASE_CMD;
    CRC32_Value = Calculate_CRC32(BL_Host_Buffer, CBL_FLASH_ERASE_CMD_Len - 4);
    Serial.printf("Host CRC = 0x%x \n",CRC32_Value);
    BL_Host_Buffer[2] = (uint8_t)(CRC32_Value);
    BL_Host_Buffer[3] = (uint8_t)(CRC32_Value >> 8);
    BL_Host_Buffer[4] = (uint8_t)(CRC32_Value >> 16);
    BL_Host_Buffer[5] = (uint8_t)(CRC32_Value >> 24);
    Serial.printf("Sending Data to Bootloader : ");
    Send_Data_To_Bootloader(&BL_Host_Buffer[0], 1);
    Send_Data_To_Bootloader(&BL_Host_Buffer[1], CBL_FLASH_ERASE_CMD_Len - 1);
    Serial.printf("\n\n");
    Recieve_Data_From_Bootloader(2);
     if(BL_Host_Receive_Buffer[0] == CBL_SEND_ACK)
     {
        Serial.println("\nReceived Acknowledgement from Bootloader");
        Serial.println("\nCRC Verification Successful");
        Length_To_Follow = BL_Host_Receive_Buffer[1];
        Serial.println("\nErasing Application .......");
        BootloaderReply.publish (" Erasing Application .......");
        Recieve_Data_From_Bootloader_Noprint(Length_To_Follow);
        Process_CBL_FLASH_ERASE_CMD();
     }
     else if (BL_Host_Receive_Buffer[0] == CBL_SEND_NACK)
     {
        Serial.println("\n   Received Not-Acknowledgement from Bootloader");
        Serial.println("\n   CRC Verification Failed");
        BootloaderReply.publish("CRC Verification Failed");
     }  
}
void BL_Host_Jump_To_Application(void)
{
    uint8_t CBL_GO_TO_MAIN_APP_CMD_Len = 6;
    uint32_t CRC32_Value =0;
    uint8_t Length_To_Follow = 0;
    BL_Host_Buffer[0] = CBL_GO_TO_MAIN_APP_CMD_Len - 1;
    BL_Host_Buffer[1] = CBL_GO_TO_MAIN_APP_CMD;
    CRC32_Value = Calculate_CRC32(BL_Host_Buffer, CBL_GO_TO_MAIN_APP_CMD_Len - 4);
    Serial.printf("Host CRC = 0x%x \n",CRC32_Value);
    BL_Host_Buffer[2] = (uint8_t)(CRC32_Value);
    BL_Host_Buffer[3] = (uint8_t)(CRC32_Value >> 8);
    BL_Host_Buffer[4] = (uint8_t)(CRC32_Value >> 16);
    BL_Host_Buffer[5] = (uint8_t)(CRC32_Value >> 24);
    Serial.printf("Sending Data to Bootloader : ");
    Send_Data_To_Bootloader(&BL_Host_Buffer[0], 1);
    Send_Data_To_Bootloader(&BL_Host_Buffer[1], CBL_GO_TO_MAIN_APP_CMD_Len - 1);
    Serial.printf("\n\n");
    Recieve_Data_From_Bootloader(2);
     if(BL_Host_Receive_Buffer[0] == CBL_SEND_ACK)
     {
        Serial.println("\nReceived Acknowledgement from Bootloader");
        Serial.println("\nCRC Verification Successful");
        Length_To_Follow = BL_Host_Receive_Buffer[1];
        Recieve_Data_From_Bootloader(Length_To_Follow);
        Process_CBL_GO_TO_MAIN_APP_CMD();
     }
     else if (BL_Host_Receive_Buffer[0] == CBL_SEND_NACK)
     {
        Serial.println("\n   Received Not-Acknowledgement from Bootloader");
        Serial.println("\n   CRC Verification Failed");
        BootloaderReply.publish("CRC Verification Failed");
     }
}
void BL_Host_Flash_Application(void)
{
    uint32_t CBL_MEM_WRITE_CMD_Len = 0;
    uint32_t CRC32_Value =0;
    uint8_t Length_To_Follow = 0;   
    uint8_t Download_status = 0;
    uint32_t File_Total_Len = 0;
    uint32_t BinFileRemainingBytes = 0;
    uint32_t BinFileSentBytes = 0;
    uint32_t BaseMemoryAddress = 0;
    uint32_t BinFileReadLength = 0;
    uint8_t BinFileByteValue = 0;
    uint8_t Flash_write_status = 0;
    uint32_t Uploading_percentage =0;
    uint32_t Uploading_percentage_temp =0;
    char uploading_percentage_str[55] = {0};
     BootloaderReply.publish("Downloading Application .....");
    Download_status = FireBase_DownloadFile("FOTA_Application.bin","update.bin");
    if (Download_status == DOWNLOAD_FAILED)
    {
        BootloaderReply.publish("Application Download Failed");
    }
    else
    {
        BootloaderReply.publish("Application Download Successful");
    }
    File file = LittleFS.open("/update.bin", "r");
   // Get the total length of the binary file 
    File_Total_Len =  file.size();
    Serial.printf("Preparing writing a binary file with length %d Bytes\n\n",File_Total_Len);
    // Calculate the remaining payload 
    BinFileRemainingBytes = File_Total_Len;
    // Get the start address to write the payload 
    BaseMemoryAddress = 0x08004000;
    // Keep sending the write packet till the last payload byte
    delay(2000);
    while(BinFileRemainingBytes)
    {
        if(BinFileRemainingBytes >= 128)
        {
            BinFileReadLength = 128;
        }
        else
        {
            BinFileReadLength = BinFileRemainingBytes;
        }
        for (uint8_t BinFileByte = 0; BinFileByte < BinFileReadLength; BinFileByte++)
        {
            BinFileByteValue = file.read();
            BL_Host_Buffer[7 + BinFileByte] = BinFileByteValue;
        }
        BL_Host_Buffer[1] = CBL_MEM_WRITE_CMD;
        //Update the Host packet with the base address
        BL_Host_Buffer[2] = (uint8_t)(BaseMemoryAddress);
        BL_Host_Buffer[3] = (uint8_t)(BaseMemoryAddress >> 8);
        BL_Host_Buffer[4] = (uint8_t)(BaseMemoryAddress >> 16);
        BL_Host_Buffer[5] = (uint8_t)(BaseMemoryAddress >> 24);
     // Update the Host packet with the payload length 
        BL_Host_Buffer[6] = BinFileReadLength;
    // Update the Host packet with the packet length
        CBL_MEM_WRITE_CMD_Len = (BinFileReadLength + 11);
        BL_Host_Buffer[0] = CBL_MEM_WRITE_CMD_Len - 1;
        CRC32_Value = Calculate_CRC32(BL_Host_Buffer, CBL_MEM_WRITE_CMD_Len - 4);
        BL_Host_Buffer[7 + BinFileReadLength] = (uint8_t)(CRC32_Value);
        BL_Host_Buffer[8 + BinFileReadLength] = (uint8_t)(CRC32_Value >> 8);
        BL_Host_Buffer[9 + BinFileReadLength] = (uint8_t)(CRC32_Value >> 16);
        BL_Host_Buffer[10 + BinFileReadLength] = (uint8_t)(CRC32_Value >> 24);
          Uploading_percentage = (100 * (BinFileSentBytes) / File_Total_Len);
        if (Uploading_percentage != Uploading_percentage_temp)
        {
            sprintf(uploading_percentage_str, "Uploading Application .... ( %d %% )", Uploading_percentage);
            if(Uploading_percentage%10 == 0)
            {
            BootloaderReply.publish(uploading_percentage_str);
            }
            else if(Uploading_percentage ==99)
            {
            BootloaderReply.publish("Uploading Application .... ( 100 % )");
            }
            Serial.print(uploading_percentage_str);
            Serial.println();
        }
        Uploading_percentage_temp = Uploading_percentage;
     // Send the packet length to the bootloader  
        Send_Data_To_Bootloader_Noprint(&BL_Host_Buffer[0], 1);
        Send_Data_To_Bootloader_Noprint(&BL_Host_Buffer[1], CBL_MEM_WRITE_CMD_Len - 1);
     // Calculate the next Base memory address '''
        BaseMemoryAddress = BaseMemoryAddress + BinFileReadLength;    
    // Update the total number of bytes sent to the bootloader
        BinFileSentBytes = BinFileSentBytes + BinFileReadLength;
    //Calculate the remaining payload 
        BinFileRemainingBytes = File_Total_Len - BinFileSentBytes;
        Recieve_Data_From_Bootloader_Noprint(2);
     if(BL_Host_Receive_Buffer[0] == CBL_SEND_ACK)
     {
        Length_To_Follow = BL_Host_Receive_Buffer[1];
        Recieve_Data_From_Bootloader_Noprint(Length_To_Follow);
        Flash_write_status = Process_CBL_MEM_WRITE_CMD();
        if (Flash_write_status == FLASH_PAYLOAD_WRITE_FAILED)
        {
           break;
        }
     }
     else if (BL_Host_Receive_Buffer[0] == CBL_SEND_NACK)
     {
        Serial.println("\n   Received Not-Acknowledgement from Bootloader");
        Serial.println("\n   CRC Verification Failed");
        BootloaderReply.publish("CRC Verification Failed");
        break;
     }    
    }
    if (Flash_write_status == FLASH_PAYLOAD_WRITE_PASSED)
    {
        Serial.println("\nApplication Uploaded Successfully");
        BootloaderReply.publish("Application Uploaded Successfully");
    }
}
/**********************************************************************************************************************
 *  END OF FILE: Bootloader_Host.cpp
 *********************************************************************************************************************/
