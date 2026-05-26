# STM32 LiDAR + GPS + IMU Emulation Firmware

## Overview

This project is an STM32 firmware application designed to emulate and synchronize:

* GPS timing messages (NMEA GPRMC)
* IMU sensor acquisition
* LiDAR synchronization timing
* Camera hardware triggering

The firmware is implemented on an STM32F103 MCU using STM32 HAL drivers generated from STM32CubeMX.

The project combines:

* UART communication
* DMA transfers
* I2C IMU acquisition
* External interrupt synchronization
* Timer-based PPS timing
* Hardware PWM triggering

---

# Setup / Build / Flash Guide

## Requirements

Required tools:

* STM32CubeIDE
* ST-Link Utility or STM32CubeProgrammer
* ST-Link V2 programmer/debugger

---

## Build Procedure

1. Open the project in STM32CubeIDE.
2. Select:

```text
Project -> Build Configurations -> Set Active -> Release
```

3. Build the firmware:

```text
Project -> Build Project
```

The generated binary will be located in:

```text
/Release
```

---

## Flash Procedure

1. Connect the ST-Link programmer to the STM32F103 Bluepill.
2. Open ST-Link Utility or STM32CubeProgrammer.
3. Connect to target.
4. Load the generated `.hex` or `.bin` file.
5. Flash the firmware.

---

## Post-Flash Procedure

After flashing completes:

1. Restart or power-cycle the STM32.
2. The firmware becomes fully operational after reboot.

This restart sequence is required to correctly initialize synchronization peripherals and DMA state machines.

---

## Recovery Procedure

In case of synchronization failure or unexpected runtime behavior:

```text
Reboot the STM32 device.
```

No additional recovery sequence is required.

---

# Build Environment

Generated using:

* STM32CubeMX
* STM32 HAL
* STM32CubeIDE

Target MCU family:

```text
STM32F1xx
```

In this particular project we used STM32F103 Bluepill.

---

# Main Features

## GPS NMEA Emulation

The firmware periodically generates a valid `$GPRMC` NMEA sentence and transmits it over UART using DMA.

Example generated sentence:

```text
$GPRMC,121530,A,4808.0000,N,01706.0000,E,0.0,0.0,090323,,,A*XX
```

The checksum is dynamically calculated before transmission.

### GPS Transmission Flow

1. Timer event occurs
2. Internal software clock increments
3. Firmware generates GPRMC message
4. NMEA checksum is calculated
5. Message is transmitted via UART1 DMA

---

# IMU Acquisition

The firmware interfaces with a 6DOF IMU over I2C.

The IMU driver supports:

* Accelerometer configuration
* Gyroscope configuration
* Temperature acquisition
* Raw burst reading
* WHO_AM_I verification
* Device reset

Files involved:

* `Core/Src/IMU.c`
* `Core/Inc/IMU.h`

---

# Synchronization Architecture

## External Interrupt Synchronization

The IMU data-ready pin triggers an EXTI interrupt.

Inside the interrupt:

* Current timer ticks are captured
* Timestamp metadata is appended
* DMA-safe acquisition flags are set

This enables:

* precise timestamping
* synchronization between LiDAR/GPS/IMU streams
* deterministic acquisition timing

---

# UART Configuration

## USART1

Used for:

* GPS NMEA transmission

Configuration:

* Baudrate: 9600
* DMA enabled

## USART2

Used for:

* IMU raw data output
* Debug messages

Configuration:

* Baudrate: 115200

---

# Timer Configuration

## TIM1

TIM1 is used as the primary synchronization timer. It generates a 1 Hz PPS signal for LiDAR timestamping and serves as the high-resolution timing provider for IMU timestamps.

For ARR we used a value close to the maximum of unsigned 16-bit range for maximal timestamp resolution.

Timer configuration:

* Prescaler = 1200 - 1
* Period = 60000 - 1
* PWM enabled
* PWM pulse = 30000

---

## TIM2

TIM2 is used for camera hardware triggering.

The timer is configured as PWM output and generates a periodic trigger pulse suitable for external camera synchronization.

Timer configuration:

* Prescaler = 7199
* Period = 999
* PWM pulse = 500

### TIM2 Frequency Calculation

System clock:

