#include "PCH.h"
#ifdef BENCH_DT
#include "Benchmark.h"
#endif 

#ifdef OOD
#include "GameOOD.h"
#elif defined DOD
#include "GameDOD.h"
#endif

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    sf::Clock clock;

#ifdef OOD
    GameOOD game;
#elif defined DOD
    GameDOD game;
#endif

#ifdef BENCH_DT
    Benchmark benchmark;
#endif


    while (WINDOW.isOpen())
    {
        float dt = clock.getElapsedTime().asSeconds();
        clock.restart();

#ifdef BENCH_DT
        benchmark.AddDT(dt);
#endif

        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
        }

        game.Update(dt);
#if DRAW_GAME
        game.Render();
#endif
    }

    WINDOW.close();
    return 0;
}