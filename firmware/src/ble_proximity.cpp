#include <Arduino.h>
#include <NimBLEDevice.h>

#include "config.h"
#include "ble_proximity.h"
#include "proximity.h"

// ============================================================
// BLE service used by both proximity devices
// ============================================================

static NimBLEUUID proximityServiceUUID(
    PROXIMITY_SERVICE_UUID
);

// ============================================================
// Scan callback
// ============================================================

class ProximityScanCallbacks : public NimBLEScanCallbacks
{
public:

    void onResult(
        const NimBLEAdvertisedDevice* advertisedDevice
    ) override
    {
        // Ignore devices that don't advertise our service.
        if (!advertisedDevice->haveServiceUUID())
        {
            return;
        }

        if (!advertisedDevice->isAdvertisingService(
                proximityServiceUUID))
        {
            return;
        }

        // Ignore our own device if it appears in scan results.
        if (advertisedDevice->getAddress() ==
            NimBLEDevice::getAddress())
        {
            return;
        }

        int rssi = advertisedDevice->getRSSI();

        Serial.printf(
            "[BLE] Proximity device found | %s | RSSI: %d dBm\n",
            advertisedDevice->getAddress().toString().c_str(),
            rssi
        );

        updateRSSI(rssi);
    }

    void onScanEnd(
        const NimBLEScanResults& results,
        int reason
    ) override
    {
        Serial.printf(
            "[BLE] Scan ended | reason=%d | devices=%d\n",
            reason,
            results.getCount()
        );

        // Restart scanning.
        NimBLEDevice::getScan()->start(
            SCAN_DURATION_MS,
            false,
            true
        );
    }
};

static ProximityScanCallbacks scanCallbacks;

// ============================================================
// BLE initialization
// ============================================================

void bleProximityInit()
{
    Serial.println("[BLE] Initializing...");

    NimBLEDevice::init(DEVICE_NAME);

    // --------------------------------------------------------
    // Create a GATT server.
    //
    // The server itself is not used for data exchange here.
    // Its service UUID allows the devices to identify each
    // other during scanning.
    // --------------------------------------------------------

    NimBLEServer* server = NimBLEDevice::createServer();

    NimBLEService* service =
        server->createService(proximityServiceUUID);

    service->start();

    // --------------------------------------------------------
    // Configure advertising
    // --------------------------------------------------------

    NimBLEAdvertising* advertising =
        NimBLEDevice::getAdvertising();

    advertising->addServiceUUID(
        proximityServiceUUID
    );

    advertising->setName(DEVICE_NAME);

    // Advertising interval.
    advertising->setMinInterval(
        ADVERTISING_INTERVAL
    );

    advertising->setMaxInterval(
        ADVERTISING_INTERVAL
    );

    advertising->start();

    Serial.println("[BLE] Advertising started.");

    // --------------------------------------------------------
    // Configure scanning
    // --------------------------------------------------------

    NimBLEScan* scan = NimBLEDevice::getScan();

    scan->setScanCallbacks(
        &scanCallbacks,
        false
    );

    scan->setActiveScan(true);

    // We process results in callbacks instead of storing
    // a large scan-result list.
    scan->setMaxResults(0);

    // Start continuous scanning.
    scan->start(
        SCAN_DURATION_MS,
        false,
        true
    );

    Serial.println("[BLE] Continuous scanning started.");
}
