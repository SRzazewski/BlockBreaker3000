#include "paddle.hpp"
#include "ball.hpp"
#include <SFML/Graphics.hpp>

int main()
{
    auto window = sf::RenderWindow{ { 800u, 600u }, "BlockBreaker3000" };
    window.setFramerateLimit(144);

    sf::Text text;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        window.close();
    }

    // select the font
    text.setFont(font); // font is a sf::Font

    // set the string to display
    text.setString("Hello world in BlockBreaker3000");

    // set the character size
    text.setCharacterSize(24); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::Red);

    // set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    paddle paddle_obj = paddle();
    ball ball_obj = ball();

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Left)
                {
                    paddle_obj.move_paddle_left();
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    paddle_obj.move_paddle_right();
                }
                break;
            default:
                break;
            }
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        

        window.clear(sf::Color::Black);
        // inside the main loop, between window.clear() and window.display()
        window.draw(text);
        window.draw(*paddle_obj.get_paddle());
        window.draw(*ball_obj.get_ball());
        window.display();
    }
}