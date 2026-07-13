#include "input.h"

void Input_Init(void) {
    // TODO: Cấu hình ADC cho Joystick và GPIO Interrupt cho nút bấm
}

Joystick_State Input_GetState(void) {
    Joystick_State state = { JOYSTICK_NONE, 0 };
    // TODO: Đọc giá trị ADC/GPIO và gán vào state
    return state;
}
