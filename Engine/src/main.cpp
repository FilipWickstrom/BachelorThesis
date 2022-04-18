#include "PCH.h"
#if BENCH_DT
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

    //Benchmarking
#if BENCH_DT
    Benchmark benchmark;
#endif // BENCH_DT


    while (WINDOW.isOpen())
    {
        float dt = clock.getElapsedTime().asSeconds();
        clock.restart();

#if BENCH_DT
        benchmark.AddDT(dt);
#endif

        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
        }

        game.Update(dt);
        game.Render();
    }

#if BENCH_DT
    float averageDT = benchmark.GetAverageDT();
    std::cout << "Average DT: " << averageDT << std::endl;
    std::cout << "Average FPS: " << 1.f / averageDT << std::endl;
#endif

    WINDOW.close();
    return 0;
}