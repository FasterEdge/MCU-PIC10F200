/* FasterEdge 开源项目
 * GitHub: https://github.com/FasterEdge
 * Gitee:  https://gitee.com/FasterEdge
 */
// main.c — FasterEdge MCU PIC10F200 极简版（MPLAB-X + XC8）
// PIC10F200 资源极小（256 字程序 / 16B RAM / 无 UART / 4 引脚 GPIO），
// 本平台只实现「寄存器/GPIO 基础控制」：
//   - GP0 输出（驱动 LED），GP1 输入（按键），GP3 输入
//   - 通过 TRIS / GPIO 寄存器直接控制（寄存器级，无库）
// 对应能力子集：GpioAbility（mode/write/read）+ ChipData（info）
#include "pic10f200.h"

// ---- 寄存器级驱动（直接读写 SFR）----
static void gpio_set_output(u8 pin) { TRIS &= (u8)~(1u << pin); }
static void gpio_set_input(u8 pin)  { TRIS |= (u8)(1u << pin); }
static void gpio_write(u8 pin, u8 v){ if (v) GPIO |= (u8)(1u << pin); else GPIO &= (u8)~(1u << pin); }
static u8   gpio_read(u8 pin)       { return (GPIO >> pin) & 1u; }

static void delay(void) { volatile u16 i; for (i = 0; i < 60000u; i++) ; }

int main(void) {
    // 配置位：内部 4MHz、关 WDT、关 MCLR（由编译器 pragma 处理）
    gpio_set_output(PIN_GP0);   // LED
    gpio_set_input(PIN_GP1);    // 按键
    gpio_set_input(PIN_GP3);
    for (;;) {
        if (gpio_read(PIN_GP1)) {
            gpio_write(PIN_GP0, 1);
        } else {
            gpio_write(PIN_GP0, 0);
        }
        delay();
    }
}
