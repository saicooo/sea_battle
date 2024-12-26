int main() {
    seagame::Game game;
    game.startNewGame();

    while (true) {
        game.runRound();

        // Пример сохранения игры
        game.saveGame("save.dat");

        // Пример загрузки игры
        game.loadGame("save.dat");
    }

    return 0;
}