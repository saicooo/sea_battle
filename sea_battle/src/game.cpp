#include "game.h"
#include "field.h"
#include "skill_manager.h"
#include "ship_manager.h"
#include "unit.h"
#include "skill_factory.h"
#include "skill.h"
#include <fstream>
#include <iostream>

namespace seagame {

class Game {
public:
    Game() : field(5, 5), userShipManager(), enemyShipManager(), skillManager(), isUserTurn(true) {}

    void startNewGame() {
        // Инициализация поля, кораблей и способностей
        field = Field(5, 5);
        userShipManager = ShipManager({Ship::Len::TWO, Ship::Len::THREE});
        enemyShipManager = ShipManager({Ship::Len::TWO, Ship::Len::THREE});
        skillManager = SkillManager();
        isUserTurn = true;

        // Размещение кораблей пользователя
        field.add_ship(userShipManager[0], Unit(1, 1));
        field.add_ship(userShipManager[1], Unit(3, 3));

        // Размещение кораблей врага
        field.add_ship(enemyShipManager[0], Unit(2, 2));
        field.add_ship(enemyShipManager[1], Unit(4, 4));
    }

    void runRound() {
        while (!isRoundOver()) {
            if (isUserTurn) {
                userTurn();
            } else {
                enemyTurn();
            }
            isUserTurn = !isUserTurn;
        }
        if (isGameOver()) {
            std::cout << "Game Over! You lost." << std::endl;
            startNewGame();
        } else {
            std::cout << "Round Over! Starting new round." << std::endl;
        }
    }

    void userTurn() {
        std::cout << "Your turn. Choose a skill to use:" << std::endl;
        // Показываем доступные способности
        auto availableSkills = skillManager.__get_random_skills();
        for (size_t i = 0; i < availableSkills.size(); ++i) {
            std::cout << i << ": " << availableSkills[i] << std::endl;
        }

        int choice;
        std::cin >> choice;

        if (choice >= 0 && choice < availableSkills.size()) {
            auto skillFactory = skillManager.pop_skill();
            auto skill = skillFactory->create(Unit(2, 3)); // Пример выбора юнита
            skill->use(field);
            std::cout << "Skill result: " << skill->result()->get() << std::endl;
        } else {
            std::cout << "Invalid choice. Skipping turn." << std::endl;
        }
    }

    void enemyTurn() {
        std::cout << "Enemy's turn." << std::endl;
        // Простой пример атаки врага
        field.shot(Unit(1, 1)); // Пример атаки врага
    }

    void saveGame(const std::string& filename) {
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Failed to open file for saving.");
        }
        // Сохранение состояния игры
        // (например, сохранение поля, кораблей, способностей и т.д.)
        // Пример:
        // file << field;
        // file << userShipManager;
        // file << enemyShipManager;
        // file << skillManager;
        file.close();
    }

    void loadGame(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Failed to open file for loading.");
        }
        // Загрузка состояния игры
        // (например, загрузка поля, кораблей, способностей и т.д.)
        // Пример:
        // file >> field;
        // file >> userShipManager;
        // file >> enemyShipManager;
        // file >> skillManager;
        file.close();
    }

    bool isGameOver() const {
        // Проверка, остались ли у пользователя корабли
        return userShipManager.container().empty();
    }

    bool isRoundOver() const {
        // Проверка, закончен ли раунд (например, если у врага не осталось кораблей)
        return enemyShipManager.container().empty();
    }

private:
    Field field;
    ShipManager userShipManager;
    ShipManager enemyShipManager;
    SkillManager skillManager;
    bool isUserTurn;
};

} // namespace seagame