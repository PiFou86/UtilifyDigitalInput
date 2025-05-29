# UtilifyDigitalInput

**UtilifyDigitalInput** is a library that provides a versatile collection of digital inputs for **Arduino** and **ESP32** platforms. Designed to simplify pushbutton management, it offers reliable detection of press, release, and long-press events while seamlessly integrating with the **Utilify** library.

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
[env:uno]
platform = atmelavr
board = uno
monitor_speed = 9600
lib_deps =
    https://github.com/PiFou86/Utilify.git
    https://github.com/PiFou86/UtilifyDigitalInput.git

[env:esp32doit-devkit-v1]
platform = espressif32
board = esp32doit-devkit-v1
monitor_speed = 115200
lib_deps =
    https://github.com/PiFou86/Utilify.git
    https://github.com/PiFou86/UtilifyDigitalInput.git
monitor_filters = esp32_exception_decoder
```

### Basic Usage

Include the library in your project and set up your callbacks to respond to various pushbutton events:

```cpp
#include <Arduino.h>
#include <Utilify/DigitalInput/PushButton.h>

PushButton* pushButton = nullptr;
void setup() {
  Serial.begin(115200);

  // Initialize the button on pin 2
  pushButton = new PushButton(2);

  // Set up the callback for button release (Key Up)
  pushButton->callbackKeyUp([]() {
    Serial.println("Up");
  });

  // Set up the callback for button press (Key Down)
  pushButton->callbackKeyDown([]() {
    Serial.println("Down");
  });

  // Set up the callback for a long press
  pushButton->callbackKeyUpLongPress([]() {
    Serial.println("Long press");
  });
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

**Pierre-François Léon @PiFou86** 
🔗 [Linkedin](https://www.linkedin.com/in/pierrefrancoisleon/)  
🔗 [GitHub Profile](https://github.com/PiFou86)
