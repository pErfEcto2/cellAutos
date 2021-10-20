#include "Cell.h"

Cell::Cell(Vector2f s) {
    linSpeed = {10 + rand() % 21, 10 + rand() % 21};
    cell.setSize(s);
    cell.setFillColor(color);
    cell.setOrigin(cell.getSize().x / 2.0, cell.getSize().y / 2.0);
    pos = Vector2f(rand() % monitorSize.x, rand() % monitorSize.y);
    cell.setPosition(pos);
};

void Cell::update() {
    cell.move(linSpeed);
    if (rand() % 50 == 0) {
        linSpeed = {0 - rand() % 16, 0 - rand() % 16};
    }
    if (pos.x + linSpeed.x >= monitorSize.x || pos.x + linSpeed.x <= 0) linSpeed.x *= -1;
    if (pos.y + linSpeed.y >= monitorSize.y || pos.y + linSpeed.y <= 0) linSpeed.y *= -1;
    life -= 1;
    if (life > 25 && life <= 60) cell.setFillColor(Color::Yellow);
    if (life <= 25) cell.setFillColor(Color::Red);
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

void Cell::invertLinSpeed() {
    linSpeed = {linSpeed.x * -1, linSpeed.y * -1};
};

Vector2f Cell::getSpeed() {
    return linSpeed;
};

void Cell::setSpeed(Vector2f sp) {
    linSpeed = sp;
};

void Cell::setLife(float l) {
    life = l;
};

Color Cell::getColor() {
    return cell.getFillColor();
}