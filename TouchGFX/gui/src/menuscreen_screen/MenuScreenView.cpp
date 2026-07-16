#include <gui/menuscreen_screen/MenuScreenView.hpp>

MenuScreenView::MenuScreenView()
{

}

void MenuScreenView::setupScreen()
{
    MenuScreenViewBase::setupScreen();
    
    // Setup the second background image for continuous scrolling
    movingBg2.setBitmap(movingBg.getBitmap());
    movingBg2.setXY(movingBg.getX(), movingBg.getY() - movingBg.getHeight());
    
    // Insert movingBg2 right after movingBg in the Z-order so they are drawn behind UI elements
    insert(&movingBg, movingBg2);
}

void MenuScreenView::tearDownScreen()
{
    MenuScreenViewBase::tearDownScreen();
}

void MenuScreenView::handleTickEvent()
{
    // Xóa vùng vẽ cũ
    movingBg.invalidate();
    movingBg2.invalidate();
    
    // Di chuyển background xuống (tốc độ có thể tùy chỉnh)
    int speed = 2;
    movingBg.setY(movingBg.getY() + speed);
    movingBg2.setY(movingBg2.getY() + speed);
    
    // Nếu movingBg trôi quá màn hình thì nối nó vào sau movingBg2
    if (movingBg.getY() >= 320)
    {
        movingBg.setY(movingBg2.getY() - movingBg.getHeight());
    }
    
    // Nếu movingBg2 trôi quá màn hình thì nối nó vào sau movingBg
    if (movingBg2.getY() >= 320)
    {
        movingBg2.setY(movingBg.getY() - movingBg.getHeight());
    }
    
    // Cập nhật vùng vẽ mới
    movingBg.invalidate();
    movingBg2.invalidate();
}
