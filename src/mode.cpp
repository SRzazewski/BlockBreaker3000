#include "game.hpp"
#include "mode.hpp"

void Mode::set_game_instance(game *game_inst)
{
    if (nullptr != game_inst)
    {
        game_instance = game_inst;
    }
}

Mode_init::Mode_init(game *game_inst = nullptr)
    :Mode(game_inst)
    {
        game_instance->enter_init_level_state();
    }

void Mode_init::serve_events_level(std::optional<sf::Event> event)
{
    game_instance->serve_events_level_init(event);
}

Mode_play::Mode_play(game *game_inst = nullptr)
    :Mode(game_inst)
    {
        game_instance->enter_playing_game_state();
    }

void Mode_play::serve_events_level(std::optional<sf::Event> event)
{
    game_instance->serve_events_level(event);
}

Mode_won::Mode_won(game *game_inst = nullptr)
    :Mode(game_inst)
    {
        game_instance->enter_won_game_state();
    }

void Mode_won::serve_events_level(std::optional<sf::Event> event)
{
    game_instance->serve_events_level_won(event);
}

Mode_lost::Mode_lost(game *game_inst = nullptr)
    :Mode(game_inst)
    {
        game_instance->enter_lost_game_state();
    }

void Mode_lost::serve_events_level(std::optional<sf::Event> event)
{
    game_instance->serve_events_level_lost(event);
}