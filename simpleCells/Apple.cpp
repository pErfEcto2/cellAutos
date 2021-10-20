#include "Apple.h"

Apple::Apple() {
    pos = Vector2f(rand() % VideoMode::getDesktopMode().width, rand() % VideoMode::getDesktopMode().height);
    apple.setPosition(pos);
    apple.setSize(size);
    apple.setFillColor(color);
};

void Apple::draw(RenderTarget &window) {
    window.draw(apple);
};