#include "game_engine.h"

// Biến lưu trữ trạng thái cục bộ của Game Engine
static Game_State current_game_state;

void Game_Init(void) {
    // TODO: Khởi tạo giá trị ban đầu cho phi thuyền, đàn gà, đạn, điểm số
    current_game_state.status = STATE_MENU;
    current_game_state.score = 0;
    current_game_state.player.lives = 3;
    current_game_state.player.pos.x = 120; // Giả sử chiều rộng LCD là 240
    current_game_state.player.pos.y = 280; // Giả sử chiều cao LCD là 320
    current_game_state.player.width = 16;
    current_game_state.player.height = 16;

    // Reset gà và đạn
    for (int i = 0; i < MAX_CHICKENS; i++) {
        current_game_state.chickens[i].is_alive = 0;
    }
    for (int i = 0; i < MAX_BULLETS; i++) {
        current_game_state.bullets[i].is_active = 0;
    }
}

Game_Event Game_Update(Joystick_State input) {
    Game_Event event = EVENT_NONE;

    if (current_game_state.status == STATE_PLAYING) {
        // TODO: Xử lý di chuyển phi thuyền theo input.direction
        // TODO: Xử lý bắn đạn khi input.shoot_pressed == 1
        // TODO: Cập nhật tọa độ đạn bay lên, gà bay qua lại
        // TODO: Tính toán va chạm giữa đạn-gà, gà-phi thuyền
    } else if (current_game_state.status == STATE_MENU) {
        // TODO: Nhấn nút bắn để vào game chơi
        if (input.shoot_pressed) {
            Game_Init();
            current_game_state.status = STATE_PLAYING;
        }
    } else if (current_game_state.status == STATE_GAME_OVER) {
        // TODO: Nhấn nút bắn để quay lại menu chính
        if (input.shoot_pressed) {
            current_game_state.status = STATE_MENU;
        }
    }

    return event;
}

const Game_State* Game_GetState(void) {
    return &current_game_state;
}
