#include "Cell.h"
#include "Apple.h"
using namespace sf;
using namespace std;
// this fun returns "true" if r2 crosses r1
bool intersects(FloatRect r1, FloatRect r2) {
    return r1.intersects(r2);
}

int main() {
    int monitorWidth = VideoMode::getDesktopMode().width;
    int monitorHeight = VideoMode::getDesktopMode().height;

    RenderWindow window(VideoMode(monitorWidth, monitorHeight), "Screen Saver", Style::Fullscreen);
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);
    Event event;
    
    vector<Cell> cells;
    vector<Apple> apples;

    Vector2f size = {10, 10};

    int startNum = 100 + rand() % 31;

    for (int i = 0; i < startNum; i++) {
        Cell cell(size);
        cells.push_back(cell);
        Apple apple;
        apples.push_back(apple);
    }

    while (window.isOpen()) {
        while (window.pollEvent(event)){
            if (event.type == sf::Event::EventType::Closed) {
                window.close();
                return EXIT_SUCCESS;
            }
        }

        if (rand() % 8 == 0) {
            Apple apple;
            apples.push_back(apple);
        }

        for (int i = 0; i < cells.size(); i++) {
            cells[i].update();
            
            for (int j = 0; j < apples.size(); j++) {
                if (intersects(cells[i].cell.getGlobalBounds(), apples[j].apple.getGlobalBounds())) {
                    cells[i].addLife(50.f);
                    apples.erase(apples.begin() + j);
                }
            }

            if (cells[i].getLife() <= 0.f) {
                cells.erase(cells.begin() + i);
            }

            if (rand() % 200 == 0) {
                cells.erase(cells.begin() + i);
                Cell cell1(size);
                cell1.setPos(Vector2f(cells[i].getPos().x - 20, cells[i].getPos().y));
                Cell cell2(size);
                cell1.setPos(Vector2f(cells[i].getPos().x + 20, cells[i].getPos().y));
                cells.push_back(cell1);
                cells.push_back(cell2);
            }
        }
        
        window.clear();

        for (int i = 0; i < apples.size(); i++) {
            apples[i].draw(window);
        }

        for (int i = 0; i < cells.size(); i++) {
            cells[i].draw(window);
        }

        window.display();
    }
}