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
    Vector2f linSpeed;
    Vector2f pos;
    float life = 100;
    Color color = Color::White;
    Vector2i monitorSize = {VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height};
public:
    RectangleShape cell;
    Cell(Vector2f s);
    void update();
    float getLife();
    void addLife(float l);
    Vector2f getPos();
    Vector2f getSpeed();
    void setSpeed(Vector2f sp);
    void draw(RenderTarget &window);
    void setPos(Vector2f p);
    void invertLinSpeed();
    void setLife(float l);
    Color getColor();
};