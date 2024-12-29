#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>

int main()
{
    const game_area block_breaker_area = {0.0f, 800.0f, 60.0f, 600.0f};
    auto window = sf::RenderWindow{ { static_cast<unsigned int>(block_breaker_area.x_stop), static_cast<unsigned int>(block_breaker_area.y_stop) }, "BlockBreaker3000" };
    window.setFramerateLimit(144);

    std::string path = std::filesystem::canonical("/proc/self/exe");
    while (path.length() > 1)
    {
        char last_character = path.back();
        if ('/' == last_character)
        {
            break;
        }
        path.erase(path.end() - 1);
    }

    sf::Font font;
    if (!font.loadFromFile(path + "font/arial.ttf"))
    {
        window.close();
    }

    game game_obj = game(font, block_breaker_area);

    sf::Clock clock_obj = sf::Clock();

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            else
            {
                game_obj.serve_events(event);
            }
        }

        window.clear(sf::Color(166u, 166u, 166u));
        game_obj.update(window, clock_obj.restart());
        game_obj.draw(window);
        window.display();
    }
}