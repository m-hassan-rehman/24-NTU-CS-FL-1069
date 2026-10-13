
// Home Task - OLED Display with Button Counter
// This program initializes an OLED display and counts button presses on an ESP32.

// Name: Abdul Ahad 
// Registration Number: 24-NTU-CS-FL-1051

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_ADDR 0x3C


#define BUTTON_PIN 18
#define DEBOUNCE_MS 50


Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    -1
);


int pressCount = 0;

int lastRawState = HIGH;
int stableButtonState = HIGH;

unsigned long lastDebounceTime = 0;


void updateDisplay() {
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 0);
    display.println("ESP32 BUTTON COUNTER");

    display.println("---------------------");

    display.print("Button: ");

    if (stableButtonState == LOW) {
        display.println("PRESSED");
    } else {
        display.println("RELEASED");
    }

    display.println();

    display.setTextSize(2);
    display.print("Count: ");
    display.println(pressCount);

    display.display();
}

void setup() {
    Serial.begin(115200);

    
    Wire.begin(OLED_SDA, OLED_SCL);

   
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    
    if (!display.begin(
            SSD1306_SWITCHCAPVCC,
            OLED_ADDR
        )) {
        Serial.println("OLED initialization failed!");

        while (true) {
           
        }
    }

    
    lastRawState = digitalRead(BUTTON_PIN);
    stableButtonState = lastRawState;

    
    updateDisplay();

    Serial.println("OLED initialized successfully.");
    Serial.println("Button counter ready.");
    Serial.println("Press count: 0");
}

void loop() {
  
    int reading = digitalRead(BUTTON_PIN);

    
    if (reading != lastRawState) {
        lastDebounceTime = millis();
        lastRawState = reading;
    }

   
    if (millis() - lastDebounceTime >= DEBOUNCE_MS) {

        if (reading != stableButtonState) {
            stableButtonState = reading;

            
            if (stableButtonState == LOW) {
                pressCount++;

                Serial.print("Accepted press! Count: ");
                Serial.println(pressCount);
            }

            updateDisplay();
        }
    }

    
}
