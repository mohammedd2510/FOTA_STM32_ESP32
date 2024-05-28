#ifndef FIRE_BASE_H
#define FIRE_BASE_H
/****************** Includes*********************************/
#include <Firebase_ESP_Client.h>
#include <LittleFS.h>

/****************** Macros *********************************/

#define DOWNLOAD_SUCCESSFULL 0x01
#define DOWNLOAD_FAILED 0x00
/* 1. Define the API Key */
#define API_KEY ""

/* 2. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL ""
#define USER_PASSWORD ""

/* 3. Define the Firebase storage bucket ID e.g bucket-name.appspot.com */
#define STORAGE_BUCKET_ID ""

/****************** extern Firebase Objects *********************************/

// extern Firebase Data object
extern FirebaseData fbdo;

extern FirebaseAuth auth;
extern FirebaseConfig config;


/****************** Global Functions Prototypes *********************************/
void FireBase_Init();


void fcsDownloadCallback(FCS_DownloadStatusInfo info);

void readFile(const char *path);

uint8_t FireBase_DownloadFile(std::string server_file , std::string local_file);


#endif