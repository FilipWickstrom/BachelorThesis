#include "PCH.h"
#include "GameObject.h"

GameObject::GameObject()
{
	m_collisionRad = 0;
	m_tag = ETagType::none;
}

GameObject::GameObject(const ETagType& type)
{
	m_collisionRad = 0;
	m_tag = type;
}

bool GameObject::IsColliding(const GameObject& obj) const
{
	vec2 pos1 = m_shape->getPosition();
	vec2 pos2 = obj.GetPosition();
	float rad1 = m_collisionRad;
	float rad2 = obj.GetCollionRad();

	//Check distance between the positions
	float xDif = pos1.x - pos2.x;
	float yDif = pos1.y - pos2.y;
	float distance = std::sqrtf((xDif * xDif) + (yDif * yDif));

	//Collision!
	if (distance > rad1 || distance > rad2)
		return true;

	return false;
}

void GameObject::SetPosition(const vec2& pos)
{
	if (!m_shape) return;
	m_shape->setPosition(pos);
}

const vec2& GameObject::GetPosition() const
{
	return m_shape->getPosition();
}

const float& GameObject::GetCollionRad() const
{
	return m_collisionRad;
}



