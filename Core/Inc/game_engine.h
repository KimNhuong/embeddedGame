#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <stdint.h>
#include "input.h"

#define MAX_CHICKENS 15
#define MAX_BULLETS  8

// Cấu trúc tọa độ 2D
typedef struct {
    int16_t x;
    int16_t y;
} Position2D;

// Định nghĩa cấu trúc dữ liệu Phi thuyền (Player Ship)
typedef struct {
    Position2D pos;    // Tọa độ hiện tại (trọng tâm hoặc góc trên trái)
    uint8_t lives;     // Số mạng/máu còn lại (ví dụ: 3 mạng)
    uint8_t width;     // Chiều rộng phi thuyền (dùng để tính va chạm)
    uint8_t height;    // Chiều cao phi thuyền (dùng để tính va chạm)
} Player_Ship;

// Định nghĩa cấu trúc dữ liệu Gà (Chicken Enemy)
typedef struct {
    Position2D pos;    // Tọa độ của gà
    uint8_t is_alive;  // Trạng thái sống/chết (1: Sống, 0: Chết)
    uint8_t width;     // Chiều rộng
    uint8_t height;    // Chiều cao
} Chicken_Enemy;

// Định nghĩa cấu trúc dữ liệu Viên đạn (Bullet)
typedef struct {
    Position2D pos;    // Tọa độ của viên đạn
    uint8_t is_active; // Trạng thái đạn (1: Đang bay trên màn hình, 0: Không hoạt động)
} Bullet_Proj;

// Trạng thái màn hình/màn chơi của Game
typedef enum {
    STATE_MENU,
    STATE_PLAYING,
    STATE_GAME_OVER
} Game_Status;

// Định nghĩa cấu trúc chứa toàn bộ Trạng thái Logic của Game
typedef struct {
    Player_Ship player;
    Chicken_Enemy chickens[MAX_CHICKENS];
    Bullet_Proj bullets[MAX_BULLETS];
    uint32_t score;
    Game_Status status;
} Game_State;

// Định nghĩa các sự kiện âm thanh sinh ra trong quá trình cập nhật logic
typedef enum {
    EVENT_NONE = 0,
    EVENT_PLAY_SHOOT,      // Sự kiện bắn đạn
    EVENT_PLAY_CHICKEN_DIE, // Sự kiện gà chết
    EVENT_PLAY_GAME_OVER    // Sự kiện thua cuộc
} Game_Event;

/**
 * @brief Khởi tạo lại toàn bộ trạng thái Logic game (Vị trí thuyền, gà, đạn, điểm số...)
 */
void Game_Init(void);

/**
 * @brief Cập nhật logic game sau mỗi khung hình (frame)
 * @param input Trạng thái đầu vào từ người chơi nhận từ module Input
 * @return Sự kiện âm thanh (nếu có) phát sinh trong frame này để main xử lý
 */
Game_Event Game_Update(Joystick_State input);

/**
 * @brief Lấy con trỏ đến trạng thái hiện tại của Game
 * @return Hằng con trỏ trỏ đến Game_State (Read-only từ bên ngoài)
 */
const Game_State* Game_GetState(void);

#endif // GAME_ENGINE_H
