#ifndef GAME
#define GAME

#include "paddle.hpp"
#include "ball.hpp"
#include "block.hpp"
#include "physic_of_object.hpp"
#include <SFML/Graphics.hpp>

class game
{
public:
    game();
    void init(sf::Font &font);
    void serve_events(const sf::Event event, sf::RenderWindow &window, sf::Clock &clock_obj);
    void update(sf::Clock &clock_obj);
    void draw(sf::RenderWindow &window);

private:
    game_area block_breaker_area;
    game_states game_state;
    paddle paddle_obj;
    std::vector<ball> balls;
    std::vector<block> blocks;
    sf::Text text_obj;
    sf::Font font_obj;
};

#endif