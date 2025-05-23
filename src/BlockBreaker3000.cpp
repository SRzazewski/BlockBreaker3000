#include "mode.hpp"
#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>

int main()
{
    const game_area block_breaker_area = {0, 800, 60, 600};
    auto window = sf::RenderWindow(
            sf::VideoMode(
                {
                    block_breaker_area.x_stop, 
                    block_breaker_area.y_stop
                }), 
            "BlockBreaker3000");
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
    if (!font.openFromFile(path + "font/arial.ttf"))
    {
        window.close();
    }

    game game_obj = game(window, font, block_breaker_area);
    game_obj.transition_to_state(new Mode_init(&game_obj));

    sf::Clock clock_obj = sf::Clock();

    while (window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else
            {
                game_obj.serve_events(event);
            }
        }

        window.clear(sf::Color(166u, 166u, 166u));
        game_obj.update(clock_obj.restart());
        game_obj.draw();
        window.display();
    }
}