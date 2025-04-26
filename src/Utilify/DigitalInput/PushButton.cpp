#include <Utilify/DigitalInput/PushButton.h>

PushButton::PushButton(int pin)
    : TaskBase(),
      m_pin(pin),

      m_callbackKeyUp(nullptr),
      m_actionKeyUp(nullptr),

      m_callbackKeyDown(nullptr),
      m_actionKeyDown(nullptr),

      m_callbackKeyUpLongPress(nullptr),
      m_actionKeyUpLongPress(nullptr) {
  pinMode(this->m_pin, INPUT);

  this->m_lastStateChangeTime = 0;
  this->m_lastButtonState = HIGH;
  this->m_lastStableButtonState = HIGH;
}

PushButton::PushButton(int pin, ActionBase<void>* actionKeyUp)
    : PushButton(pin) {
  this->m_actionKeyUp = actionKeyUp;
}

PushButton::PushButton(int pin, Callback callbackKeyUp)
    : PushButton(pin) {
  this->m_callbackKeyUp = callbackKeyUp;
}

void PushButton::callbackKeyUp(Callback callbackKeyUp) {
  this->m_callbackKeyUp = callbackKeyUp;
  this->m_actionKeyUp = nullptr;
}

void PushButton::callbackKeyUp(ActionBase<void>* action) {
  this->m_actionKeyUp = action;
  this->m_callbackKeyUp = nullptr;
}

void PushButton::callbackKeyDown(Callback callbackKeyDown) {
  this->m_callbackKeyDown = callbackKeyDown;
  this->m_actionKeyDown = nullptr;
}

void PushButton::callbackKeyDown(ActionBase<void>* actionKeyDown) {
  this->m_actionKeyDown = actionKeyDown;
  this->m_callbackKeyDown = nullptr;
}

void PushButton::callbackKeyUpLongPress(Callback callbackKeyUpLongPress) {
  this->m_callbackKeyUpLongPress = callbackKeyUpLongPress;
  this->m_actionKeyUpLongPress = nullptr;
}

void PushButton::callbackKeyUpLongPress(
    ActionBase<void>* actionKeyUpLongPress) {
  this->m_actionKeyUpLongPress = actionKeyUpLongPress;
  this->m_callbackKeyUpLongPress = nullptr;
}

void PushButton::tick() {
  int buttonState = digitalRead(this->m_pin);
  long currentTime = millis();
  if (buttonState != m_lastButtonState) {
    m_lastStateChangeTime = currentTime;
    m_lastButtonState = buttonState;
  }
  if (currentTime - m_lastStateChangeTime > minPressDelay) {
    if (m_lastStableButtonState == HIGH && buttonState == LOW) {
      if (m_actionKeyDown) {
        m_actionKeyDown->execute();
      } else if (m_callbackKeyDown) {
        m_callbackKeyDown();
      }
    } else if (m_lastStableButtonState == LOW && buttonState == HIGH) {
      if (currentTime - m_lastStateChangeTime > longPressDelay) {
        if (m_actionKeyUpLongPress) {
          m_actionKeyUpLongPress->execute();
        } else if (m_callbackKeyUpLongPress) {
          m_callbackKeyUpLongPress();
        }
      } else if (m_actionKeyUp) {
        m_actionKeyUp->execute();
      } else if (m_callbackKeyUp) {
        m_callbackKeyUp();
      }
    }
    m_lastStableButtonState = buttonState;
  }
}