#ifndef _KEYMAP_H
#define _KEYMAP_H
#include "mp3/card_content.h"

// Elegoo IR remote (from the Starter Kit for UNO)
// used with IRremote >= 3.x 

#define KEY_POWER (0xBA45FF00)
#define KEY_FUNC_STOP (0xB946FF00)
#define KEY_VOL_ADD (0xB847FF00)
#define KEY_FAST_BACK (0xBB44FF00)
#define KEY_PAUSE (0xBF40FF00)
#define KEY_FAST_FORWARD (0xBC43FF00)
#define KEY_DOWN (0xF807FF00)
#define KEY_VOL_DEC (0xEA15FF00)
#define KEY_UP (0xF609FF00)
#define KEY_EQ (0xE619FF00)
#define KEY_ST_REPT (0xF20DFF00)
#define KEY_0 (0xE916FF00)
#define KEY_1 (0xF30CFF00)
#define KEY_2 (0xE718FF00)
#define KEY_3 (0xA15EFF00)
#define KEY_4 (0xF708FF00)
#define KEY_5 (0xE31CFF00)
#define KEY_6 (0xA55AFF00)
#define KEY_7 (0xBD42FF00)
#define KEY_8 (0xAD52FF00)
#define KEY_9 (0xB54AFF00)

typedef struct {
    const uint32_t key;
    const char *name;
    const int index;
} keyMap;

const keyMap keyMapArr[] {
  { KEY_POWER, "POWER", MP3_ID_0000 },
  { KEY_FUNC_STOP, "FUNC/STOP", MP3_ID_0001 },
  { KEY_VOL_ADD, "VOL+", MP3_ID_0002 },
  { KEY_FAST_BACK, "FAST BACK", MP3_ID_0003 },
  { KEY_PAUSE, "PAUSE", MP3_ID_0004 },
  { KEY_FAST_FORWARD, "FAST FORWARD", MP3_ID_0005 },
  { KEY_DOWN, "DOWN", MP3_ID_0006 },
  { KEY_VOL_DEC, "VOL-", MP3_ID_0007 },
  { KEY_UP, "UP", MP3_ID_0008 },
  { KEY_EQ, "EQ", MP3_ID_0009 },
  { KEY_ST_REPT, "ST/REPT", MP3_ID_0010 },
  { KEY_0, "0", MP3_ID_0011 },
  { KEY_1, "1", MP3_ID_0012 },
  { KEY_2, "2", MP3_ID_0013 },
  { KEY_3, "3", MP3_ID_0014 },
  { KEY_4, "4", MP3_ID_0015 },
  { KEY_5, "5", MP3_ID_0016 },
  { KEY_6, "6", MP3_ID_0017 },
  { KEY_7, "7", MP3_ID_0018 },
  { KEY_8, "8", MP3_ID_0019 },
  { KEY_9, "9", MP3_ID_0020 },
};

keyMap * getKeyMap(uint32_t key) {
  for (uint8_t k = 0; k < sizeof(keyMapArr) / sizeof(keyMap); ++k) {
    if (keyMapArr[k].key == key) {
      return &keyMapArr[k];
    }
  }
  return NULL;
}

#endif
