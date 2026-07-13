#include "audio.h"

void Audio_Init(void) {
    // TODO: Cấu hình Timer PWM hoặc DAC cho Loa/Buzzer
}

void Audio_Play(Sound_Effect effect) {
    // TODO: Phát tần số âm thanh tương ứng với từng effect
    switch (effect) {
        case SOUND_SHOOT:
            break;
        case SOUND_CHICKEN_DIE:
            break;
        case SOUND_GAME_OVER:
            break;
        default:
            break;
    }
}
