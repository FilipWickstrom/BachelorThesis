#include "PCH.h"

#define OOD
//#define DOD


#ifdef OOD
int main()
{
    //sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML works!");
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

#endif