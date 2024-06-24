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

    game game_obj = game(block_breaker_area);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        window.close();
    }

    sf::Clock clock_obj = sf::Clock();
    sf::Time time_obj = sf::Time();

    game_obj.init(font);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            game_obj.serve_events(event, window, clock_obj);
        }

        window.clear(sf::Color(166u, 166u, 166u));
        game_obj.update(clock_obj);
        game_obj.draw(window);

        // std::cout << "Number of blocks:" << block::get_number_of_blocks() << "\n";
        window.display();
    }
}