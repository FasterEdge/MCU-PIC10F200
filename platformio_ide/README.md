# FasterEdge MCU - PIC10F200（PlatformIO + MPASM 汇编版）

PlatformIO 的 **microchippic** 平台对 PIC10F200 仅支持 **MPASM 汇编**（PIC10 无 C 运行时 / 16B RAM）。

## 使用方法

```bash
cd platformio_ide
pio run            # 编译（MPASM → HEX）
pio run -t upload  # 烧录（PICkit/Snap/MPLAB Snap 等）
```

## 能力裁剪说明

PIC10F200 无 UART、RAM 仅 16B、程序仅 256 字，只实现：
- **GpioAbility**：GP0 输出（LED）/ GP1 输入（按键），寄存器级 TRIS/GPIO 操作
- **ChipData.info**：芯片信息

完整能力集（Base/Role/Time/OneKey/Serial/Modbus/Reg）在 PIC10F200 上无法承载，
详见仓库顶层 README「能力裁剪」。
