#include "game.hpp"
#include <SFML/Graphics.hpp>

int main()
{
    const game_area block_breaker_area = {0.0f, 800.0f, 60.0f, 600.0f};
    auto window = sf::RenderWindow{ { static_cast<unsigned int>(block_breaker_area.x_stop), static_cast<unsigned int>(block_breaker_area.y_stop) }, "BlockBreaker3000" };
    window.setFramerateLimit(144);

    sf::Font font;
    if (!font.loadFromFile("font/arial.ttf"))
    {
        window.close();
    }

    game game_obj = game(font, block_breaker_area);

    sf::Clock clock_obj = sf::Clock();

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            game_obj.serve_events(event, window);
        }

        window.clear(sf::Color(166u, 166u, 166u));
        game_obj.update(window, clock_obj.restart());
        game_obj.draw(window);
        window.display();
    }
}