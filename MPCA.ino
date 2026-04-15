#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define DATA_PIN 11
#define CLK_PIN 13
#define CS_PIN 10

MD_Parola display = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Message Queue
#define MAX_MSG 10
String messageQueue[MAX_MSG];
int msgCount = 0;
int currentMsg = 0;

// Controls
int speedDelay = 100;
int brightness = 5;
bool isPaused = false;
bool scrollLeft = true;
bool systemOn = true;

// UNDO VARIABLES
String lastMessage = "";
int lastIndex = -1;
String lastAction = "";

// NEW FEATURES
String mode = "normal";
String emergencyMsg = "";
String infoMsg = "INFO MODE";
bool modeInitialized = false;

void setup() {
  Serial.begin(9600);

  display.begin();
  display.setIntensity(brightness);
  display.displayClear();

  messageQueue[0] = "WELCOME TO PES";
  messageQueue[1] = "MICROPROCESSOR PROJECT";
  messageQueue[2] = "DIGITAL NOTICE BOARD";
  msgCount = 3;

  display.displayScroll(messageQueue[currentMsg].c_str(), PA_LEFT, PA_SCROLL_LEFT, speedDelay);

  Serial.println("Commands:");
  Serial.println("on/off = start/stop");
  Serial.println("p = Pause/Resume");
  Serial.println("f/s = Speed");
  Serial.println("b/d = Brightness");
  Serial.println("r = Reverse");
  Serial.println("clear = Remove All");
  Serial.println("remove = Delete Last");
  Serial.println("del X = Delete Index");
  Serial.println("undo = Undo last action");

  Serial.println("mode normal/info/emergency");
  Serial.println("emergency YOUR_MSG");
  Serial.println("info YOUR_MSG");
  Serial.println("status");
  Serial.println("edit X NEW_MSG");   // 🔥 NEW
}

void loop() {

  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.startsWith("mode ")) {
      mode = input.substring(5);
      modeInitialized = false;
    }

    else if (input.startsWith("emergency ")) {
      emergencyMsg = input.substring(10);
      mode = "emergency";
      modeInitialized = false;
    }

    else if (input.startsWith("info ")) {
      infoMsg = input.substring(5);
      mode = "info";
      modeInitialized = false;
    }

    else if (input == "status") {
      Serial.println("---- STATUS ----");
      Serial.print("Messages: "); Serial.println(msgCount);
      Serial.print("Speed: "); Serial.println(speedDelay);
      Serial.print("Brightness: "); Serial.println(brightness);
      Serial.print("Mode: "); Serial.println(mode);
    }

    // 🔥 EDIT FEATURE
    else if (input.startsWith("edit ")) {
      int firstSpace = input.indexOf(' ');
      int secondSpace = input.indexOf(' ', firstSpace + 1);

      if (secondSpace != -1) {
        int index = input.substring(firstSpace + 1, secondSpace).toInt();
        String newMsg = input.substring(secondSpace + 1);

        if (index >= 0 && index < msgCount) {
          messageQueue[index] = newMsg;
          Serial.println("Message updated");
          modeInitialized = false;
        } else {
          Serial.println("Invalid index");
        }
      }
    }

    else if (input == "off") {
      systemOn = false;
      display.displayClear();
    }

    else if (input == "on") {
      systemOn = true;
      modeInitialized = false;
    }

    else if (input == "p") {
      isPaused = !isPaused;
    }

    else if (input == "f") {
      speedDelay = max(20, speedDelay - 20);
    }

    else if (input == "s") {
      speedDelay += 20;
    }

    else if (input == "b") {
      brightness = min(15, brightness + 1);
      display.setIntensity(brightness);
    }

    else if (input == "d") {
      brightness = max(0, brightness - 1);
      display.setIntensity(brightness);
    }

    else if (input == "r") {
      scrollLeft = !scrollLeft;
      modeInitialized = false;
    }

    else if (input == "clear") {
      msgCount = 0;
      currentMsg = 0;
      display.displayClear();
    }

    else if (input == "remove") {
      if (msgCount > 0) {
        lastAction = "remove";
        lastMessage = messageQueue[msgCount - 1];
        lastIndex = msgCount - 1;
        msgCount--;
        if (currentMsg >= msgCount) currentMsg = 0;
      }
    }

    else if (input.startsWith("del ")) {
      int index = input.substring(4).toInt();

      if (index >= 0 && index < msgCount) {
        lastAction = "delete";
        lastMessage = messageQueue[index];
        lastIndex = index;

        for (int i = index; i < msgCount - 1; i++) {
          messageQueue[i] = messageQueue[i + 1];
        }

        msgCount--;

        if (currentMsg >= msgCount) currentMsg = 0;
      }
    }

    else if (input == "undo") {

      if (lastAction == "add") {
        if (msgCount > 0) msgCount--;
      }

      else if (lastAction == "remove") {
        if (msgCount < MAX_MSG) {
          messageQueue[msgCount] = lastMessage;
          msgCount++;
        }
      }

      else if (lastAction == "delete") {
        if (msgCount < MAX_MSG) {
          for (int i = msgCount; i > lastIndex; i--) {
            messageQueue[i] = messageQueue[i - 1];
          }
          messageQueue[lastIndex] = lastMessage;
          msgCount++;
        }
      }

      lastAction = "";
    }

    else {
      if (msgCount < MAX_MSG) {
        lastAction = "add";
        lastMessage = input;
        lastIndex = msgCount;

        messageQueue[msgCount] = input;
        msgCount++;
      }
    }
  }

  if (!systemOn) return;

  // EMERGENCY MODE
  
if (mode == "emergency") {
  static unsigned long lastBlink = 0;
  static bool blink = true;

  // Start scrolling once
  if (!modeInitialized) {
    display.displayScroll(emergencyMsg.c_str(), PA_LEFT, PA_SCROLL_LEFT, 80);
    modeInitialized = true;
  }

  // 🔥 RESTART SCROLL WHEN FINISHED
  if (display.displayAnimate()) {
    display.displayReset();   // restart same message
  }

  // Blinking effect
  if (millis() - lastBlink > 300) {
    blink = !blink;
    lastBlink = millis();
    display.setIntensity(blink ? brightness : 0);
  }

  return;
}
  // INFO MODE
  if (mode == "info") {
    if (!modeInitialized) {
      display.displayClear();
      display.displayText(infoMsg.c_str(), PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
      modeInitialized = true;
    }
    display.displayAnimate();
    return;
  }

  // NORMAL MODE
  if (!isPaused && msgCount > 0) {
    if (display.displayAnimate()) {
      currentMsg = (currentMsg + 1) % msgCount;

      display.displayScroll(messageQueue[currentMsg].c_str(), PA_LEFT,
        scrollLeft ? PA_SCROLL_LEFT : PA_SCROLL_RIGHT, speedDelay);
    }
  }
}