#include "PCH.h"
#include "Game.h"


#ifdef OOD
int main()
{
    srand(static_cast<uint>(time(nullptr)));

    Game game;
    game.Init();

    sf::Clock start;

    while (SFMLTon::GetWindow().isOpen())
    {
        float dt = start.getElapsedTime().asSeconds();
        std::cout << "FPS: " << 1.0f / dt << std::endl;
        start.restart();

        sf::Event event;
        while (SFMLTon::GetWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                SFMLTon::GetWindow().close();
        }

        game.Update(dt);

        SFMLTon::GetWindow().clear();
        //game.Draw();
        SFMLTon::GetWindow().display();
    }

    SFMLTon::GetWindow().close();

    return 0;
}
#elif defined DOD
int main()
{
    srand(static_cast<uint>(time(nullptr)));

    Game game;
    game.Init();

    sf::Clock start;
    
    while (SFMLTon::GetWindow().isOpen())
    {
        float dt = start.getElapsedTime().asSeconds();
        //std::cout << "FPS: " << 1.0f / dt << std::endl;
        start.restart();

        sf::Event event;
        while (SFMLTon::GetWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                SFMLTon::GetWindow().close();
        }

        game.Update(dt);

        game.Draw();
    }

    SFMLTon::GetWindow().close();

    return 0;
}
#endif