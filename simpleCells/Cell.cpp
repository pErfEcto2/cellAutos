#include "Cell.h"

Cell::Cell(Vector2f s) {
    cell.setSize(s);
    cell.setFillColor(color);
    cell.setOrigin(cell.getSize().x / 2.0, cell.getSize().y / 2.0);
    pos = Vector2f(rand() % VideoMode::getDesktopMode().width, rand() % VideoMode::getDesktopMode().height);
    cell.setPosition(pos);
};

void Cell::update() {
    life -= 1;
};

float Cell::getLife() {
    return life;
};

Vector2f Cell::getPos() {
    return pos;
};

void Cell::draw(RenderTarget &window) {
    window.draw(cell);
};

void Cell::setPos(Vector2f p) {
    cell.setPosition(p);
};

void Cell::addLife(float l) {
    life += l;
};