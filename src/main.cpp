#include <Arduino.h>

#include <Utilify/DigitalInput/PushButton.h>

PushButton* pushButton = nullptr;
void setup() {
  Serial.begin(115200);

  pushButton = new PushButton(2);

  pushButton->callbackKeyUp([]() {
    Serial.println("Up");
  });

  pushButton->callbackKeyDown([]() {
    Serial.println("Down");
  });

  pushButton->callbackKeyUpLongPress([]() {
    Serial.println("Long press");
  });
}

void loop() {
  pushButton->tick();
}
