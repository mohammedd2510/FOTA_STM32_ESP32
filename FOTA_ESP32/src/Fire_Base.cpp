#include "Fire_Base.h"


/****************** Define Firebase Objects *********************************/

// Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

/****************** Firebase Global Functions Definition *******************************/
void FireBase_Init() 
{
    Serial.printf("\nFirebase Client v%s\n", FIREBASE_CLIENT_VERSION);
    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    Firebase.reconnectNetwork(true);

    // Since v4.4.x, BearSSL engine was used, the SSL buffer need to be set.
    // Large data transmission may require larger RX buffer, otherwise connection issue or data read time out can be occurred.
    fbdo.setBSSLBufferSize(4096 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);

    /* Assign download buffer size in byte */
    // Data to be downloaded will read as multiple chunks with this size, to compromise between speed and memory used for buffering.
    // The memory from external SRAM/PSRAM will not use in the TCP client internal rx buffer.
    config.fcs.download_buffer_size = 2048;

    Firebase.begin(&config, &auth);
    Serial.println("Connected to FireBase Server\n");
}

void fcsDownloadCallback(FCS_DownloadStatusInfo info)
{
    if (info.status == firebase_fcs_download_status_init)
    {
        Serial.printf("Downloading file %s (%d) to %s\n", info.remoteFileName.c_str(), info.fileSize, info.localFileName.c_str());
    }
    else if (info.status == firebase_fcs_download_status_download)
    {
        Serial.printf("Downloaded %d%s, Elapsed time %d ms\n", (int)info.progress, "%", info.elapsedTime);
    }
    else if (info.status == firebase_fcs_download_status_complete)
    {
        Serial.println("Download completed\n");
    }
    else if (info.status == firebase_fcs_download_status_error)
    {
        Serial.printf("Download failed, %s\n", info.errorMsg.c_str());
    }
}
void readFile(const char *path)
{
  File file = LittleFS.open(path, "r");
  if(!file)
  {
    Serial.println("Failed to open file");
    return;
  }
  Serial.println("Read from file:");
  while(file.available())
  {
    Serial.print(file.read(), HEX);
    Serial.print(' ');
  }
  file.close();
}
uint8_t FireBase_DownloadFile(std::string server_file , std::string local_file)
{
    uint8_t Download_status = DOWNLOAD_SUCCESSFULL;
    local_file.insert(0,1,'/');
    while(!(Firebase.ready()));
    Serial.println("\nDownload file...\n");
  
    // The file systems for flash and SD/SDMMC can be changed in FirebaseFS.h.
    if (!Firebase.Storage.download(&fbdo, STORAGE_BUCKET_ID /* Firebase Storage bucket id */, server_file /* path of remote file stored in the bucket */,local_file  /* path to local file */, mem_storage_type_flash /* memory storage type, mem_storage_type_flash and mem_storage_type_sd */, fcsDownloadCallback /* callback function */)){
        Serial.println(fbdo.errorReason());
        Download_status = DOWNLOAD_FAILED;
        }            
    return Download_status;
}