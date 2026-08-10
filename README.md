# ESP32-C3 BLE Proximity Device

A two-node Bluetooth Low Energy (BLE) proximity detection system based on the **ESP32-C3**, designed to detect when two dedicated devices come within a defined proximity range.

The project combines a custom-designed PCB with ESP32-C3 BLE communication and an RSSI-based proximity detection algorithm. Each device continuously scans for its counterpart and uses the received BLE signal strength to determine whether the other device has entered the configured proximity region.

> **Project Status:** Hardware design completed. Firmware development, RSSI calibration, and physical testing are in progress.

---

## Overview

The system consists of two identical BLE-enabled devices.

Each device:

1. Advertises its BLE identity.
2. Continuously scans for the corresponding device.
3. Detects the other device when its BLE advertisement is received.
4. Measures the received signal strength indicator (RSSI).
5. Filters the RSSI measurements to reduce short-term fluctuations.
6. Applies a configurable proximity threshold.
7. Activates the local output when the other device enters the defined proximity region.

The system is intended to operate without requiring a smartphone or external gateway.

### Basic Concept

```text
             BLE Proximity Link

        Device A                 Device B
     ┌─────────────┐          ┌─────────────┐
     │ ESP32-C3    │          │ ESP32-C3    │
     │             │          │             │
     │ Advertise   │◄────────►│ Advertise   │
     │ Scan        │   BLE    │ Scan        │
     │ RSSI        │          │ RSSI        │
     │ Processing  │          │ Processing  │
     └──────┬──────┘          └──────┬──────┘
            │                        │
            ▼                        ▼
         Output                   Output
```

---

## Key Features

* Two-node standalone BLE proximity system
* ESP32-C3 based design
* BLE advertising and scanning
* Dedicated device identification
* RSSI-based proximity estimation
* RSSI filtering for improved stability
* Configurable proximity threshold
* Hysteresis-based proximity decision
* Custom PCB designed in KiCad
* CR2032 battery-powered hardware design
* 3.3 V regulated power supply
* Local LED/output indication
* Firmware structured for future expansion

---

## Hardware

The custom PCB is built around the **ESP32-C3-MINI-1-N4** module.

### Main Hardware

| Component             | Function                                        |
| --------------------- | ----------------------------------------------- |
| ESP32-C3-MINI-1-N4    | Main MCU and BLE controller                     |
| CR2032                | Battery supply                                  |
| AP2112K-3.3           | 3.3 V voltage regulator                         |
| LED                   | Proximity/status indication                     |
| Transistor stage      | LED/output driving                              |
| Push buttons          | User/control input                              |
| Decoupling capacitors | Power supply stabilization                      |
| Resistors             | Pull-ups, current limiting and transistor drive |

The complete schematic and PCB design are available in the [`hardware`](hardware/) directory.

---

## Hardware Design

### Schematic

The complete KiCad schematic is available at:

```text
hardware/schematic/
```

The repository will contain both the editable KiCad schematic and an exported version for easy viewing.

### PCB

The PCB has been designed specifically for the ESP32-C3 based proximity device.

```text
hardware/pcb/
```

The directory contains the editable PCB design and exported PCB views.

### 3D Design

3D renders of the PCB are provided in:

```text
hardware/3d/
```

These views are intended to document the physical board layout and component placement.

---

## Proximity Detection

The system uses **BLE RSSI** as an indicator of relative proximity.

A simplified detection pipeline is:

```text
BLE Advertisement
        │
        ▼
Device Identification
        │
        ▼
RSSI Measurement
        │
        ▼
RSSI Filtering
        │
        ▼
Proximity Decision
        │
    ┌───┴───┐
    ▼       ▼
   NEAR     FAR
    │       │
    ▼       ▼
 Output   Output
   ON       OFF
```

RSSI is not treated as an exact distance measurement because it is affected by antenna orientation, obstacles, multipath propagation, human-body absorption, and the surrounding environment.

Therefore, the project will use experimental calibration to determine a suitable operating threshold for the intended application.

---

## Firmware

Firmware development is currently in progress.

The planned firmware architecture consists of separate modules for:

