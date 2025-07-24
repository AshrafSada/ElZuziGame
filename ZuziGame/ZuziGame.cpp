#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
int main(int argc, char* argv[]) {
    // create game window
    const int winWidth = 1400u;
    const int winHeight = 1050u;
    sf::RenderWindow window(sf::VideoMode({ winWidth,winHeight }), "Zuzi Game");
    // set window frame limit: recommended(60 - 144)
    window.setFramerateLimit(60);

    // draw shape circle with default color white
    const float circleRadius = 50.f;
    sf::CircleShape circle(circleRadius);

    // set position top, left (x,y)
    sf::Vector2f circlePos;
    circlePos.x = (float)winWidth / 2;
    circlePos.y = (float)winHeight / 2;
    circle.setPosition(circlePos);
    float circleMoveSpeed = 1.0f;

    // draw rectangular shape
    sf::Vector2f rectPos;
    rectPos.x = 33.f;
    rectPos.y = 33.f;
    sf::Vector2f rectSize;
    rectSize.x = 100.f;
    rectSize.y = 100.f;

    sf::RectangleShape rect;
    rect.setSize(rectSize);
    rect.setPosition(rectPos);

    // fill with custom rgb color
    int r, g, b, a;
    r = 197u;
    g = 18u;
    b = 33u;
    a = 255u;
    rect.setFillColor(sf::Color(r, g, b, a));

    // load custom font from file
    sf::Font techFont;
    if (!techFont.openFromFile("..\\Fonts\\tech.ttf")) {
        // error message
        std::cout << "Font not found" << std::endl;
        exit(-1);
    }

    // use text to test custom font
    sf::Text text(techFont, "sample text", 24u);

    // position the text
    sf::Vector2f txtPos;
    txtPos.x = 33.f;
    txtPos.y = winHeight - (float)text.getCharacterSize() - 33.f;
    text.setPosition(txtPos);

    // handling window loop
    while (window.isOpen())
    {
        // handling window events
        while (const std::optional event = window.pollEvent())
        {
            // handling closed event
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                // handling escape key press event
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window.close();
                }
            }
            else if (const auto* resized = event->getIf<sf::Event::Resized>()) {
                std::cout << "new width: " << resized->size.x << std::endl;
                std::cout << "new height: " << resized->size.y << std::endl;
            }
        }

        // move the circle
        sf::Vector2f cmPos;
        cmPos.x -= circleMoveSpeed;
        cmPos.y -= circleMoveSpeed;
        circle.move(cmPos);

        window.clear();
        window.draw(circle);
        window.draw(text);
        window.draw(rect);
        window.display();
    }
}
