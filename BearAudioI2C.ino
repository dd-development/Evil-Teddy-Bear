#include <SoftwareSerial.h>
#include <DFMiniMp3.h>
#include <Wire.h>

// forward declare the notify class, just the name
class Mp3Notify; 

// Using software serial so RX and TX can be open for communication between other boards
SoftwareSerial secondarySerial(10, 11); // RX, TX
typedef DFMiniMp3<SoftwareSerial, Mp3Notify> DfMp3; // typedef for DFMiniMp3 object
DfMp3 dfmp3(secondarySerial); // declare our dfmp3 instance

// Notification class will send double finish notifications because that's how the chip was made, probably for a reason but I have no idea what it is
// Therefore, we need to ignore the first notification so we don't try to spam play a single file (refer to OnPlayFinished in the notification class)
// firstNotif variable exists to make this check and do nothing if it's 0, and play the next file if it's 1 and reset
// isPlaying is just to check if a file is currently being played, since this function isn't present in the library
int firstNotif = 0;
int isPlaying = 0;

unsigned long prev = 0;

// implement a notification class,
// its member methods will get called 
//
class Mp3Notify
{
public:
  static void PrintlnSourceAction(DfMp3_PlaySources source, const char* action)
  {
    if (source & DfMp3_PlaySources_Sd) 
    {
        Serial.print("SD Card, ");
    }
    if (source & DfMp3_PlaySources_Usb) 
    {
        Serial.print("USB Disk, ");
    }
    if (source & DfMp3_PlaySources_Flash) 
    {
        Serial.print("Flash, ");
    }
    Serial.println(action);
  }
  static void OnError([[maybe_unused]] DfMp3& mp3, uint16_t errorCode)
  {
    // see DfMp3_Error for code meaning
    Serial.println();
    Serial.print("Com Error ");
    Serial.println(errorCode);
  }
  static void OnPlayFinished([[maybe_unused]] DfMp3& mp3, [[maybe_unused]] DfMp3_PlaySources source, uint16_t track)
  {
    if (firstNotif == 0) {
      firstNotif = 1;
    }
    else {
      firstNotif = 0;
      Serial.print("Play finished for #");
      Serial.println(track);

      isPlaying = 0;
      prev = millis();
    }
  }
  static void OnPlaySourceOnline([[maybe_unused]] DfMp3& mp3, DfMp3_PlaySources source)
  {
    PrintlnSourceAction(source, "online");
  }
  static void OnPlaySourceInserted([[maybe_unused]] DfMp3& mp3, DfMp3_PlaySources source)
  {
    PrintlnSourceAction(source, "inserted");
  }
  static void OnPlaySourceRemoved([[maybe_unused]] DfMp3& mp3, DfMp3_PlaySources source)
  {
    PrintlnSourceAction(source, "removed");
  }
};

void setup()
{
  Wire.begin(1);
  Wire.onReceive(changeAngerLevel);

  Serial.begin(9600);

  Serial.println("initializing...");
  
  dfmp3.begin();
  // for boards that support hardware arbitrary pins
  // dfmp3.begin(10, 11); // RX, TX

  // during development, it's a good practice to put the module
  // into a known state by calling reset().  
  // You may hear popping when starting and you can remove this 
  // call to reset() once your project is finalized
  dfmp3.reset();

  uint16_t version = dfmp3.getSoftwareVersion();
  Serial.print("version ");
  Serial.println(version);

  uint16_t volume = dfmp3.getVolume();
  Serial.print("volume ");
  Serial.println(volume);
  dfmp3.setVolume(20);
  
  uint16_t count = dfmp3.getTotalTrackCount(DfMp3_PlaySource_Sd);
  Serial.print("files ");
  Serial.println(count);
  
  Serial.println("starting...");
}

byte angerLevel = 1;

void changeAngerLevel(int numBytesRead) {
  angerLevel = Wire.read();
  Serial.println("ANGER LEVEL:");
  Serial.println((int)angerLevel);
}

void loop() 
{
  if (isPlaying == 0 && (millis() - prev >= 3000)) {
    isPlaying = 1;

    if (angerLevel == 1) {
      int randNum = random(1, 6);
      dfmp3.playFolderTrack(1, randNum);
    }
    else if (angerLevel == 2) {
      int randNum = random(1, 6);
      dfmp3.playFolderTrack(2, randNum);
    }
    else if (angerLevel == 3) {
      int randNum = random(1, 6);
      dfmp3.playFolderTrack(3, randNum);
    }
    else if (angerLevel == 4) {
      int randNum = random(1, 5);
      dfmp3.playFolderTrack(4, randNum);
    }
    else if (angerLevel == 5) {
      dfmp3.playFolderTrack(5, 1);
    }
  }
  dfmp3.loop();
}
