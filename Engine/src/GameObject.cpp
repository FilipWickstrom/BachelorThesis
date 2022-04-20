#include "PCH.h"
#include "GameObject.h"
#include <cmath>

#ifdef OOD

GameObject::GameObject()
{
	m_tag = Tags::DEFAULT;
}

void GameObject::SetTag(const Tags& tag)
{
	m_tag = tag;
}

const vec2& GameObject::GetPosition() const
{
	return m_position;
}

const vec2& GameObject::GetScale() const
{
	return m_scale;
}

const Tags& GameObject::GetTag() const
{
	return m_tag;
}

void RenderObject::SetShape(sf::CircleShape& shape)
{
	m_shape = shape;
}

void RenderObject::SetPosition(const vec2& pos)
{
	m_position = pos;
	m_shape.setPosition(m_position);
}

void RenderObject::SetScale(const vec2& scale)
{
	m_scale = scale;
	m_shape.setRadius(m_scale.x);
}

const sf::FloatRect RenderObject::GetBounds() const
{
	return m_shape.getGlobalBounds();
}

void RenderObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_shape);
}

const bool RenderObject::IsColliding(RenderObject& other)
{
	vec2 pos1 = m_shape.getPosition();
	vec2 pos2 = other.GetPosition();

	float xdist = pos2.x - pos1.x;
	float ydist = pos2.y - pos1.y;
	float distance = std::sqrt(xdist * xdist + ydist * ydist);

	if (distance < m_shape.getRadius() + other.m_shape.getRadius())
	{
		return true;
	}

	return false;


	//return m_shape.getGlobalBounds().intersects(other.GetBounds());
}

#endif
