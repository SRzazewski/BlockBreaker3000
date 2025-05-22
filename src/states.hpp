#ifndef STATES
#define STATES

#include <SFML/Window/Event.hpp>
#include <vector>
#include <optional>

class game; //the states class needs a declaration of the game class

class states
{
public:
    states(game *game_inst = nullptr)
    :game_instance(game_inst)
    {}
    virtual ~states() = default;
    virtual void serve_events_level(std::optional<sf::Event> event) = 0;
    void set_game_instance(game *game_inst);
protected:
    game *game_instance;
};

class state_game_init : public states
{
public:
    state_game_init(game *game_inst);
    void serve_events_level(std::optional<sf::Event> event) override;
};

class state_game_playing : public states
{
public:
    state_game_playing(game *game_inst);
    void serve_events_level(std::optional<sf::Event> event) override;
};

class state_game_won : public states
{
public:
    state_game_won(game *game_inst);
    void serve_events_level(std::optional<sf::Event> event) override;
};

class state_game_lost : public states
{
public:
    state_game_lost(game *game_inst);
    void serve_events_level(std::optional<sf::Event> event) override;
};

#endif