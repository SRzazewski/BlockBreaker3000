#ifndef MODE
#define MODE

#include <SFML/Window/Event.hpp>
#include <vector>
#include <optional>

class game; //the Mode class needs a declaration of the game class

class Mode
{
public:
    Mode(game *game_inst = nullptr)
    :game_instance(game_inst)
    {}
    virtual ~Mode() = default;
    virtual void serve_events_level(std::optional<sf::Event> event) = 0;
    void set_game_instance(game *game_inst);
protected:
    game *game_instance;
};

class Mode_init : public Mode
{
public:
    Mode_init(game *game_inst);
    void serve_events_level(std::optional<sf::Event> event) override;
};

class Mode_play : public Mode
{
public:
    Mode_play(game *game_inst);
    void serve_events_level(std::optional<sf::Event> event) override;
};

class Mode_won : public Mode
{
public:
    Mode_won(game *game_inst);
    void serve_events_level(std::optional<sf::Event> event) override;
};

class Mode_lost : public Mode
{
public:
    Mode_lost(game *game_inst);
    void serve_events_level(std::optional<sf::Event> event) override;
};

#endif