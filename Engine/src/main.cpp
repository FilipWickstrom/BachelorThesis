#include "PCH.h"
#define OOD     //OOD or DOD

#ifdef OOD
#include "GameOOD.h"
#elif defined DOD
#include "GameDOD.h"
#endif

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    sf::Clock clock;

    //Init all gameobjects
#ifdef OOD
    GameOOD game;
#elif defined DOD
    GameDOD game;
#endif

    while (WINDOW.isOpen())
    {
        float dt = clock.getElapsedTime().asSeconds();
        //std::cout << "FPS: " << 1.f / dt << std::endl;
        clock.restart();

        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
        }

        //Benchmark start
        game.Update(dt);
        //Benchmark end
        game.Render();
    }

    WINDOW.close();
    return 0;
}