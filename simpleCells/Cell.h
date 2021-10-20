#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "iostream"
#include "random"
#include "vector"

using namespace sf;
using namespace std;

class Cell {
private:
    Vector2f pos;
    float life = 100;
    Color color = Color(rand() % 256, rand() % 256, rand() % 256);
public:
    RectangleShape cell;
    Cell(Vector2f s = {0, 0});
    void update();
    float getLife();
    void addLife(float l);
    Vector2f getPos();
    void draw(RenderTarget &window);
    void setPos(Vector2f p);
};