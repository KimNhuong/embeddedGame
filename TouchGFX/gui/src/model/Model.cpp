#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

// --- WORKAROUND FOR STM32CubeIDE LINKER BUG ---
// STM32CubeIDE đôi khi bị lỗi không chịu compile các file ảnh mới sinh ra (dù đã Refresh).
// Include trực tiếp ở đây để ép compiler nhúng data của ảnh vào Model.o.
// Nếu sau này bạn thấy lỗi "multiple definition of image_bg_menu", hãy xoá 2 dòng include này đi.
#include "../../../generated/images/src/image_bg_menu.cpp"
#include "../../../generated/images/src/image_bg_round1.cpp"
// ----------------------------------------------
#include <gui/model/ModelListener.hpp>

Model::Model() : modelListener(0)
{

}

void Model::tick()
{

}
