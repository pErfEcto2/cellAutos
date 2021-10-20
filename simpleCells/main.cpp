#include "Cell.h"
#include "Apple.h"
using namespace sf;
using namespace std;
// this fun returns "true" if r2 crosses r1
bool intersects(FloatRect r1, FloatRect r2) {
    return r1.intersects(r2);
}

CircleShape circleInit(Color color, Vector2f pos) {
    CircleShape circle(1);
    circle.setFillColor(color);
    circle.setPosition(pos);
    return circle;
}

int main() {
    Text time;
    Font font;
    Clock clock;

    float t = 0;

    if (!font.loadFromFile("font.ttf")) {
        cout << "Failed while loading font" << endl;
    }

    time.setFont(font);
    time.setCharacterSize(30);
    time.setFillColor(Color::Cyan);
    time.setPosition(Vector2f(1300, 30));

    int monitorWidth = VideoMode::getDesktopMode().width;
    int monitorHeight = VideoMode::getDesktopMode().height;
    int c = 0;
    int whiteCells = 0;
    int yellowCells = 0;
    int redCells = 0;

    RenderWindow window(VideoMode(monitorWidth, monitorHeight), "Screen Saver", Style::Fullscreen);
    //window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);
    Event event;
    
    vector<Cell> cells;
    vector<Apple> apples;
    vector<CircleShape> graph;

    Vector2f size = {15, 15};

    int startNum = 100 + rand() % 31;

    for (int i = 0; i < startNum; i++) {
        Cell cell(size);
        cells.push_back(cell);
        Apple apple;
        apples.push_back(apple);
    }

    RectangleShape Y(Vector2f(5, 150));
    Y.setPosition(Vector2f(30, 600));
    Y.setFillColor(Color::Cyan);
    
    RectangleShape X(Vector2f(1300, 5));
    X.setPosition(Vector2f(30, 750));
    X.setFillColor(Color::Cyan);

    while (window.isOpen()) {
        while (window.pollEvent(event)){
            if (event.type == sf::Event::EventType::Closed) {
                window.close();
                return EXIT_SUCCESS;
            }
        }
        clock.restart();

        Apple apple;
        apples.push_back(apple);

        for (int i = 0; i < cells.size(); i++) {
            cells[i].update();
            
            for (int j = 0; j < apples.size(); j++) {
                if (intersects(cells[i].cell.getGlobalBounds(), apples[j].apple.getGlobalBounds())) {
                    cells[i].addLife(50.f);
                    apples.erase(apples.begin() + j);
                }
            }

            for (int j = 0; j < cells.size(); j++) {
                if (intersects(cells[i].cell.getGlobalBounds(), cells[j].cell.getGlobalBounds())) {
                    if (i != j && rand() % 10 == 0) {
                        cells[i].setLife(30);
                        cells.erase(cells.begin() + j);
                    }
                    else {
                        cells[i].invertLinSpeed();
                        cells[j].invertLinSpeed();
                    }
                }
            }

            if (cells[i].getLife() <= 0.f) {
                cells.erase(cells.begin() + i);
            }

            if (rand() % 100 == 0) {
                Cell cell1(size);
                cell1.setPos(Vector2f(cells[i].getPos().x - 20, cells[i].getPos().y));
                cell1.setSpeed(cells[i].getSpeed());
                cell1.setLife(cells[i].getLife());

                Cell cell2(size);
                cell2.setPos(Vector2f(cells[i].getPos().x + 20, cells[i].getPos().y));
                cell2.setSpeed(cells[i].getSpeed());
                cell2.setLife(cells[i].getLife());

                cells.erase(cells.begin() + i);
                cells.push_back(cell1);
                cells.push_back(cell2);
            }

            if (cells[i].getColor() == Color::White) whiteCells++;
            if (cells[i].getColor() == Color::Yellow) yellowCells++;
            if (cells[i].getColor() == Color::Red) redCells++;
        }

        if (cells.size() != 0) {
            t += clock.getElapsedTime().asSeconds();
            time.setString(to_string(static_cast<int>(t / 60.0)));
        }

        if (c % 5 == 0 && 38 + c / 20 < monitorWidth) {
            CircleShape circle1 = circleInit(Color::White, Vector2f(35 + t * 2.5, 750 - whiteCells));
            CircleShape circle2 = circleInit(Color::Yellow, Vector2f(35 + t * 2.5, 750 - yellowCells));
            CircleShape circle3 = circleInit(Color::Red, Vector2f(35 + t * 2.5, 750 - redCells));
            graph.push_back(circle1);
            graph.push_back(circle2);
            graph.push_back(circle3);
            c = 0;
        }

        window.clear();

        for (int i = 0; i < apples.size(); i++) {
            apples[i].draw(window);
        }

        for (int i = 0; i < cells.size(); i++) {
            cells[i].draw(window);
        }

        for (int i = 0; i < graph.size(); i++) {
            window.draw(graph[i]);
        }

        window.draw(time);
        window.draw(Y);
        window.draw(X);

        window.display();

        c++;
        whiteCells = 0;
        yellowCells = 0;
        redCells = 0;
    }
}