#ifndef GAME
#define GAME

#include "paddle.hpp"
#include "ball.hpp"
#include "block.hpp"
#include <SFML/Graphics.hpp>

struct game_area
{
    float x_start;
    float x_stop;
    float y_start;
    float y_stop;
};
class game
{
public:
    game();
    game(game_area area);
    void init(sf::Font &font);
    void serve_events(const sf::Event event, sf::RenderWindow &window, sf::Clock &clock_obj);
    void update(sf::Clock &clock_obj);
    void draw(sf::RenderWindow &window);

private:
    game_area block_breaker_area;
    sf::RectangleShape game_area_field;
    game_states game_state;
    game_states game_state_request;
    paddle paddle_obj;
    std::vector<ball> balls;
    std::vector<block> blocks;
    sf::Text text_obj;
    sf::Font font_obj;
    sf::Time previus_time;
    sf::Time time_delta;
    int blocks_number;

    void game_state_update();
    void move_paddle();
    void move_ball(ball &ball_obj);
    void ball_meets_edge(ball &ball_obj, sf::Vector2f position_of_ball);
    void ball_meets_block(ball &ball_obj, block &block_obj, sf::Vector2f position_of_ball);
    void ball_meets_paddle(ball &ball_obj, sf::Vector2f position_of_ball);
};

#endif