<div align="center">
<img src="https://avatars.githubusercontent.com/u/245985800?s=200&v=4" style="width:100px;" width="100"/>
<h2>FasterEdge MCU - PIC10F200</h2>
<h3>FasterEdge 框架的 PIC10F200 平台实现（MPLAB-X / PlatformIO 版）</h3>
</div>

### 一、简介

本项目是 **[FasterEdge](https://github.com/FasterEdge/FasterEdge)** 框架在 **Microchip PIC10F200** 上的极简实现。PIC10F200 为 8 位内核、**仅 256 字（12 位）程序、16B RAM、4MHz、无 UART/ADC/I2C**，是资源最小的 MCU 之一，无法承载完整能力集，因此按「**只实现基础寄存器控制**」裁剪为 GPIO 控制 + 芯片信息。

- ✅ **mplab_x/（MPLAB-X + XC8，C 版）** + **platformio_ide/（MPASM 汇编版）** 双版本
- ✅ 寄存器级 GPIO 控制（TRIS/GPIO 直接操作）
- ✅ 极简命令集，适配 16B RAM / 256 字程序极限

### 二、已实现能力（极简裁剪）

| 名称 | 类型 | 命令/功能 | 说明 |
|------|------|-----------|------|
| `GpioAbility` | Ability | `mode` / `write` / `read` | GP0 输出（LED）、GP1 输入（按键），寄存器级 |
| `ChipData` | Data | `info` | 芯片信息（固定字符串）|

**示例（主循环逻辑）：** GP1 按键按下 → 点亮 GP0，否则熄灭。

### 三、排除项与理由

| 能力 | 排除原因 |
|------|---------|
| Base/Role/Time/OneKey/Serial/Modbus/RegAbility | 无 UART（无串口命令通道）、RAM 仅 16B、程序仅 256 字 |
| ConfigData | 无 EEPROM/Flash 可持久化 |
| 所有网络能力 | PIC10F200 无网络 |

### 四、目录结构

```
MCU-PIC10F200/
├── mplab_x/                    # MPLAB-X + XC8（C 编译器）
│   ├── pic10f200.h             # 寄存器映射 / 引脚常量
│   ├── fe_port.h               # 移植层接口（GPIO / 信息）
│   └── src/main.c              # 寄存器级 GPIO 控制演示
└── platformio_ide/             # PlatformIO + microchippic（MPASM 汇编）
    ├── platformio.ini          # board = pic10f200
    └── src/main.asm            # MPASM 汇编（GP0 输出 / GP1 输入）
```

> PIC10F200 无 UART，两个版本均以 **GPIO 寄存器控制** 演示，不提供串口命令解释器。

### 五、使用说明

1. **mplab_x 版**：MPLAB-X 新建工程 → 器件选 PIC10F200 → 编译器 XC8 → 加入 `src/main.c` → Build + Program（PICkit/Snap）
2. **platformio_ide 版**：`cd platformio_ide && pio run -t upload`（microchippic 平台，MPASM 汇编）
3. 接线：GP0 → LED（串联电阻），GP1 → 按键（下拉或上拉按需）

### 六、平台适配要点

| 差异点 | ESP32/ESP8266 | PIC10F200 |
|--------|--------------|-----------|
| 架构 | Xtensa 32 位 | **8 位（12 位指令）** |
| 程序 / RAM | KB~MB | **256 字 / 16B** |
| 外设 | WiFi/UART/ADC 等 | **仅 GPIO + TMR0** |
| 串口 | 有 | **无（软件模拟也不现实）** |
| 存储 | NVS / Flash | **无（OTP 一次性可编程）** |

### 七、能力裁剪说明

PIC10F200 是全仓库资源最紧张的芯片，只做**寄存器级 GPIO 基础控制**。若需完整能力集，请改用 [MCU-C51](../MCU-C51) / [MCU-CH32V003](../MCU-CH32V003) 等更大资源平台。

### 八、姊妹项目

- **[FasterEdge MCU - C51](https://github.com/FasterEdge/MCU-C51)**：8 位 8051（256B+ RAM，能力全）
- **[FasterEdge MCU - CH32V003](https://github.com/FasterEdge/MCU-CH32V003)**：RISC-V，16KB/2KB
- **[FasterEdge MCU - Arduino Uno R3](https://github.com/FasterEdge/MCU-Arduino-Uno-R3)**：8 位 AVR
- **[FasterEdge](https://github.com/FasterEdge/FasterEdge)**：框架主仓库
