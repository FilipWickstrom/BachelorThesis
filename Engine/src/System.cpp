#include "PCH.h"
#include "System.hpp"
#include "Components.h"
#include "Coordinator.hpp"

void MovementSystem::Update(Coordinator& coord, const float& dt)
{
    for (const auto& entity : m_entities)
    {
        Transform& transf = coord.GetComponent<Transform>(entity);

        const Tag& tag = coord.GetComponent<Tag>(entity);
        switch (tag.tag)
        {
        case Tags::PLAYER:
        {
            transf.velocity = { 0.0f, 0.0f };

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
                transf.velocity.x = 45;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
                transf.velocity.x = -45;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
                transf.velocity.y = -45;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
                transf.velocity.y = 45;

            break;
        }
        default:
            break;
        }

        transf.position.x += transf.velocity.x * dt;
        transf.position.y += transf.velocity.y * dt;
    }
}

void RenderSystem::Render(Coordinator& coord)
{
    for (const auto& entity : m_entities)
    {
        Renderable& shape = coord.GetComponent<Renderable>(entity);
        const Transform& transf = coord.GetComponent<Transform>(entity);

        shape.shape.setPosition(transf.position);
        SFMLTon::GetWindow().draw(shape.shape);
    }
}

void CollisionSystem::Detect(const Entity& playerEntity, Coordinator& coord)
{
    const Renderable& shape = coord.GetComponent<Renderable>(playerEntity);

    for (Entity entity = 1; entity < m_entities.size(); entity++)
    {
        const Renderable& otherShape = coord.GetComponent<Renderable>(entity);

        if (shape.shape.getGlobalBounds().intersects(otherShape.shape.getGlobalBounds()))
            m_collisions.push_back({ playerEntity, entity });
    }
}

void CollisionSystem::Act(Coordinator& coord)
{
    while (m_collisions.size() > 0)
    {
        const CollInfo& info = m_collisions[(int)m_collisions.size()];
        const Tag& tag = coord.GetComponent<Tag>(info.other);

        Renderable& rend = coord.GetComponent<Renderable>(info.player);
        switch (tag.tag)
        {
        case Tags::GOOD:
        {
            rend.shape.scale(1.25f, 1.25f);
            break;
        }
        case Tags::BAD:
        {
            rend.shape.setScale(1.0f, 1.0f);
            break;
        }
        default:
            break;
        }

        m_collisions.pop_back();
    }
}
