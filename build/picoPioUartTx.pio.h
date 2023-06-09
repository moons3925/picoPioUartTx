// -------------------------------------------------- //
// This file is autogenerated by pioasm; do not edit! //
// -------------------------------------------------- //

#pragma once

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// ------------- //
// picoPioUartTx //
// ------------- //

#define picoPioUartTx_wrap_target 0
#define picoPioUartTx_wrap 3

static const uint16_t picoPioUartTx_program_instructions[] = {
            //     .wrap_target
    0x9fa0, //  0: pull   block           side 1 [7] 
    0xf728, //  1: set    x, 8            side 0 [7] 
    0x6001, //  2: out    pins, 1                    
    0x0642, //  3: jmp    x--, 2                 [6] 
            //     .wrap
};

#if !PICO_NO_HARDWARE
static const struct pio_program picoPioUartTx_program = {
    .instructions = picoPioUartTx_program_instructions,
    .length = 4,
    .origin = -1,
};

static inline pio_sm_config picoPioUartTx_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + picoPioUartTx_wrap_target, offset + picoPioUartTx_wrap);
    sm_config_set_sideset(&c, 2, true, false);
    return c;
}

#include "hardware/clocks.h"
static inline void picoPioUartTx_program_init(PIO pio, uint sm, uint offset, uint pin_tx, uint baud) {
    // マスクしてピンを設定します
    pio_sm_set_pins_with_mask(pio, sm, 1u << pin_tx, 1u << pin_tx);
    // マスクしてピン方向を設定します
    pio_sm_set_pindirs_with_mask(pio, sm, 1u << pin_tx, 1u << pin_tx);
    // GPIO初期化します
    pio_gpio_init(pio, pin_tx);
    // デフォルト設定を得ます
    pio_sm_config c = picoPioUartTx_program_get_default_config(offset);
    // 右シフト、自動pullしない、スレッショルドを9に設定します
    // LSBファーストなので右シフトする
    // アセンブラで pull命令を書いているので自動pullは不要
    // データ8ビット+パリティ付きなのでスレッショルドは9
    sm_config_set_out_shift(&c, true, false, 9);
    // 出力に設定します(pin_tx = GPIO0)
    sm_config_set_out_pins(&c, pin_tx, 1);
    // サイドセットピンを設定します(pin_tx = GPIO0)
    // （出力ピンとサイドセットピンに同じものを指定することも可能）
    sm_config_set_sideset_pins(&c, pin_tx);
    // FIFOを送信専用にします
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);
    // 1クロックを通信速度の8倍に設定します
    // （クロック8個で1ビット分の幅になる仕様）
    float div = (float)clock_get_hz(clk_sys) / (8 * baud);
    sm_config_set_clkdiv(&c, div);
    // SMを初期化します
    pio_sm_init(pio, sm, offset, &c);
    // SMを有効にします
    pio_sm_set_enabled(pio, sm, true);
}

#endif

