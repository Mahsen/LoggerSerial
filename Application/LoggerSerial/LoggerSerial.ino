
//// Camera libraries
//#include "esp_camera.h"
//#include "soc/soc.h"
//#include "soc/rtc_cntl_reg.h"
//#include "driver/rtc_io.h"

// MicroSD Libraries
#include "FS.h"
#include "SD_MMC.h"

// Delay time in millieconds
unsigned int Delay = 2000;

// Counter 
unsigned int Counter = 0;

void initMicroSDCard() {
  // Start the MicroSD card

  //Serial.println("Mounting MicroSD Card");
  if (!SD_MMC.begin()) {
    //Serial.println("MicroSD Card Mount Failed");
    return;
  }
  uint8_t cardType = SD_MMC.cardType();
  if (cardType == CARD_NONE) {
    //Serial.println("No MicroSD Card found");
    return;
  }

}

void takeNewRecord(String Text_v) {

  // Save picture to microSD card
  fs::FS &fs = SD_MMC;
  File file = fs.open("/Files.txt", FILE_APPEND);
  if (!file) {
    //Serial.println("Failed Open.");
  }
  else {
    //Serial.println("Opened.");
    Counter++;    
    if(file.printf("%d : %s\r\n", Counter, Text_v.c_str()))
    {
      //Serial.println("Saved.");    
    }
    else
    {
      //Serial.println("Failed Save."); 
    }
    file.close();
    //Serial.println("Closed.");
  }
}

void setup() {

  // Start Serial Monitor
  Serial.begin(9600);
  delay(2000);
  
  // Initialize the MicroSD
  //Serial.print("Initializing the MicroSD card module... ");
  initMicroSDCard();
}

void loop() {

  if(Serial.available()>0)
  {
    delay(Delay);
    takeNewRecord(Serial.readString());
  }

}
