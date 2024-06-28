#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <SFML/Graphics.hpp>
#include <array>

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

class game_object
{
public:
    game_object(sf::RenderWindow *const app_window = nullptr):
        window(app_window){}
    virtual void set_position(sf::Vector2f position) = 0;
    virtual sf::Vector2f get_position() const = 0;
    virtual void draw(sf::RenderWindow &window) = 0;

protected:
    sf::RenderWindow *const window;
};

class moving_object : public game_object
{
public:
    moving_object(sf::RenderWindow *const app_window = nullptr, sf::Clock *const app_clock = nullptr):
        window(app_window),
        clock(app_clock) {}
    virtual void set_velocity_vector(sf::Vector2f vector) = 0;
    virtual sf::Vector2f get_velocity_vector() const = 0;
    
protected:
    sf::RenderWindow *const window;
    sf::Clock *const clock;
    sf::Vector2f velocity_vector;
};

#endif