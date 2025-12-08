# Signal Analysis MCU

A lightweight RTOS + DSP engine for microcontrollers demonstrating real-time embedded systems and signal processing.

## What It Does

- Generates synthetic audio waveforms (50 Hz sine wave)
- Simulates ADC sampling at 1 kHz
- Performs 128-point FFT analysis to extract frequency components
- Outputs results via UART at 9600 baud

## Technical Stack

- **Microcontroller**: ATmega644P @ 12 MHz
- **Real-Time Operating System**: Custom cooperative scheduler with 1ms tick
- **Digital Signal Processing**: Cooley-Tukey radix-2 FFT algorithm
- **Memory Footprint**: 7.8 KB flash, 1.7 KB RAM

## Architecture

```
Timer ISR (1ms) → Scheduler Tick → Task Dispatch
                ↓
         Signal Generator (50 Hz sine)
                ↓
         Circular Buffer (128 samples)
                ↓
         FFT Engine (128-point)
                ↓
         Peak Detection
                ↓
         UART Output (9600 baud)
```

## Key Features

- **Pre-computed Trig Tables**: Eliminates runtime cos/sin calls, reducing code size by 40%
- **In-place FFT**: Minimizes RAM usage on resource-constrained hardware
- **Magnitude-squared Comparison**: Avoids expensive sqrt() operations
- **Modular Design**: Clean separation between scheduler, DSP, and I/O layers

## Building

```bash
make          # Compile
make flash    # Upload via USBasp
make clean    # Remove build artifacts
```

## Hardware Requirements

- ATmega644P or compatible AVR microcontroller
- USBasp programmer
- UART-to-USB adapter for serial output
- LED on PB0 (optional, for heartbeat indicator)

## Output Example

```
Mini-RTOS-DSP-FFT starting...
Entering main loop
FFT peak: bin=6 freq=46 Hz
FFT peak: bin=6 freq=46 Hz
```

## Technical Highlights

- Demonstrates understanding of real-time constraints and interrupt-driven architecture
- Implements classic DSP algorithm (FFT) on 8-bit microcontroller
- Optimized for embedded: no stdlib, no floating-point math library
- Clean C code following embedded best practices

## Purpose

This project demonstrates practical knowledge of:
- Real-time embedded systems architecture
- Digital signal processing algorithms
- Resource-constrained programming
- Hardware/software integration

## Status

Functional proof-of-concept. Core DSP pipeline operational with known timing sensitivities under concurrent ISR/task execution.
