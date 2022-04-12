#pragma once

enum class Tags : uint8_t
{
	DEFAULT,
	GOOD,
	PLAYER,
	BAD,
};

// COMPONENTS

struct Transform
{
	// Position
	vec2 pos = {rand() % 10000 - 5000, rand() % 10000 - 5000};
	
	// Scale
	vec2 scale = {10.0f, 10.0f};
};

struct RigidBody
{
	// Velocity
	vec2 velo = { rand() % 32 - 16, rand() % 32 - 16 };

	RigidBody() = default;
	RigidBody(float velo)
	{
		this->velo.x = velo;
		this->velo.y = velo;
	}
};

struct Color
{
	sf::Color color = sf::Color::Blue;

	Color() = default;
	Color(const sf::Color& color)
	{
		this->color = color;
	}
};

struct Value
{
	int worth = 1;
	Value() = default;
	Value(int wort)
	{
		worth = wort;
	}
};

struct Tag
{
	Tags tag = Tags::PLAYER;

	Tag() = default;
	Tag(const Tags& tag)
	{
		this->tag = tag;
	}
};




// END OF COMPONENTS


// Components Classes


class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void EntitiyDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray
{
private:

	std::array<T, MAX_ENTITIES> m_components;
	std::unordered_map<Entity, size_t> m_entityToIndexMap;
	std::unordered_map<size_t, Entity> m_indexToEntityMap;

	size_t m_size;

public:

	void InsertData(Entity entity, T component);

	void RemoveData(Entity entity);

	T& GetData(Entity entity);

	// Inherited via IComponentArray
	virtual void EntitiyDestroyed(Entity entity) override;
};

template<typename T>
inline void ComponentArray<T>::InsertData(Entity entity, T component)
{
	assert(m_entityToIndexMap.find(entity) == m_entityToIndexMap.end() && "Component already exists");

	size_t newIndex = m_size;
	m_entityToIndexMap[entity] = newIndex;
	m_indexToEntityMap[newIndex] = entity;
	m_components[newIndex] = component;
	m_size++;
}

template<typename T>
inline void ComponentArray<T>::RemoveData(Entity entity)
{
	assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end() && "Component doesn't exist");

	size_t removedIndex = m_entityToIndexMap[entity];
	size_t indexLastElem = m_size - 1;
	m_components[removedIndex] = m_components[indexLastElem];


	Entity lastEntity = m_indexToEntityMap[removedIndex];
	m_entityToIndexMap[lastEntity] = removedIndex;
	m_indexToEntityMap[removedIndex] = lastEntity;

	m_entityToIndexMap.erase(entity);
	m_indexToEntityMap.erase(removedIndex);

	m_size--;
}

template<typename T>
inline T& ComponentArray<T>::GetData(Entity entity)
{
	//assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end() && "Component doesn't exist");

	return m_components[m_entityToIndexMap[entity]];
}

template<typename T>
inline void ComponentArray<T>::EntitiyDestroyed(Entity entity)
{
	if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end())
	{
		RemoveData(entity);
	}
}



class ComponentManager
{
private:

	std::unordered_map<size_t, ComponentType> m_componentTypes{};
	std::unordered_map<size_t, std::shared_ptr<IComponentArray>> m_componentArrays{};

	ComponentType m_nextComponentType{};

	template<typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray()
	{
		size_t typeName = typeid(T).hash_code();

		assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "Such component doesnt exist.");

		return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
	}

public:

	template<typename T>
	void RegisterComponent()
	{
		size_t typeName = typeid(T).hash_code();

		assert(m_componentTypes.find(typeName) == m_componentTypes.end() && "Component is already registered");

		m_componentTypes.insert({ typeName, m_nextComponentType });
		m_componentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

		m_nextComponentType++;
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		size_t typeName = typeid(T).hash_code();

		assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "Component doesn't exist.");

		return m_componentTypes[typeName];
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
		GetComponentArray<T>()->InsertData(entity, component);
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		GetComponentArray<T>()->RemoveData(entity);
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
		return GetComponentArray<T>()->GetData(entity);
	}

	void EntityDestroyed(Entity entity)
	{
		for (auto const& pair : m_componentArrays)
		{
			auto const& comp = pair.second;
			comp->EntitiyDestroyed(entity);
		}
	}

};


// END OF COMPONENT CLASSES
