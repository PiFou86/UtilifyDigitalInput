#pragma once

#include <Arduino.h>
#include <Utilify/Action/ActionBase.h>
#include <Utilify/Callback.h>
#include <Utilify/Task/TaskBase.h>

// Pull-up resistor is used
class PushButton : public TaskBase {
 public:
  PushButton(int pin, ActionBase<void>* action = nullptr);
  PushButton(int pin, Callback callback);

  void callback(Callback callback);
  void action(ActionBase<void>* action);

  void tick() override;

 private:
  uint8_t m_pin;

  Callback m_callback;
  ActionBase<void>* m_action;

  long m_lastStateChangeTime;
  int m_lastButtonState;
  int m_lastStableButtonState;

  static const int minPressDelay = 25;  // ms
};
