#include "game_state.h"
#include "field.h"
#include "ship_manager.h"
#include "skill_manager.h"
#include <iostream>
#include <fstream>

namespace seagame {

class GameState {
public:
    GameState(const Field& field, const ShipManager& userShips, const ShipManager& enemyShips, const SkillManager& skills)
        : field(field), userShips(userShips), enemyShips(enemyShips), skills(skills) {}

    friend std::ostream& operator<<(std::ostream& os, const GameState& state) {
        // Сохранение состояния игры в поток
        os << state.field << state.userShips << state.enemyShips << state.skills;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, GameState& state) {
        // Загрузка состояния игры из потока
        is >> state.field >> state.userShips >> state.enemyShips >> state.skills;
        return is;
    }

    // Геттеры для доступа к состоянию игры
    const Field& getField() const { return field; }
    const ShipManager& getUserShips() const { return userShips; }
    const ShipManager& getEnemyShips() const { return enemyShips; }
    const SkillManager& getSkills() const { return skills; }

private:
    Field field;
    ShipManager userShips;
    ShipManager enemyShips;
    SkillManager skills;
};

} // namespace seagame