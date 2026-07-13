# Tài liệu Hướng dẫn Phân chia Công việc và Định nghĩa API Game bắn gà (Chicken Invaders)

Tài liệu này đóng vai trò là **"Hợp đồng Giao diện" (Interface Contract)** giữa 3 thành viên trong nhóm phát triển game nhúng trên KIT STM32F429 Discovery. Bằng cách thống nhất sớm cấu trúc của 4 file `.h`, mỗi người có thể lập trình độc lập phần việc của mình mà không cần đợi người khác code xong.

---

## 📂 Danh sách 4 File Header Quy định Giao diện

### 1. `input.h`
Quy định cách lấy dữ liệu từ Joystick (Trái, Phải, Lên, Xuống) và Nút bấm (Bắn).

```c
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
```

---

### 2. `audio.h`
Quy định các hàm khởi tạo và phát các hiệu ứng âm thanh trong game.

```c
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
```

---

### 3. `game_engine.h`
Định nghĩa cấu trúc dữ liệu cốt lõi của game (Thuyền, Gà, Đạn) và các hàm xử lý logic game.

```c
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
```

---

### 4. `display.h`
Quy định các hàm vẽ các thực thể game lên màn hình LCD.

```c
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
```

---

## 👥 Phân chia chi tiết đầu việc cho 3 người

### 🧑‍💻 Người 1: Hardware Driver & Sound (Chuyên gia Phần cứng)
Chịu trách nhiệm cấu hình các ngoại vi của chip STM32F429 và hiện thực các file: `input.h` và `audio.h`.
- **Đầu việc cụ thể**:
  1. Cấu hình **ADC** (Sử dụng DMA hoặc Polling) để đọc giá trị analog từ 2 trục X, Y của Joystick để phân tích ra các hướng `UP, DOWN, LEFT, RIGHT`.
  2. Cấu hình **GPIO EXTI (Interrupt)** hoặc **Polling** cho nút nhấn để nhận biết sự kiện bắn đạn.
  3. Cấu hình **Timer PWM** hoặc **DAC** để tạo tín hiệu hình sin/vuông tần số khác nhau điều khiển Buzzer/Loa nhằm phát các tiếng động tương ứng với `Sound_Effect`.
- **Sản phẩm bàn giao**: File `input.c` và `audio.c` triển khai đầy đủ các hàm đã định nghĩa trong `input.h` và `audio.h`.

---

### 🧑‍💻 Người 2: Game Logic & Core Engine (Bộ não của Game)
Chịu trách nhiệm thiết kế logic trò chơi, tính toán chuyển động và va chạm. Người này làm việc độc lập trên file `game_engine.h` và `game_engine.c`.
- **Đầu việc cụ thể**:
  1. Xử lý di chuyển của phi thuyền dựa trên `input` của Người 1 gửi tới.
  2. Xử lý đường bay của các viên đạn (đi thẳng lên) và cập nhật tọa độ tự động di chuyển của đàn gà (đi ngang qua lại hoặc lao xuống).
  3. **Tính toán va chạm (Collision Detection)**:
     - Nếu Đạn va chạm với Gà: Đặt Gà `is_alive = 0`, tăng `score`, tắt Đạn và kích hoạt sự kiện `EVENT_PLAY_CHICKEN_DIE`.
     - Nếu Gà hoặc Trứng va chạm với Thuyền: Trừ `lives` của Thuyền. Nếu `lives == 0`, đổi trạng thái game sang `STATE_GAME_OVER` và kích hoạt sự kiện `EVENT_PLAY_GAME_OVER`.
  4. Quản lý trạng thái chuyển đổi giữa `STATE_MENU` -> `STATE_PLAYING` -> `STATE_GAME_OVER`.
- **Sản phẩm bàn giao**: File `game_engine.c` triển khai các hàm logic độc lập với phần cứng hiển thị/âm thanh.

---

### 🧑‍💻 Người 3: Graphics & UI (Giao diện & Đồ họa)
Chịu trách nhiệm thiết kế hình ảnh và tối ưu hóa hiển thị đồ họa trên màn hình LCD sử dụng thư viện BSP và bộ tăng tốc đồ họa **DMA2D** (Chrom-ART).
- **Đầu việc cụ thể**:
  1. Thiết kế hoặc chuyển đổi ảnh Sprite (Thuyền, Gà, Đạn, Vụ nổ) thành các mảng hằng số Hex trong bộ nhớ (C Array / `.h` resource).
  2. Triển khai cấu hình **Double Buffering** (Bộ đệm kép) để tránh hiện tượng giật lag, xé hình khi vẽ.
  3. Thực hiện các hàm vẽ đối tượng tại tọa độ tương ứng được truyền vào từ `Game_State` của Người 2.
- **Sản phẩm bàn giao**: File `display.c` triển khai đầy đủ các hàm vẽ định nghĩa trong `display.h`.

---

## 🔗 Cách kết nối kết quả lại với nhau (Integration)

Khi 3 thành viên đã hoàn thành công việc của mình theo đúng hợp đồng giao diện, lập trình viên trưởng chỉ cần kết nối tất cả tại file `main.c` như sau:

```c
#include "main.h"
#include "input.h"
#include "audio.h"
#include "game_engine.h"
#include "display.h"

// Biến lưu trữ sự kiện âm thanh sinh ra từ Engine
Game_Event current_event = EVENT_NONE;

int main(void) {
    // 1. Khởi tạo cấu hình phần cứng cơ bản của STM32
    HAL_Init();
    SystemClock_Config();
    
    // 2. Khởi tạo các module của nhóm
    Input_Init();     // Code của Người 1
    Audio_Init();     // Code của Người 1
    Display_Init();   // Code của Người 3
    Game_Init();      // Code của Người 2

    // Vòng lặp chính của Game
    while (1) {
        // --- BƯỚC 1: LẤY ĐẦU VÀO (Người 1) ---
        Joystick_State input = Input_GetState();
        
        // --- BƯỚC 2: CẬP NHẬT LOGIC (Người 2) ---
        current_event = Game_Update(input);
        
        // Lấy trạng thái game hiện tại sau khi đã cập nhật logic
        const Game_State* game = Game_GetState();

        // --- BƯỚC 3: XỬ LÝ ÂM THANH (Người 1 kết nối Người 2) ---
        if (current_event == EVENT_PLAY_SHOOT) {
            Audio_Play(SOUND_SHOOT);
        } else if (current_event == EVENT_PLAY_CHICKEN_DIE) {
            Audio_Play(SOUND_CHICKEN_DIE);
        } else if (current_event == EVENT_PLAY_GAME_OVER) {
            Audio_Play(SOUND_GAME_OVER);
        }

        // --- BƯỚC 4: VẼ ĐỒ HỌA LÊN MÀN HÌNH (Người 3 kết nối Người 2) ---
        Display_Clear();
        
        if (game->status == STATE_MENU) {
            Display_DrawMenu();
        } else if (game->status == STATE_PLAYING) {
            Display_DrawGameplay(game);
        } else if (game->status == STATE_GAME_OVER) {
            Display_DrawGameOver(game->score);
        }
        
        // Khống chế thời gian khung hình (FPS ~ 50Hz)
        HAL_Delay(20);
    }
}
```