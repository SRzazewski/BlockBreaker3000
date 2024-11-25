#ifndef GAME
#define GAME

#include "paddle.hpp"
#include "ball.hpp"
#include "block.hpp"
#include "powerup.hpp"
// #include "states.hpp"
#include <SFML/Graphics.hpp>
#include <array>
#include <random>

enum class game_states
{
    game_init = 0,
    game_init_level,
    game_playing,
    game_won,
    game_lost
};

enum class game_levels
{
    level_0 = 0,
    level_1,
    level_2,
    level_3,
    level_4,
    level_5,
};

class game;

struct game_states_st
{
    game_levels state_name;
    int level_number;
    void (game:: *init_function)();
};

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
    game(sf::Font &font, game_area area)
        : block_breaker_area(area)
        , mt(std::random_device()())
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
    }
    void serve_events(const sf::Event event);
    void update(sf::RenderWindow &window, sf::Time delta);
    void draw(sf::RenderWindow &window);
    static sf::Vector2f rotate_vector(sf::Vector2f vector_current, float fi);

private:
    game_area block_breaker_area;
    sf::RectangleShape game_area_field;
    game_states game_state = game_states::game_init;
    game_states game_state_requested = game_states::game_init_level;
    int game_level = 1;
    paddle paddle_obj;
    std::vector<ball> balls;
    std::vector<block> blocks;
    std::vector<powerup> powerups;
    sf::Text text_obj;
    sf::Text text_score;
    std::vector<int> powerup_from_blocks;
    std::mt19937 mt;
    int score = 0;
    int score_level = 0;
    const float position_paddle_x_min = block_breaker_area.x_start + paddle_size.x/2.0f;
    const float position_paddle_x_max = block_breaker_area.x_stop - paddle_size.x/2.0f;

    std::array<game_states_st, 6> game_levels_var
    {{
        {game_levels::level_0, 0, nullptr},
        {game_levels::level_1, 1, &game::game_state_level_1_prepare},
        {game_levels::level_2, 2, &game::game_state_level_2_prepare},
        {game_levels::level_3, 3, &game::game_state_level_3_prepare},
        {game_levels::level_4, 4, &game::game_state_level_4_prepare},
        {game_levels::level_5, 5, &game::game_state_level_5_prepare}
    }};

    void serve_events_level_init(const sf::Event event);
    void serve_events_level(const sf::Event event);
    void serve_events_level_won(const sf::Event event);
    void serve_events_level_lost(const sf::Event event);

    void game_state_update(sf::RenderWindow &window);
    void obj_reset();
    std::vector<int> rand_powerups(int powerup_number);
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
    void calculate_angle_of_incidence(float &fi);
};
#endif