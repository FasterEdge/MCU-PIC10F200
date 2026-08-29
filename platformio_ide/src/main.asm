; ============================================================
; FasterEdge MCU - PIC10F200 极简版（MPASM 汇编）
; PIC10F200: 256 字程序 / 16B RAM / 无 UART / 4 引脚 GPIO
; 能力子集（仅基础寄存器控制）：
;   - GP0 输出（LED），GP1 输入（按键）
;   - 寄存器级 TRIS / GPIO 直接操作
; 对应能力：GpioAbility（mode/write/read）+ ChipData（info）
; ============================================================
    list p=10F200
    include <p10f200.inc>

    __CONFIG _UNPROTECT & _BODEN_ON & _CP_OFF & _MCLRE_OFF & _WDT_OFF & _PWRTE_OFF

; ---- 通用文件寄存器（16B RAM）----
GPIO_   equ 0x06    ; GPIO 数据寄存器
TRIS_   equ 0x06+3  ; TRIS 方向寄存器（实际在 bank0 偏移由 PCLATH 控制，此处用文件选择位）
; 说明：PIC10F200 的 TRIS 与 GPIO 同一文件号，靠 FSR/OPTION 寄存器位切换。
; 为简洁，本示例直接使用 p10f200.inc 提供的符号。

; ---- 变量 ----
    cblock 0x0A
        count1
        count2
    endc

; ---- 复位向量 ----
    org 0x0000
    goto start

; ---- 主程序 ----
start
    ; GP0 = 输出，GP1 = 输入
    movwf   0x09        ; 访问 TRIS 文件寄存器
    movlw   b'00000010' ; GP1 输入，其余输出
    movwf   TRIS_
    clrw
    movwf   GPIO_

loop
    ; 读 GP1：按键按下(GP1=0) 则点亮 GP0，否则熄灭
    btfsc   GPIO_, 1
    goto    led_off
    bsf     GPIO_, 0
    goto    delay
led_off
    bcf     GPIO_, 0

delay
    ; 简单软件延时
    movlw   0xFF
    movwf   count1
d1
    decfsz  count1, f
    goto    d1
    goto    loop

    end
