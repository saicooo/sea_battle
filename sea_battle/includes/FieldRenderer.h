#include "game.h"
#include <iostream>

namespace seagame {

class FieldRenderer {
public:
    FieldRenderer(Game& game) : game(game) {}

    void render() {
        const Field& field = game.getField();
        const ShipManager& userShips = game.getUserShips();
        const ShipManager& enemyShips = game.getEnemyShips();

        // Пример отрисовки поля
        for (std::uint64_t y = 1; y <= field.size().n(); ++y) {
            for (std::uint64_t x = 1; x <= field.size().m(); ++x) {
                Unit unit(x, y);
                if (userShips.container().find(unit) != userShips.container().end()) {
                    std::cout << 'U'; // User ship
                } else if (enemyShips.container().find(unit) != enemyShips.container().end()) {
                    std::cout << 'E'; // Enemy ship
                } else {
                    std::cout << '.'; // Empty cell
                }
            }
            std::cout << std::endl;
        }
    }

private:
    Game& game;
};

} // namespace seagame