```text
firmware/
├── src/
│   ├── main.cpp
│   ├── ble_proximity.cpp
│   ├── ble_proximity.h
│   ├── proximity.cpp
│   ├── proximity.h
│   ├── led.cpp
│   ├── led.h
│   └── config.h
│
└── platformio.ini
```

The firmware will progressively implement:

* GPIO initialization
* Output/LED control
* BLE advertising
* BLE scanning
* Device identification
* RSSI acquisition
* RSSI filtering
* Proximity state detection
* Hysteresis
* Timing/debounce logic
* Final proximity indication

---

## RSSI Filtering

Raw RSSI measurements can fluctuate considerably even when two devices remain stationary.

For this reason, the firmware will process multiple RSSI measurements rather than making a proximity decision from a single sample.

The planned processing chain is:

```text
Raw RSSI
   │
   ▼
Filtering
   │
   ▼
Filtered RSSI
   │
   ▼
Threshold + Hysteresis
   │
   ▼
Proximity State
```

The filtering method and threshold values will be finalized after measurements are collected from the actual hardware.

---

## Calibration

The proximity threshold will be experimentally determined using the completed devices.

Measurements will be collected at different physical separations and under different orientations.

Example measurement format:

| Distance | RSSI |
| -------: | ---: |
|    0.5 m |  TBD |
|    1.0 m |  TBD |
|    1.5 m |  TBD |
|    2.0 m |  TBD |
|    3.0 m |  TBD |
|    4.0 m |  TBD |

These values will be replaced with measurements from the physical hardware.

Detailed calibration results will be documented in:

```text
documentation/RSSI_calibration.md
```

---

## Repository Structure

```text
ESP32-C3-BLE-Proximity/
│
├── README.md
├── LICENSE
│
├── hardware/
│   ├── schematic/
│   ├── pcb/
│   ├── 3d/
│   └── fabrication/
│
├── firmware/
│   ├── src/
│   └── test/
│
├── documentation/
│
├── images/
│
└── results/
```

---

## Development Roadmap

### Hardware

* [ ] Schematic design
* [ ] PCB layout
* [ ] 3D PCB design/review
* [ ] PCB fabrication
* [ ] Physical hardware assembly
* [ ] Hardware validation

### Firmware

* [ ] GPIO test
* [ ] BLE advertising
* [ ] BLE scanning
* [ ] Device identification
* [ ] RSSI measurement
* [ ] RSSI filtering
* [ ] Proximity threshold
* [ ] Hysteresis
* [ ] LED/output control
* [ ] Two-device testing
* [ ] Final firmware optimization

### Documentation

* [ ] Initial hardware documentation
* [ ] Firmware architecture
* [ ] BLE protocol documentation
* [ ] RSSI calibration
* [ ] Experimental results
* [ ] Final performance analysis

---

## Limitations

The primary proximity estimation method is based on BLE RSSI.

RSSI-based proximity estimation does not provide a universally accurate physical distance because the measured signal strength depends on the environment and device orientation.

Potential sources of variation include:

* Antenna orientation
* Obstacles
* Human-body effects
* Multipath propagation
* Reflections
* Transmit power
* Device-to-device orientation
* Environmental RF interference

The final operating threshold will therefore be selected experimentally rather than assuming a fixed RSSI-to-distance relationship.

---

## Future Improvements

Potential future developments include:

* Improved RSSI filtering
* Adaptive proximity thresholds
* Low-power BLE operation
* Battery-life optimization
* Improved proximity-state stability
* Additional user feedback mechanisms
* Enclosure design
* More extensive environmental testing
* Multiple proximity zones
* Improved ranging techniques beyond basic RSSI

---

## Tools Used

* **KiCad** — Schematic and PCB design
* **ESP32-C3** — Embedded controller and BLE
* **PlatformIO / Arduino framework** — firmware development
* **Git / GitHub** — Version control and project documentation

---

## Project Status

This project is under active development.

The custom hardware design is being documented first, followed by firmware implementation, RSSI calibration, physical testing, and final performance evaluation.

---

## License

This project is released under the **MIT License**.

See `LICENSE` for details.
