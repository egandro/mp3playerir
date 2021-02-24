#include "IRremote.h"
#if !defined VERSION_IRREMOTE_MAJOR || VERSION_IRREMOTE_MAJOR < 3
#error please update IRremote library to version >= 3
#endif

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#define _SIMPLEDEBUG
#include "SimpleDebug.h"

// #define _DFPLAYER_DETAIL
#include "DFPlayerDetail.h"

#include "KeyMap.h"

#define IR_RECEIVE_PIN 6
#define DFPLAYER_RX_PIN 10
#define DFPLAYER_TX_PIN 11

#define IR_LED_FEEDBACK ENABLE_LED_FEEDBACK
// #define IR_LED_FEEDBACK DISABLE_LED_FEEDBACK

SoftwareSerial softwareSerial(DFPLAYER_RX_PIN, DFPLAYER_TX_PIN); // RX, TX
DFRobotDFPlayerMini dfPlayer;

void setup()
{
  DEBUG_INIT(9600);
  //DEBUG_WAIT(true);

  DEBUG_PRINTLN("IR Receiver Button Decode");
  IrReceiver.begin(IR_RECEIVE_PIN, IR_LED_FEEDBACK);

  // Use softwareSerial to communicate with mp3
  softwareSerial.begin(9600);
  if (!dfPlayer.begin(softwareSerial))
  {
    DEBUG_PRINTLN(F("Unable to begin:"));
    DEBUG_PRINTLN(F("1.Please recheck the connection!"));
    DEBUG_PRINTLN(F("2.Please insert the SD card!"));
    pinMode(LED_BUILTIN, OUTPUT);
    while (true)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
      delay(1000);
    }
  }

  dfPlayer.setTimeOut(500); //Set serial communication time out 500ms
  dfPlayer.volume(25);      //Set volume value (0~30).
  dfPlayer.EQ(DFPLAYER_EQ_NORMAL);
  dfPlayer.outputDevice(DFPLAYER_DEVICE_SD);
}

void loop()
{
  handleIR();

#ifdef _DFPLAYER_DETAIL
  if (dfPlayer.available())
  {
    printDetail(dfPlayer.readType(), dfPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
#endif
}

void playMp3(keyMap *map, boolean isRepeat)
{
  static keyMap *lastMap = NULL;

  if (map == NULL)
  {
    return;
  }

  DEBUG_PRINT("keyName: ");
  DEBUG_PRINTLN(map->name);

  if (isRepeat)
  {
    DEBUG_PRINTLN(" (REPEAT)");
  }

  if (dfPlayer.readState() != 512) // 512 is stop state of the player
  {
    // not idle
    if (lastMap != NULL && lastMap->index == map->index)
    {
      // still playing the last song
      DEBUG_PRINTLN(" already playing");
      return;
    }
  }

  dfPlayer.playMp3Folder(map->index);
  lastMap = map;
}

void handleIR()
{
  const unsigned long handleIRCallFreq = 500;
  unsigned long currentTime = millis();

  static keyMap *lastMap = NULL;
  static unsigned long startTime = millis();

  if (currentTime - startTime < handleIRCallFreq)
  {
    return;
  }

  startTime = currentTime;

  if (IrReceiver.decode()) // have we received an IR signal?
  {
    boolean isRepeat = false;
    keyMap *map = getKeyMap(IrReceiver.decodedIRData.decodedRawData);
    if (map != NULL)
    {
      lastMap = map;
    }
    else
    {
      if (IrReceiver.decodedIRData.flags == 0)
      {
        // we detected a key but it is unknown to us
        DEBUG_PRINT(" unknown: ");
        DEBUG_PRINTLN(IrReceiver.decodedIRData.decodedRawData);
        lastMap = NULL;
      }
      else if (lastMap != NULL && IrReceiver.decodedIRData.flags && IRDATA_FLAGS_IS_REPEAT)
      {
        isRepeat = true;
        //        DEBUG_PRINT("isRepeat lastKey: ");
        //        DEBUG_PRINT(lastMap->key);
        //        DEBUG_PRINT(" lastKeyName: ");
        //        DEBUG_PRINTLN(lastMap->name);
      }
      //      else
      //      {
      //        DEBUG_PRINT("decodedRawData: ");
      //        DEBUG_PRINT(IrReceiver.decodedIRData.decodedRawData);
      //        DEBUG_PRINT(" IrReceiver.decodedIRData.flags ");
      //        DEBUG_PRINTLN(IrReceiver.decodedIRData.flags);
      //      }
    }

    if (map != NULL)
    {
      playMp3(map, false);
    }
    else if (lastMap != NULL && isRepeat)
    {
      DEBUG_PRINT(" lastKeyName: ");
      DEBUG_PRINTLN(lastMap->name);
      playMp3(lastMap, true);
    }

    IrReceiver.resume(); // receive the next value
  }
}
