# ESP32-C3 BLE Proximity Firmware

Firmware for the ESP32-C3 based BLE proximity detection device.

The system is designed around two identical ESP32-C3 devices that continuously advertise and scan for each other over Bluetooth Low Energy (BLE). The received signal strength indicator (RSSI) is used as an approximation of proximity between the two devices.

When the detected device is sufficiently close according to the configured RSSI thresholds, the firmware changes the proximity state to `NEAR` and activates the onboard LED output.

---

## System Overview

Two identical devices operate simultaneously:

```text
              BLE
       ┌─────────────────┐
       │                 │
       ▼                 ▼
┌─────────────┐     ┌─────────────┐
│  Device A   │     │  Device B   │
│  ESP32-C3   │◄───►│  ESP32-C3   │
└──────┬──────┘     └──────┬──────┘
       │                   │
       │ RSSI              │ RSSI
       ▼                   ▼
┌─────────────────────────────────┐
│       Proximity Processing      │
│                                 │
│  RSSI acquisition               │
│        ↓                        │
│  RSSI filtering                 │
│        ↓                        │
│  Threshold + hysteresis         │
│        ↓                        │
│  NEAR / FAR classification      │
└───────────────┬─────────────────┘
                │
                ▼
          GPIO2 output
                │
                ▼
             LED / Q1
