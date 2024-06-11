#ifndef GAME
#define GAME

#include "paddle.hpp"
#include "ball.hpp"
#include "block.hpp"
#include <SFML/Graphics.hpp>

class game
{
public:
    game();
    ~game();
    void init();
    void serve_events(const sf::Event event);
    void serve_time();
    void draw();

private:
    paddle paddle_obj;
    std::vector<ball> balls;
    std::vector<block> blocks
};

#endif