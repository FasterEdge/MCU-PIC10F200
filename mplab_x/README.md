# FasterEdge MCU - PIC10F200（MPLAB-X + XC8 版）

PIC10F200 为 Microchip 极低端 8 位 MCU：**256 字程序 / 16B RAM / 无 UART / 4MHz / 6 引脚**。
资源过小，无法承载完整 FasterEdge 能力集，本平台按「只实现基础寄存器控制」裁剪：
仅 GPIO 寄存器控制（GP0 输出 LED、GP1 按键输入）+ 芯片信息。

## 开发环境

- **MPLAB X IDE**（Microchip 官方，免费）+ **XC8 编译器**（免费 Standard 版即可）
- 芯片型号：**PIC10F200**（或兼容 DIP/SOT23-6）
- 烧录器：PICkit 3/4、MPLAB Snap、或支持 HVPP 的编程器

## 使用方法

1. 打开 MPLAB X，`File → New Project → Microchip Embedded → Standalone Project`
2. 选择器件 **PIC10F200**，工具选择你的烧录器，编译器选 **XC8**
3. 将本目录 `src/main.c` 加入工程（Source Files），`pic10f200.h` 加入头文件路径
4. `Project Properties` 里配置位按需设置（内部 4MHz、关 WDT）
5. 点击 **Build**（F11）→ **Make and Program Device**（F6）烧录

## 能力裁剪说明

| 能力 | 状态 | 说明 |
|------|------|------|
| GpioAbility | ✅ | GP0 输出 / GP1+GP3 输入（TRIS+GPIO 寄存器级） |
| ChipData.info | ✅ | 芯片信息（固定字符串） |
| BaseData / Role / Time / OneKey / Serial / Modbus / Reg | ❌ | 无 UART、RAM 仅 16B、程序仅 256 字，无法承载 |

> PlatformIO 的 `microchippic` 平台对 PIC10F200 仅支持汇编（MPASM），见 `../platformio_ide/`。
