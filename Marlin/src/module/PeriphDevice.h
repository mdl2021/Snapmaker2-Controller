#pragma once

#include "../inc/MarlinConfig.h"

//IO Switch Bits
#define PERIPH_IOSW_DOOR     1

#define PERIPH_FAN_COUNT 1

enum EnclosureEvent : uint8_t {
  ENCLOSURE_EVENT_NONE,
  ENCLOSURE_EVENT_OPEN,
  ENCLOSURE_EVENT_OPEN_FINISH,
  ENCLOSURE_EVENT_CLOSE,
  ENCLOSURE_EVENT_INVALID
};

class PeriphDevice 
{
public:
  PeriphDevice(){};
  void Init();
  #if ENABLED(DOOR_SWITCH)
    void DoorSwitchInit();
    void SetDoorCheck(bool Enable);
    void StartDoorCheck();
    void StopDoorCheck();
    FORCE_INLINE bool GetDoorCheckFlag() { return TEST(IOSwitch, PERIPH_IOSW_DOOR); } 
    bool IsDoorOpened();
    EnclosureEvent LatestEnclosureEvent() { return latest_enclosure_event_; }
    void LatestEnclosureEvent(EnclosureEvent);
  #else
    void DoorSwitchInit() {}
    void SetDoorCheck(bool Enable) {}
    void StartDoorCheck() {}
    void StopDoorCheck() {}
    FORCE_INLINE bool GetDoorCheckFlag() { return false; }
    FORCE_INLINE bool IsDoorOpened() { return true; }
  #endif

  uint8_t GetFanSpeed(uint8_t index) { return FanSpeed[index]; }

  #if ENABLED(CAN_FAN)
    void SetFanSpeed(uint8_t index, uint8_t DelayTime, uint8_t s_value);
    void SetEnclosureFanSpeed(uint8_t s_value);
  #endif
  
  void Process();

private:
  uint8_t FanSpeed[PERIPH_FAN_COUNT];
  EnclosureEvent latest_enclosure_event_;

public:
  uint8_t IOSwitch;
};

extern PeriphDevice Periph;
