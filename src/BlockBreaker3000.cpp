#include "paddle.hpp"
#include "ball.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

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
    sf::Clock clock_obj = sf::Clock();
    sf::Time time_obj = sf::Time();
    sf::Vector2f position_of_ball;
    sf::Vector2f velocity_of_ball;

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

        time_obj = clock_obj.getElapsedTime();
        position_of_ball = ball_obj.get_position();
        velocity_of_ball = ball_obj.get_velocity_vector();
        position_of_ball.x = position_of_ball.x + (velocity_of_ball.x * time_obj.asSeconds());
        position_of_ball.y = position_of_ball.y + (velocity_of_ball.y * time_obj.asSeconds());
        
        if (position_of_ball.x < 0)
        {
            position_of_ball.x *= -1.0;
            velocity_of_ball.x *= -1.0;
        }
        else if(position_of_ball.x > (800.0f - 30.0f))
        {
            position_of_ball.x = 2 * (800.0f - 30.0f) - position_of_ball.x;
            velocity_of_ball.x *= -1.0;
        }

        if (position_of_ball.y < 0)
        {
            position_of_ball.y *= -1.0;
            velocity_of_ball.y *= -1.0;
        }
        else if(position_of_ball.y > (600.0f - 30.0f))
        {
            position_of_ball.y = 2 * (600.0f - 30.0f) - position_of_ball.y;
            velocity_of_ball.y *= -1.0;
        }

        // std::cout << "Ball position x , y:" << position_of_ball.x << " ," << position_of_ball.y << "\n";
        // std::cout << "Ball velocity x , y:" << velocity_of_ball.x << " ," << velocity_of_ball.y << "\n";

        ball_obj.set_velocity_vector(velocity_of_ball);
        ball_obj.set_position(position_of_ball);

        clock_obj.restart();

        window.clear(sf::Color::Black);
        // inside the main loop, between window.clear() and window.display()
        // window.draw(text);
        window.draw(*paddle_obj.get_paddle());
        window.draw(*ball_obj.get_ball());
        window.display();
    }
}