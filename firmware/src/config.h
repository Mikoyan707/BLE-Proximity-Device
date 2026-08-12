#ifndef CONFIG_H
#define CONFIG_H

// ============================================================
// ESP32-C3 BLE Proximity Device
// Hardware pin configuration
// ============================================================

// Proximity / status LED
// GPIO2 drives the base of Q1 through R4.
#define LED_PIN 2

// User push button SW2
// Hardware pull-up: 10 kΩ to 3.3 V
// Button connects GPIO9 to GND when pressed.
#define BUTTON_PIN 9

#endif
