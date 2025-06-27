#pragma once

#include <Arduino.h>
#include <Utilify/Action/ActionBase.h>
#include <Utilify/Callback.h>
#include <Utilify/Task/TaskBase.h>

// Pull-up resistor is used
class PushButton : public TaskBase {
 public:
  PushButton(int pin);
  PushButton(int pin, 
             ActionBase<void>* actionKeyUp, 
             ActionBase<void>* actionKeyDown = nullptr, 
             ActionBase<void>* actionKeyUpLongPress = nullptr,
             ActionBase<void>* actionKeyDownLongPress = nullptr,
             const unsigned int& longPressDelay = 3000);
  PushButton(int pin, 
             Callback callbackKeyUp, 
             Callback callbackKeyDown = nullptr,
             Callback callbackKeyUpLongPress = nullptr,
             Callback callbackKeyDownLongPress = nullptr,
             const unsigned int& longPressDelay = 3000);

  void callbackKeyUp(Callback callbackKeyUp);
  void callbackKeyUp(ActionBase<void>* actionKeyUp);

  void callbackKeyDown(Callback callbackKeyDown);
  void callbackKeyDown(ActionBase<void>* actionKeyDown);

  void callbackKeyUpLongPress(Callback callbackKeyUpLongPress);
  void callbackKeyUpLongPress(ActionBase<void>* actionKeyUpLongPress);

  void callbackKeyDownLongPress(Callback callbackKeyDownLongPress);
  void callbackKeyDownLongPress(ActionBase<void>* actionKeyDownLongPress);

  inline void longPressDelay(unsigned int longPressDelay) {
    if (longPressDelay >= minPressDelay) {
      this->m_longPressDelay = longPressDelay;
    }
  }
  inline unsigned int longPressDelay() const {
    return this->m_longPressDelay;
  }

  void tick() override;

 private:
  uint8_t m_pin;

  Callback m_callbackKeyUp;
  ActionBase<void>* m_actionKeyUp;

  Callback m_callbackKeyDown;
  ActionBase<void>* m_actionKeyDown;

  Callback m_callbackKeyUpLongPress;
  ActionBase<void>* m_actionKeyUpLongPress;

  Callback m_callbackKeyDownLongPress;
  ActionBase<void>* m_actionKeyDownLongPress;

  unsigned long m_lastStateChangeTime;
  unsigned long m_lastDownStateChangeTime;
  int m_lastButtonState;
  int m_lastStableButtonState;

  unsigned int m_longPressDelay = 3000;  // ms, default long press delay

  bool m_isLongPressDownTriggered = false;

  static const int minPressDelay = 25;  // ms
};
