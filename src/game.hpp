#ifndef GAME
#define GAME

#include "paddle.hpp"
#include "ball.hpp"
#include "block.hpp"
#include "powerup.hpp"
#include <SFML/Graphics.hpp>
#include <array>
#include <random>

enum class game_states
{
    game_init = 0,
    level_1_init,
    level_1,
    level_2_init,
    level_2,
    level_3_init,
    level_3,
    level_4_init,
    level_4,
    level_5_init,
    level_5,
    level_won,
    level_lost
};

constexpr std::array<game_states, 5> states_init
{{game_states::level_1_init, 
game_states::level_2_init, 
game_states::level_3_init, 
game_states::level_4_init, 
game_states::level_5_init}};

constexpr std::array<game_states, 5> states_playing
{{game_states::level_1, 
game_states::level_2, 
game_states::level_3, 
game_states::level_4, 
game_states::level_5}};

struct game_area
{
    float x_start;
    float x_stop;
    float y_start;
    float y_stop;
};

const sf::Vector2f ball_start_position_shift = sf::Vector2f(-10.0f, -40.f);
constexpr int points_for_ball = 200;
constexpr float paddle_velocity = 400.0f;
constexpr int powerup_banned_blocks = 6;
constexpr int blocks_in_row = 8;

class game
{
public:
    game(sf::Font &font, game_area area):
        block_breaker_area(area)
    {
        game_area_field.setSize(sf::Vector2f(block_breaker_area.x_stop - block_breaker_area.x_start, 
                                            block_breaker_area.y_stop - block_breaker_area.y_start));
        game_area_field.setFillColor(sf::Color::Black);
        game_area_field.setPosition(sf::Vector2f(block_breaker_area.x_start, block_breaker_area.y_start));
        text_obj.setFont(font);
        text_obj.setString("BlockBreaker3000");
        text_obj.setCharacterSize(24);
        text_obj.setFillColor(sf::Color::Red);
        text_obj.setStyle(sf::Text::Bold);
        text_score.setFont(font);
        text_score.setString("Score: " + std::to_string(score + score_level));
        text_score.setCharacterSize(24);
        text_score.setFillColor(sf::Color::Red);
        text_score.setStyle(sf::Text::Bold);
        text_score.setPosition(0.0f, 30.0f);
        mt = std::mt19937(rd());
    }
    void serve_events(const sf::Event event);
    void update(sf::RenderWindow &window, sf::Time delta);
    void draw(sf::RenderWindow &window);

private:
    game_area block_breaker_area;
    sf::RectangleShape game_area_field;
    game_states game_state_previus;
    game_states game_state = game_states::game_init;
    game_states game_state_requested = game_states::level_1_init;
    paddle paddle_obj;
    std::vector<ball> balls;
    std::vector<block> blocks;
    std::vector<powerup> powerups;
    sf::Text text_obj;
    sf::Text text_score;
    std::vector<int> powerup_from_blocks;
    std::random_device rd;
    std::mt19937 mt;
    int score = 0;
    int score_level = 0;
    const float position_paddle_x_min = block_breaker_area.x_start + paddle_size.x/2.0f;
    const float position_paddle_x_max = block_breaker_area.x_stop - paddle_size.x/2.0f;

    void serve_events_level_init(const sf::Event event);
    void serve_events_level(const sf::Event event);
    void serve_events_level_won(const sf::Event event);
    void serve_events_level_lost(const sf::Event event);

    void game_state_update(sf::RenderWindow &window);
    void obj_reset();
    void rand_powerups(int powerup_number);
    void put_blocks(int block_type, int rows_number);
    void game_state_level_1_prepare();
    void game_state_level_2_prepare();
    void game_state_level_3_prepare();
    void game_state_level_4_prepare();
    void game_state_level_5_prepare();
    
    void move_paddle(sf::Time time_delta);
    bool move_ball(ball &ball_obj, sf::Time time_delta);
    bool move_powerup(powerup &powerup_obj, sf::Time time_delta);
    bool ball_meets_edge(ball &ball_obj, sf::Vector2f ball_position);
    bool powerup_meets_paddle(powerup &powerup_obj);
    bool powerup_meets_edge(powerup &powerup_obj);
    bool block_broke(block &block_obj);
    bool ball_meets_block(ball &ball_obj, block &block_obj, sf::Vector2f ball_position);
    void ball_meets_paddle(ball &ball_obj, sf::Vector2f ball_position);
    sf::Vector2f calculate_new_vector(sf::Vector2f vector_current, float fi);
};

#endif