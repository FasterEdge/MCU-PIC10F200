// ─────────────────────────────────────────────────────────────
// FasterEdge 开源项目
// Github: https://github.com/FasterEdge
// Gitee:  https://gitee.com/FasterEdge
// ─────────────────────────────────────────────────────────────
// fe_port.h — FasterEdge MCU 平台移植层（PIC10F200 极简版）
// PIC10F200 资源极小（256 字程序 / 16B RAM / 无 UART），
// 本平台只实现「寄存器/GPIO 基础控制」能力子集：
//   RegAbility（SFR 读写） / GpioAbility（GPIO 控制） / BaseData / ChipData
#ifndef FE_PORT_H
#define FE_PORT_H

#include "pic10f200.h"

// ---- 寄存器读写（RegAbility）----
u8  fe_port_sfr_read(u8 addr);
void fe_port_sfr_write(u8 addr, u8 val);

// ---- GPIO（GpioAbility）----
int  fe_port_gpio_set_mode(u8 pin, const char *mode); // input / output
int  fe_port_gpio_write(u8 pin, u8 level);
int  fe_port_gpio_read(u8 pin);

// ---- 信息（BaseData / ChipData）----
void fe_port_chip_info(char *out, u16 outlen);
void fe_port_delay_ms(u32 ms);

#endif // FE_PORT_H
