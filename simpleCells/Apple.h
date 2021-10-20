#pragma once
#include "Cell.h"

class Apple {
    public:
        RectangleShape apple;
        Apple();
        FloatRect getBounds();
        void draw(RenderTarget &window);
    private:
        Vector2f pos;
        Vector2f size = {1, 1};
        Color color = Color::Red;
};