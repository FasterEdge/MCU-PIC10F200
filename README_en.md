<div align="center">
<img src="https://avatars.githubusercontent.com/u/245985800?s=200&v=4" style="width:100px;" width="100"/>
<h2>FasterEdge MCU - PIC10F200</h2>
<h3>FasterEdge framework on PIC10F200 (MPLAB-X / PlatformIO editions)</h3>
</div>

### 1. Introduction

This repo implements the **[FasterEdge](https://github.com/FasterEdge/FasterEdge)** framework on the **Microchip PIC10F200** in minimal form. The PIC10F200 is an 8-bit core with **only 256 words (12-bit) of program memory, 16B RAM, 4MHz, no UART/ADC/I2C** — one of the smallest MCUs, unable to host the full capability set. Following the "**register-only base control**" design, it is trimmed to GPIO control + chip info.

- ✅ **mplab_x/ (MPLAB-X + XC8, C)** + **platformio_ide/ (MPASM assembly)** dual editions
- ✅ Register-level GPIO control (direct TRIS/GPIO)
- ✅ Minimal command set fitting 16B RAM / 256-word program limit

### 2. Implemented Capabilities (minimal subset)

| Name | Type | Commands/Function | Description |
|------|------|-------------------|-------------|
| `GpioAbility` | Ability | `mode` / `write` / `read` | GP0 output (LED), GP1 input (button), register-level |
| `ChipData` | Data | `info` | chip info (fixed string) |

**Example (main loop):** button GP1 pressed → light GP0, else off.

### 3. Excluded Capabilities

| Capability | Reason |
|------------|--------|
| Base/Role/Time/OneKey/Serial/Modbus/RegAbility | No UART (no serial command channel), RAM only 16B, program only 256 words |
| ConfigData | No EEPROM/Flash to persist |
| All network abilities | PIC10F200 has no network |

### 4. Directory Layout

```
MCU-PIC10F200/
├── mplab_x/                    # MPLAB-X + XC8 (C compiler)
│   ├── pic10f200.h             # register map / pin constants
│   ├── fe_port.h               # porting layer (GPIO / info)
│   └── src/main.c              # register-level GPIO demo
└── platformio_ide/             # PlatformIO + microchippic (MPASM)
    ├── platformio.ini          # board = pic10f200
    └── src/main.asm            # MPASM assembly (GP0 out / GP1 in)
```

> PIC10F200 has no UART; both editions demo **register-level GPIO control** and do not provide a serial command interpreter.

### 5. Usage

1. **mplab_x edition**: MPLAB-X → New Project → device PIC10F200 → compiler XC8 → add `src/main.c` → Build + Program (PICkit/Snap)
2. **platformio_ide edition**: `cd platformio_ide && pio run -t upload` (microchippic platform, MPASM)
3. Wiring: GP0 → LED (series resistor), GP1 → button

### 6. Platform Differences

| Aspect | ESP32/ESP8266 | PIC10F200 |
|--------|---------------|-----------|
| Architecture | Xtensa 32-bit | **8-bit (12-bit instructions)** |
| Program / RAM | KB~MB | **256 words / 16B** |
| Peripherals | WiFi/UART/ADC etc | **GPIO + TMR0 only** |
| Serial | Yes | **No (software emulation unrealistic)** |
| Storage | NVS / Flash | **None (OTP one-time programmable)** |

### 7. Capability Trimming Notes

The PIC10F200 is the tightest-resource MCU in this family; it only does **register-level GPIO base control**. For the full capability set, switch to [MCU-C51](../MCU-C51) / [MCU-CH32V003](../MCU-CH32V003) and other larger-resource platforms.

### 8. Sibling Projects

- **[FasterEdge MCU - C51](https://github.com/FasterEdge/MCU-C51)**: 8-bit 8051 (256B+ RAM, full capabilities)
- **[FasterEdge MCU - CH32V003](https://github.com/FasterEdge/MCU-CH32V003)**: RISC-V, 16KB/2KB
- **[FasterEdge MCU - Arduino Uno R3](https://github.com/FasterEdge/MCU-Arduino-Uno-R3)**: 8-bit AVR
- **[FasterEdge](https://github.com/FasterEdge/FasterEdge)**: framework main repo
