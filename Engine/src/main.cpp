#include "PCH.h"
#include "Game.h"

#if BENCH_DT
#include "Benchmark.h"
#endif 

int main()
{
    srand(static_cast<uint>(time(nullptr)));

    Game game;
    game.Init();

#if BENCH_DT
    Benchmark benchmark;
#endif

    sf::Clock start;

    while (SFMLTon::GetWindow().isOpen())
    {
        float dt = start.getElapsedTime().asSeconds();
        start.restart();

#if BENCH_DT
        benchmark.AddDT(dt);
#endif

        sf::Event event;
        while (SFMLTon::GetWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                SFMLTon::GetWindow().close();
        }

        game.Update(dt);

        //game.Draw();
    }

    SFMLTon::GetWindow().close();

    return 0;
}
