#pragma once

#include <Arduino.h>
#include <Utilify/Action/ActionBase.h>
#include <Utilify/Callback.h>
#include <Utilify/Task/TaskBase.h>

// Pull-up resistor is used
class PushButton : public TaskBase {
 public:
  PushButton(int pin);
  PushButton(int pin, ActionBase<void>* actionKeyUp);
  PushButton(int pin, Callback callbackKeyUp);

  void callbackKeyUp(Callback callbackKeyUp);
  void callbackKeyUp(ActionBase<void>* actionKeyUp);

  void callbackKeyDown(Callback callbackKeyDown);
  void callbackKeyDown(ActionBase<void>* actionKeyDown);

  void callbackKeyUpLongPress(Callback callbackKeyUpLongPress);
  void callbackKeyUpLongPress(ActionBase<void>* actionKeyUpLongPress);

  void tick() override;

 private:
  uint8_t m_pin;

  Callback m_callbackKeyUp;
  ActionBase<void>* m_actionKeyUp;

  Callback m_callbackKeyDown;
  ActionBase<void>* m_actionKeyDown;

  Callback m_callbackKeyUpLongPress;
  ActionBase<void>* m_actionKeyUpLongPress;

  long m_lastStateChangeTime;
  int m_lastButtonState;
  int m_lastStableButtonState;

  static const int minPressDelay = 25;  // ms
  static const int longPressDelay = 3000;  // ms
};
