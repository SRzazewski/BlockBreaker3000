#include "paddle.hpp"
#include "ball.hpp"
#include "physic_of_object.hpp"
#include "block.hpp"
#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <iostream>

int block::number_of_blocks = 0;

int main()
{
    const game_area block_breaker_area = {0.0f, 800.0f, 30.0f, 600.0f};
    auto window = sf::RenderWindow{ { static_cast<unsigned int>(block_breaker_area.x_stop), static_cast<unsigned int>(block_breaker_area.y_stop) }, "BlockBreaker3000" };
    window.setFramerateLimit(144);

    game game_obj = game();

    // sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        window.close();
    }
    // text.setFont(font);
    // text.setString("BlockBreaker3000");
    // text.setCharacterSize(24);
    // text.setFillColor(sf::Color::Red);
    // text.setStyle(sf::Text::Bold);

    sf::Clock clock_obj = sf::Clock();
    sf::Time time_obj = sf::Time();

    sf::RectangleShape game_area_shape = sf::RectangleShape();
    game_area_shape.setSize(sf::Vector2f(block_breaker_area.x_stop - block_breaker_area.x_start, block_breaker_area.y_stop - block_breaker_area.y_start));
    game_area_shape.setFillColor(sf::Color::Black);
    game_area_shape.setPosition(sf::Vector2f(block_breaker_area.x_start, block_breaker_area.y_start));

    game_states game_state = game_states::during_game;

    game_obj.init(font);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            game_obj.serve_events(event, window, clock_obj);
        }

        window.clear(sf::Color(166u, 166u, 166u));
        window.draw(game_area_shape);
        game_obj.update(clock_obj);
        game_obj.draw(window);

        // std::cout << "Number of blocks:" << block::get_number_of_blocks() << "\n";
        window.display();
    }
}