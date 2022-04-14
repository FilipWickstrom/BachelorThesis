#pragma once

class IComponentArray
{
public:

	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(const Entity& entity) = 0;
};


template<typename T>
class ComponentArray : public IComponentArray
{
private:

	std::array<T, MAX_ENTITIES> m_components{};

public:

	ComponentArray() = default;

	std::array<T, MAX_ENTITIES>& GetArray()
	{
		return m_components;
	}

	T& GetComponent(const Entity& entity)
	{
		return m_components[entity];
	}

	// Inherited via IComponentArray
	virtual void EntityDestroyed(const Entity& entity) override
	{
	}

};
