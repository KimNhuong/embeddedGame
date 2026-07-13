#ifndef AUDIO_H
#define AUDIO_H

#include <stdint.h>

// Định nghĩa các hiệu ứng âm thanh trong game
typedef enum {
    SOUND_SHOOT,       // Bắn đạn
    SOUND_CHICKEN_DIE, // Gà chết/nổ
    SOUND_GAME_OVER    // Game Over / Thua cuộc
} Sound_Effect;

/**
 * @brief Khởi tạo phần cứng phát âm thanh (Timer PWM hoặc DAC điều khiển loa)
 */
void Audio_Init(void);

/**
 * @brief Phát một hiệu ứng âm thanh tương ứng
 * @param effect Hiệu ứng âm thanh cần phát
 */
void Audio_Play(Sound_Effect effect);

#endif // AUDIO_H
