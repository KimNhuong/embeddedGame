#ifndef DISPLAY_H
#define DISPLAY_H

#include "game_engine.h"

/**
 * @brief Khởi tạo màn hình LCD (SPI/FMC, DMA2D, cấu hình lớp đồ họa Double Buffering)
 */
void Display_Init(void);

/**
 * @brief Xóa màn hình hoặc chuyển đổi giữa các Buffer (Tránh hiện tượng xé hình)
 */
void Display_Clear(void);

/**
 * @brief Vẽ màn hình Menu chính của game
 */
void Display_DrawMenu(void);

/**
 * @brief Vẽ toàn bộ trạng thái Gameplay hiện tại lên màn hình
 * @param state Con trỏ hằng trỏ đến trạng thái Game_State cần vẽ
 */
void Display_DrawGameplay(const Game_State* state);

/**
 * @brief Vẽ màn hình thông báo kết thúc game kèm theo điểm số đạt được
 * @param final_score Điểm số cuối cùng của người chơi
 */
void Display_DrawGameOver(uint32_t final_score);

#endif // DISPLAY_H
