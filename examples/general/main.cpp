#include <Arduino.h>
#include <Utilify/DigitalInput/PushButton.h>

PushButton* pushButton = nullptr;
bool LED_state = false;
void setup() {
#ifdef ARDUINO_AVR_UNO
  Serial.begin(9600);
#elif defined(ESP32) || defined(ARDUINO_UNOR4_MINIMA) || \
    defined(ARDUINO_UNOWIFIR4)
  Serial.begin(115200);
#else
#error "Unsupported board"
#endif
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB devices
  }

  pinMode(LED_BUILTIN, OUTPUT);
  LED_state = digitalRead(LED_BUILTIN);

  pushButton = new PushButton(2);

  pushButton->callbackKeyUp([]() {
    LED_state = !LED_state;
    digitalWrite(LED_BUILTIN, LED_state);
    Serial.println("Up");
  });

  pushButton->callbackKeyDown([]() {
    Serial.println("Down");
  });

  pushButton->callbackKeyUpLongPress([]() {
    Serial.println("Long press up");
  });

  pushButton->callbackKeyDownLongPress([]() {
    Serial.println("Long press down");
  });

  pushButton->longPressDelay(3000); // Set long press delay to 3 seconds
}

void loop() {
  pushButton->tick();
}
