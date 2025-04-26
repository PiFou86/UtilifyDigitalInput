#include <Arduino.h>
#include <Utilify/DigitalInput/PushButton.h>

PushButton* pushButton = nullptr;
void setup() {
#ifdef ARDUINO_AVR_UNO
  Serial.begin(9600);
#elif defined(ESP32) || defined(ARDUINO_UNOR4_MINIMA) || \
    defined(ARDUINO_UNOWIFIR4)
  Serial.begin(115200);
#else
#error "Unsupported board"
#endif
  pushButton = new PushButton(2);

  pushButton->callbackKeyUp([]() { Serial.println("Up"); });

  pushButton->callbackKeyDown([]() { Serial.println("Down"); });

  pushButton->callbackKeyUpLongPress([]() { Serial.println("Long press"); });
}

void loop() { pushButton->tick(); }
