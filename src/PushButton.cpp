#include "PushButton.h"

PushButton::PushButton(int pin, ActionBase<void>* action)
    : TaskBase(), m_pin(pin), m_action(action) {
  pinMode(this->m_pin, INPUT);

  this->m_lastStateChangeTime = 0;
  this->m_lastButtonState = HIGH;
  this->m_lastStableButtonState = HIGH;
}

PushButton::PushButton(int pin, Callback callback)
    : TaskBase(), m_pin(pin), m_callback(callback) {
  pinMode(this->m_pin, INPUT);

  this->m_lastStateChangeTime = 0;
  this->m_lastButtonState = HIGH;
  this->m_lastStableButtonState = HIGH;
}

void PushButton::callback(Callback callback) {
  this->m_callback = callback;
  this->m_action = nullptr;
}

void PushButton::action(ActionBase<void>* action) {
  this->m_action = action;
  this->m_callback = nullptr;
}

void PushButton::tick() {
  int buttonState = digitalRead(this->m_pin);
  long currentTime = millis();
  if (buttonState != m_lastButtonState) {
    m_lastStateChangeTime = currentTime;
    m_lastButtonState = buttonState;
  }
  if (currentTime - m_lastStateChangeTime > minPressDelay) {
    if (m_lastStableButtonState == LOW && buttonState == HIGH) {
      if (m_action) {
        m_action->execute();
      } else if (m_callback) {
        m_callback();
      }
    }
    m_lastStableButtonState = buttonState;
  }
}