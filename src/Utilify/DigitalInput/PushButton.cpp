#include <Utilify/DigitalInput/PushButton.h>

PushButton::PushButton(int pin)
    : TaskBase(),
      m_pin(pin),

      m_callbackKeyUp(nullptr),
      m_actionKeyUp(nullptr),

      m_callbackKeyDown(nullptr),
      m_actionKeyDown(nullptr),

      m_callbackKeyUpLongPress(nullptr),
      m_actionKeyUpLongPress(nullptr),

      m_callbackKeyDownLongPress(nullptr),
      m_actionKeyDownLongPress(nullptr) {
  pinMode(this->m_pin, INPUT_PULLUP);

  unsigned long currentTime = millis();
  this->m_lastStateChangeTime = currentTime;
  this->m_lastDownStateChangeTime = currentTime;

  this->m_lastButtonState = HIGH;
  this->m_lastStableButtonState = HIGH;
}

PushButton::PushButton(int pin, ActionBase<void>* actionKeyUp,
                       ActionBase<void>* actionKeyDown,
                       ActionBase<void>* actionKeyUpLongPress,
                       ActionBase<void>* actionKeyDownLongPress,
                       const unsigned int& longPressDelay)
    : PushButton(pin) {
  this->m_actionKeyUp = actionKeyUp;
  this->m_actionKeyDown = actionKeyDown;
  this->m_actionKeyUpLongPress = actionKeyUpLongPress;
  this->m_actionKeyDownLongPress = actionKeyDownLongPress;
  this->m_longPressDelay = longPressDelay;
}

PushButton::PushButton(int pin, Callback callbackKeyUp,
                       Callback callbackKeyDown,
                       Callback callbackKeyUpLongPress,
                       Callback callbackKeyDownLongPress,
                       const unsigned int& longPressDelay)
    : PushButton(pin) {
  this->m_callbackKeyUp = callbackKeyUp;
  this->m_callbackKeyDown = callbackKeyDown;
  this->m_callbackKeyUpLongPress = callbackKeyUpLongPress;
  this->m_callbackKeyDownLongPress = callbackKeyDownLongPress;
  this->m_longPressDelay = longPressDelay;
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

void PushButton::callbackKeyDownLongPress(
    ActionBase<void>* actionKeyDownLongPress) {
  this->m_actionKeyDownLongPress = actionKeyDownLongPress;
  this->m_callbackKeyDownLongPress = nullptr;
}

void PushButton::callbackKeyDownLongPress(Callback callbackKeyDownLongPress) {
  this->m_callbackKeyDownLongPress = callbackKeyDownLongPress;
  this->m_actionKeyDownLongPress = nullptr;
}

void PushButton::tick() {
  int buttonState = digitalRead(this->m_pin);
  unsigned long currentTime = millis();
  if (buttonState != m_lastButtonState) {
    m_lastStateChangeTime = currentTime;
    m_lastButtonState = buttonState;
  }
  if (currentTime - m_lastStateChangeTime > minPressDelay) {
    if (m_lastStableButtonState == HIGH && buttonState == LOW) {
      // Falling edge detection
      m_isLongPressDownTriggered = false;  // Reset long press down trigger
      if (m_actionKeyDown) {
        m_actionKeyDown->execute();
      } else if (m_callbackKeyDown) {
        m_callbackKeyDown();
      }
      m_lastDownStateChangeTime = currentTime;
    } else if (m_lastStableButtonState == LOW && buttonState == HIGH) {
      // Rising edge detection
      if ((m_actionKeyUpLongPress || m_callbackKeyUpLongPress) &&
          currentTime - m_lastDownStateChangeTime > this->m_longPressDelay) {
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
    } else if (m_lastStableButtonState == LOW && buttonState == LOW &&
               !m_isLongPressDownTriggered &&
               currentTime - m_lastDownStateChangeTime >
                   this->m_longPressDelay) {
      m_isLongPressDownTriggered = true;
      if (m_actionKeyDownLongPress) {
        m_actionKeyDownLongPress->execute();
      } else if (m_callbackKeyDownLongPress) {
        m_callbackKeyDownLongPress();
      }
    }
    m_lastStableButtonState = buttonState;
  }
}
