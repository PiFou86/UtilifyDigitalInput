# UtilifyDigitalInput

**UtilifyDigitalInput** is a library that provides a versatile collection of digital inputs for **Arduino** and **ESP32** platforms. Designed to simplify pushbutton management, it offers reliable detection of press, release, and long-press events while seamlessly integrating with the **Utilify** library.

[![PlatformIO Registry](https://badges.registry.platformio.org/packages/sirdrako/library/UtilifyDigitalInput.svg)](https://registry.platformio.org/libraries/sirdrako/UtilifyDigitalInput)

## Features

- **Pushbutton Management**: Detects button presses, releases, and long presses.
- **Callbacks and Actions**: Assign custom behaviors using callback functions or action objects.
- **Built-in Debouncing**: Ensures stable input readings by filtering out unwanted signal noise.
- **Wide Compatibility**: Works on **Arduino** (Atmel AVR) and **ESP32** as well as other supported platforms.
- **Easy Integration**: Easily integrates into your PlatformIO projects.

## Getting Started

### Installation

To add **UtilifyDigitalInput** to your PlatformIO project, include the library in your `platformio.ini` file:

```ini
lib_deps =
    sirdrako/Utilify
    sirdrako/UtilifyDigitalInput
```

### Basic Usage

Include the library in your project and set up your callbacks to respond to various pushbutton events:

```cpp
#include <Arduino.h>
#include <Utilify/DigitalInput/PushButton.h>

PushButton* pushButton = nullptr;
bool LED_state = false;
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB devices
  }

  pinMode(LED_BUILTIN, OUTPUT);
  LED_state = digitalRead(LED_BUILTIN);

  // Initialize the button on pin 2
  pushButton = new PushButton(2);

  // Set up the callback for button release (Key Up)
  pushButton->callbackKeyUp([]() {
    LED_state = !LED_state;
    digitalWrite(LED_BUILTIN, LED_state);
    Serial.println("Up");
  });

  // Set up the callback for button press (Key Down)
  pushButton->callbackKeyDown([]() {
    Serial.println("Down");
  });

  // Set up the callback for a long press
  pushButton->callbackKeyUpLongPress([]() {
    Serial.println("Long press up");
  });

  pushButton->callbackKeyDownLongPress([]() {
    Serial.println("Long press down");
  });

  pushButton->longPressDelay(3000); // Set long press delay to 3 seconds
}

void loop() {
  // Update the button state
  pushButton->tick();
}
```

When you press and release the button, the terminal will display "Down" followed by "Up". A prolonged press will trigger "Long press" on the serial monitor.

## Feature Overview

### Pushbutton Management

The PushButton class allows you to define different behaviors for each event:

- `callbackKeyUp`: Assigns an action or callback for when the button is released.
- `callbackKeyDown`: Assigns an action or callback for when the button is pressed.
- `callbackKeyUpLongPress`: Assigns an action or callback for detecting a long press.

These methods provide great flexibility in customizing your application's response to button interactions.

### Built-in Debouncing

A debouncing mechanism is implemented to ensure that only stable state transitions (after a minimum delay) trigger events, reducing false positives caused by rapid signal fluctuations.

### Integration with Utilify

UtilifyDigitalInput depends on the Utilify library, ensuring seamless integration with other utilities and facilitating the development of robust embedded applications.

## Dependencies

The library depends on the following:

- [Utilify](https://github.com/PiFou86/Utilify): Core utilities for string manipulation, timer and device-specific operations.

## Author

**Pierre-François Léon**

[![LinkedIn](https://img.shields.io/badge/LinkedIn-Profile-blue?logo=linkedin&style=for-the-badge)](https://www.linkedin.com/in/pierrefrancoisleon/)
[![GitHub profile](https://img.shields.io/badge/GitHub-Profile-blue?logo=github&style=for-the-badge)](https://github.com/PiFou86)
