#include "display.h"

void Display_Init(void) {
    // TODO: Khởi tạo LCD điều khiển phần cứng BSP, cấu hình DMA2D
}

void Display_Clear(void) {
    // TODO: Xóa màn hình hoặc hoán đổi buffer (Double Buffering)
}

void Display_DrawMenu(void) {
    // TODO: Vẽ chữ "CHICKEN INVADERS", "Press SHOOT to Start"
}

void Display_DrawGameplay(const Game_State* state) {
    if (state == 0) return;

    // TODO: Vẽ phi thuyền tại state->player.pos.x, state->player.pos.y
    // TODO: Quét mảng vẽ các con gà còn sống (is_alive == 1)
    // TODO: Quét mảng vẽ các viên đạn đang bay (is_active == 1)
    // TODO: Hiển thị điểm số state->score và số mạng state->player.lives
}

void Display_DrawGameOver(uint32_t final_score) {
    // TODO: Vẽ màn hình Game Over và số điểm final_score
}
