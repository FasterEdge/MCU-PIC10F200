// ─────────────────────────────────────────────────────────────
// FasterEdge 开源项目
// Github: https://github.com/FasterEdge
// Gitee:  https://gitee.com/FasterEdge
// ─────────────────────────────────────────────────────────────
// pic10f200.h — PIC10F200 最小编译目标定义（供 XC8 或 gcc 语法检查）
// PIC10F200: 12-bit 指令、256 字程序、16B RAM、4MHz、6 引脚（GP0-GP3 可用）
// 无 UART/ADC/I2C —— 本平台只做寄存器/GPIO 级基础控制。
#ifndef PIC10F200_H
#define PIC10F200_H

#include <stdint.h>
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
#define TRUE 1
#define FALSE 0

// PIC10F200 寄存器映射（文件寄存器地址）
// 注：PIC10F200 无 UART；TRIS/GPIO 等文件寄存器地址与数据手册一致。
#define SFR(addr) (*(volatile u8 *)(addr))
#define INDF   SFR(0x00)
#define TMR0   SFR(0x01)
#define PCL    SFR(0x02)
#define STATUS SFR(0x03)
#define FSR    SFR(0x04)
#define OSCCAL SFR(0x05)
#define GPIO   SFR(0x06)
#define PCON   SFR(0x07)
// PIC10F200 的 TRIS/OPTION 不是文件寄存器(0x08/0x09 实为通用 RAM), 方向寄存器
// 必须用 TRIS/OPTION 指令写入。XC8 提供内建 TRIS/OPTION 关键字, 故不在此定义
// SFR 别名(否则 TRIS=x 会被误展开为写通用 RAM, GPIO 方向从未生效)。

// OPTION 寄存器经 OPTION 指令访问(见 main.c); 保留此注释供参考。
// #define OPTION SFR(0x08)   // 错误: 0x08 是通用 RAM, 非 OPTION
// #define TRIS   SFR(0x09)   // 错误: 0x09 是通用 RAM, 非 TRIS

// STATUS 位
#define _C 0x00
#define _DC 0x01
#define _Z 0x02
#define _PD 0x03
#define _TO 0x04
#define _PA0 0x05
#define _PA1 0x06
#define _RB 0x06

// 配置位（PIC10F200: 8-bit 配置字）
#define _CP     0x80
#define _WDTE   0x40
#define _MCLRE  0x20
#define _INTRC  0x00

// 引脚常量（SOT23-6: VDD/VSS/GP0/GP1/GP2/GP3）
#define PIN_GP0 0
#define PIN_GP1 1
#define PIN_GP2 2
#define PIN_GP3 3
#define PICO_PIN_MAX 4

#endif // PIC10F200_H
