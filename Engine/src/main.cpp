#include "PCH.h"
#include "Game.h"

#ifdef BENCH_DT
#include "Benchmark.h"
#endif 

int main()
{
    srand(static_cast<uint>(time(nullptr)));

#ifdef NR_OF_THREADS
    omp_set_num_threads(NR_OF_THREADS);
#endif

    Game game;
    game.Init();

#ifdef BENCH_DT
    Benchmark benchmark;
#endif

    sf::Clock start;

    while (SFMLTon::GetWindow().isOpen())
    {
        float dt = start.getElapsedTime().asSeconds();
        start.restart();

#ifdef BENCH_DT
        benchmark.AddDT(dt);
#endif

        sf::Event event;
        while (SFMLTon::GetWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                SFMLTon::GetWindow().close();
        }

        game.Update(dt);

#if DRAW_GAME
        game.Draw();
#endif
    }

    SFMLTon::GetWindow().close();

    return 0;
}
