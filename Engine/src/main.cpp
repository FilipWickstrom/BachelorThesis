#include "PCH.h"
#include "Game.h"

//#define OOD
#define DOD


#ifdef OOD
int main()
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (SFMLTon::GetWindow().isOpen())
    {
        sf::Event event;
        while (SFMLTon::GetWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                SFMLTon::GetWindow().close();
        }

        SFMLTon::GetWindow().clear();
        SFMLTon::GetWindow().draw(shape);
        SFMLTon::GetWindow().display();
    }

    SFMLTon::GetWindow().close();

    return 0;
}
#elif defined DOD
int main()
{
    srand(time(nullptr));

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
        
        //game.Draw();
    }

    SFMLTon::GetWindow().close();

    return 0;
}
#endif