#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>

// Định nghĩa các hướng di chuyển của Joystick
typedef enum {
    JOYSTICK_NONE = 0,
    JOYSTICK_UP,
    JOYSTICK_DOWN,
    JOYSTICK_LEFT,
    JOYSTICK_RIGHT
} Joystick_Dir;

// Cấu trúc lưu trữ trạng thái đầu vào từ Joystick và nút bấm
typedef struct {
    Joystick_Dir direction; // Hướng Joystick hiện tại
    uint8_t shoot_pressed;  // Trạng thái nút bắn (1: Nhấn, 0: Thả)
} Joystick_State;

/**
 * @brief Khởi tạo phần cứng cho bộ điều khiển (ADC cho Joystick, GPIO Interrupt cho nút bấm)
 */
void Input_Init(void);

/**
 * @brief Đọc giá trị hiện tại của Joystick và nút bấm
 * @return Trạng thái Joystick và nút bấm được chuẩn hóa
 */
Joystick_State Input_GetState(void);

#endif // INPUT_H
