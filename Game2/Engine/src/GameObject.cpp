#include "PCH.h"
#include "GameObject.h"

GameObject::GameObject()
{
	m_tag = ETagType::none;
	m_collisionRadius = 0.f;
}

GameObject::GameObject(const ETagType& type)
{
	m_tag = type;
	m_collisionRadius = 0.f;
}

bool GameObject::IsColliding(const GameObject& obj) const
{
	vec2 pos1 = m_shape.getPosition();
	vec2 pos2 = obj.GetPosition();
	
	float xdist = pos2.x - pos1.x;
	float ydist = pos2.y - pos1.y;
	float distance = std::sqrt(xdist * xdist + ydist * ydist);

	if (distance < m_collisionRadius + obj.GetCollisionRadius())
		return true;

	return false;
}

void GameObject::SetPosition(const vec2& pos)
{
	m_shape.setPosition(pos);
}

void GameObject::SetTag(const ETagType& tag)
{
	m_tag = tag;
}

void GameObject::SetCollisionRadius(const float& rad)
{
	m_collisionRadius = rad;
}

const vec2& GameObject::GetPosition() const
{
	return m_shape.getPosition();
}

const ETagType& GameObject::GetTag() const
{
	return m_tag;
}

const float& GameObject::GetCollisionRadius() const
{
	return m_collisionRadius;
}
