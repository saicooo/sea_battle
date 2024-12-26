#include "game.h"

namespace seagame {

template <typename Renderer>
class GameRenderer {
public:
    GameRenderer(Game& game) : game(game), renderer(game) {}

    void render() {
        renderer.render();
    }

private:
    Game& game;
    Renderer renderer;
};

} // namespace seagame