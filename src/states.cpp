#include "game.hpp"
#include "states.hpp"

void states::set_game_instance(game *game_inst)
{
    if (nullptr != game_inst)
    {
        game_instance = game_inst;
    }
}

state_game_init::state_game_init(game *game_inst = nullptr)
    :states(game_inst)
    {
        game_instance->enter_init_level_state();
    }

void state_game_init::serve_events_level(std::optional<sf::Event> event)
{
    game_instance->serve_events_level_init(event);
}

state_game_playing::state_game_playing(game *game_inst = nullptr)
    :states(game_inst)
    {
        game_instance->enter_playing_game_state();
    }

void state_game_playing::serve_events_level(std::optional<sf::Event> event)
{
    game_instance->serve_events_level(event);
}

state_game_won::state_game_won(game *game_inst = nullptr)
    :states(game_inst)
    {
        game_instance->enter_won_game_state();
    }

void state_game_won::serve_events_level(std::optional<sf::Event> event)
{
    game_instance->serve_events_level_won(event);
}

state_game_lost::state_game_lost(game *game_inst = nullptr)
    :states(game_inst)
    {
        game_instance->enter_lost_game_state();
    }

void state_game_lost::serve_events_level(std::optional<sf::Event> event)
{
    game_instance->serve_events_level_lost(event);
}