```text
72 MHz
```

Timer input clock:

```text
72 MHz / 7200 = 10 kHz
```

PWM frequency:

```text
10 kHz / 1000 = 10 Hz
```

Therefore:

```text
TIM2 trigger frequency = 10 Hz
```

PWM duty cycle:

```text
500 / 1000 = 50%
```

This timer provides periodic camera trigger pulses at 10 Hz.

---

# Timing Calculations

## System Clock

The MCU uses:

* External HSE oscillator
* PLL x9 multiplier

Typical STM32F103 clock:

```text
8 MHz × 9 = 72 MHz
```

Therefore:

```text
SYSCLK = 72 MHz
```

---

## TIM1 Tick Frequency

Timer prescaler:

```text
PSC = 1200
```

Timer clock:

```text
72 MHz / 1200 = 60 kHz
```

Timer tick period:

```text
1 / 60000 = 16.67 us
```

---

## TIM1 Overflow Period

Timer period:

```text
ARR = 60000
```

Overflow frequency:

```text
60000 / 60000 Hz = 1 second
```

Therefore:

```text
TIM1 overflow period = 1 second
```

This timer is used as a PPS-like timing source.

---

# PPS Timing Logic

LiDAR datasheet specifies, that GPRMC should be transmitted after the falling edge of PPS. In our case that is 500ms. This feature is implemented utilizing interrupts for falling edge of PPS, which sets the GPRMC flag, that controls the transmission of GPRMC.

This ensures:

* LiDAR synchronization alignment in compliance with the datasheet
* stable PPS edge timing
* deterministic timestamping

---

# DMA Usage

DMA is used for UART GPS transmission.

Advantages:

* reduced CPU load of main loop
* non-blocking UART transfers
* better timing determinism

---

# Interrupt Callbacks Used

The project heavily relies on HAL callbacks.

Implemented callbacks include:

* `HAL_GPIO_EXTI_Callback`
* `HAL_TIM_PeriodElapsedCallback`
* `HAL_I2C_MemRxCpltCallback`
* `HAL_I2C_ErrorCallback`

These callbacks provide:

* asynchronous sensor acquisition
* event-driven synchronization
* timestamp handling

---

# IMU Data Packet Structure

The firmware allocates:

```c
#define IMU_DATA_RAW_SIZE (14 + 4 + 2)
```

Packet composition:

| Section         | Size     |
| --------------- | -------- |
| IMU raw data    | 14 bytes |
| Timestamp major | 2 bytes  |
| Timestamp minor | 2 bytes  |
| Line ending     | 2 bytes  |

Total:

```text
20 bytes
```

---

# Software Architecture

## Main Loop Responsibilities

The main loop performs:

1. GPS message scheduling
2. IMU DMA state handling
3. I2C memory reads
4. Synchronization management
5. Camera trigger timing management

The architecture is primarily:

* interrupt-driven
* DMA-assisted
* non-blocking

---

# Important Source Files

| File      | Purpose                   |
| --------- | ------------------------- |
| `main.c`  | Main application logic    |
| `IMU.c`   | IMU driver implementation |
| `IMU.h`   | IMU driver interface      |
| `usart.c` | UART configuration        |
| `tim.c`   | Timer configuration       |
| `gpio.c`  | GPIO initialization       |
| `i2c.c`   | I2C configuration         |

---

# How It Works

## High-Level Flow

### GPRMC Emulation

```text
TIM1 -> PPS timing
        ↓
Generate GPS message
        ↓
Transmit GPS over UART DMA
```

### IMU Data Acquisition

```text
IMU DRDY interrupt occurs
        ↓
Timestamp captured
        ↓
I2C burst read starts
        ↓
IMU data sent over UART2
```

### Camera Hardware Triggering

```text
TIM2 PWM output
        ↓
10 Hz trigger generation
        ↓
Camera trigger pulse
```

---


# Notes

The project is focused on precise timing synchronization between:

* GPS timing
* LiDAR triggering
* IMU acquisition
* Camera hardware triggering

The implementation uses efficient embedded techniques:

* DMA
* interrupts
* timestamping
* asynchronous transfers
* PWM synchronization

This makes the firmware suitable for real-time sensor synchronization applications.
