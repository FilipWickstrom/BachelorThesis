#include "PCH.h"
#include "Game.h"

#define OOD
//#define DOD

#ifdef OOD
int main()
{
    srand(static_cast<unsigned int>(time(0)));
    sf::Clock clock;

    //Init all gameobjects
    Game game;

    while (WINDOW.isOpen())
    {
        float dt = clock.getElapsedTime().asSeconds();
        std::cout << "FPS: " << 1.f / dt << std::endl;
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
#elif defined DOD

#endif