#include "game.h"
#include <functional>
#include <unordered_map>
#include <iostream>

namespace seagame {

template <typename InputHandler>
class GameController {
public:
    GameController(Game& game) : game(game) {
        // Инициализация команд
        commands['s'] = std::bind(&Game::saveGame, &game, "save.dat");
        commands['l'] = std::bind(&Game::loadGame, &game, "save.dat");
        commands['n'] = std::bind(&Game::startNewGame, &game);
        commands['r'] = std::bind(&Game::runRound, &game);
    }

    void run() {
        InputHandler inputHandler;
        while (true) {
            char key = inputHandler.getKey();
            if (commands.find(key) != commands.end()) {
                commands[key]();
            } else {
                std::cout << "Unknown command: " << key << std::endl;
            }
        }
    }

private:
    Game& game;
    std::unordered_map<char, std::function<void()>> commands;
};

} // namespace seagame