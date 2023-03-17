#include "hardware/pio.h"
#include "pico/stdlib.h"
#include "picoPioUartTx.pio.h"

// パリティ付きで送信します
void picoPioUartTx_program_putc(PIO pio, uint sm, char c, bool even_parity) {
    uint32_t byte = (uint32_t)c;
    uint8_t parity = 0;
    for (int i = 0; i < 8; i++) {
        parity ^= byte & 0x1;
        byte >>= 1;
    }
    byte = (uint32_t)c;
    if (parity) {
        if (even_parity) {
            byte |= 0x100;  // 偶数になるようにパリティを付加します
        }
    } else {
        if (!even_parity) {
            byte |= 0x100;  // 奇数になるようにパリティを付加します
        }
    }
    pio_sm_put_blocking(pio, sm, (uint32_t)byte);  // TX FIFOへputします
}

void picoPioUartTx_program_puts(PIO pio, uint sm, const char *s) {
    while (*s) {
        picoPioUartTx_program_putc(pio, sm, *s++, true);  // trueで偶数パリティ
    }
}

int main() {
    const uint PIN_TX = 0;  // GPIO0
    const uint SERIAL_BAUD = 115200;

    // 使うPIOを指定します
    PIO pio = pio0;

    // 使うSMを指定します
    uint sm = 0;

    // 命令用のメモリーにアセンブラのプログラムを登録します
    // 第2引数には picoPioUartTx.pioファイルで書いたアセンブラコードの ".program
    // の後の名前 + _program に & をつけます"
    uint offset = pio_add_program(pio, &picoPioUartTx_program);

    // 初期化関数を呼びます。picoPioUartTx.pio に記述している関数です
    picoPioUartTx_program_init(pio, sm, offset, PIN_TX, SERIAL_BAUD);

    while (true) {
        // 文字列をUARTで送信します
        picoPioUartTx_program_puts(pio, sm, "pico\r\n");
        // 1秒待ちます
        sleep_ms(1000);
    }
}
