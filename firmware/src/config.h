#ifndef CONFIG_H
#define CONFIG_H

// ============================================================
// ESP32-C3 BLE Proximity Device
// ============================================================

// Hardware
constexpr uint8_t LED_PIN = 2;
constexpr uint8_t BUTTON_PIN = 9;

// BLE service used to identify another proximity device.
// Both devices advertise this same service UUID.
#define PROXIMITY_SERVICE_UUID "7b7c0001-7b7c-4e4d-9b01-000000000001"

// BLE device name
#define DEVICE_NAME "ESP32-C3-Proximity"

// ------------------------------------------------------------
// RSSI proximity configuration
// ------------------------------------------------------------
// Estimation :
// -50 dBm  -> relatively strong
// -70 dBm  -> weaker
//
// ------------------------------------------------------------

constexpr int RSSI_NEAR_THRESHOLD = -65;
constexpr int RSSI_FAR_THRESHOLD  = -72;

// RSSI exponential moving average.
// Higher value = more smoothing but slower response.
constexpr float RSSI_FILTER_ALPHA = 0.25f;

// How long the peer can disappear before we declare FAR.
constexpr unsigned long PEER_TIMEOUT_MS = 2500;

// BLE scan configuration
constexpr uint32_t SCAN_DURATION_MS = 0;

// Advertising interval.
// BLE units are 0.625 ms.
// 160 = 100 ms.
constexpr uint16_t ADVERTISING_INTERVAL = 160;

#endif
