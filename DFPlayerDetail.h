#ifndef _DFPLAYER_DETAIL_H
#define _DFPLAYER_DETAIL_H

#ifdef _DFPLAYER_DETAIL

void printDetail(uint8_t type, int value) {
  switch (type) {
    case TimeOut:
      DEBUG_PRINTLN(F("Time Out!"));
      break;
    case WrongStack:
      DEBUG_PRINTLN(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      DEBUG_PRINTLN(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      DEBUG_PRINTLN(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      DEBUG_PRINTLN(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      DEBUG_PRINTLN("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      DEBUG_PRINTLN("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      DEBUG_PRINT(F("Number: "));
      DEBUG_PRINT(value);
      DEBUG_PRINTLN(F(" Play Finished!"));
      break;
    case DFPlayerError:
      DEBUG_PRINT(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          DEBUG_PRINTLN(F("Card not found"));
          break;
        case Sleeping:
          DEBUG_PRINTLN(F("Sleeping"));
          break;
        case SerialWrongStack:
          DEBUG_PRINTLN(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          DEBUG_PRINTLN(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          DEBUG_PRINTLN(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          DEBUG_PRINTLN(F("Cannot Find File"));
          break;
        case Advertise:
          DEBUG_PRINTLN(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
#endif

#endif
