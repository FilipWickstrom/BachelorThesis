#include "PCH.h"
#include "GameObject.h"

GameObject::GameObject()
{
	m_tag = ETagType::none;
}

GameObject::GameObject(const ETagType& type)
{
	m_tag = type;
}

bool GameObject::IsColliding(const GameObject& obj) const
{
	return m_shape->getGlobalBounds().intersects(obj.m_shape->getGlobalBounds());
}

void GameObject::SetPosition(const vec2& pos)
{
	if (!m_shape) return;
	m_shape->setPosition(pos);
}

void GameObject::SetTag(const ETagType& tag)
{
	m_tag = tag;
}

const vec2& GameObject::GetPosition() const
{
	return m_shape->getPosition();
}

const ETagType& GameObject::GetTag() const
{
	return m_tag;
}
