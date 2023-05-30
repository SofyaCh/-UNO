
#include "my_player.h"
#include "logger.h"
#include "stats.h"

void statisticTest();


int main()
{
    // Ваш main должен выглядеть примерно так

    UnoGame game;
    Logger logger;
    SimplePlayer player2("Vasya");
    Player player1("Kolya");
     game.addPlayer(&player1);
     game.addPlayer(&player2);
    game.addObserver(&logger);
    //game.runGame();
    statisticTest();
}

void statisticTest()
{
    UnoGame game;
     SimplePlayer player2("Vasya");
     Player player1("Kolya");
     game.addPlayer(&player1);
     game.addPlayer(&player2);
    StatsObserver result = runGames(game, 1000);
    StatsObserver::MV winMV = result.getWinsMV();
    std::cout << "Vasya won in " << winMV.mean[0] * 100 << "% of games" << std::endl;
}
