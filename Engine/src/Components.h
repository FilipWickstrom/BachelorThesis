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
	// Velocity
	vec2 velo = {rand() % 32 - 16, rand() % 32 - 16};
	// Scale
	vec2 scale = {10.0f, 10.0f};
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

struct Collider
{
	uint8_t hasCollided = 0;
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
	virtual void EntitiyDestroyed(const Entity& entity) = 0;
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

	void InsertData(const Entity& entity, T component);

	void RemoveData(const Entity& entity);

	T& GetData(const Entity& entity);

	// Inherited via IComponentArray
	virtual void EntitiyDestroyed(const Entity& entity) override;
};

template<typename T>
inline void ComponentArray<T>::InsertData(const Entity& entity, T component)
{
	assert(m_entityToIndexMap.find(entity) == m_entityToIndexMap.end() && "Component already exists");

	size_t newIndex = m_size;
	m_entityToIndexMap[entity] = newIndex;
	m_indexToEntityMap[newIndex] = entity;
	m_components[newIndex] = component;
	m_size++;
}

template<typename T>
inline void ComponentArray<T>::RemoveData(const Entity& entity)
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
inline T& ComponentArray<T>::GetData(const Entity& entity)
{
	assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end() && "Component doesn't exist");

	return m_components[m_entityToIndexMap[entity]];
}

template<typename T>
inline void ComponentArray<T>::EntitiyDestroyed(const Entity& entity)
{
	if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end())
	{
		RemoveData(entity);
	}
}



class ComponentManager
{
private:

	std::unordered_map<const char*, ComponentType> m_componentTypes{};
	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_componentArrays{};

	ComponentType m_nextComponentType{};

	template<typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray()
	{
		const char* typeName = typeid(T).name();

		assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "Such component doesnt exist.");

		return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
	}

public:

	template<typename T>
	void RegisterComponent()
	{
		const char* typeName = typeid(T).name();

		assert(m_componentTypes.find(typeName) == m_componentTypes.end() && "Component is already registered");

		m_componentTypes.insert({ typeName, m_nextComponentType });
		m_componentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });

		m_nextComponentType++;
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		const char* typeName = typeid(T).name();

		assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "Component doesn't exist.");

		return m_componentTypes[typeName];
	}

	template<typename T>
	void AddComponent(const Entity& entity, T component)
	{
		GetComponentArray<T>()->InsertData(entity, component);
	}

	template<typename T>
	void RemoveComponent(const Entity& entity)
	{
		GetComponentArray<T>()->RemoveData(entity);
	}

	template<typename T>
	T& GetComponent(const Entity& entity)
	{
		return GetComponentArray<T>()->GetData(entity);
	}

	void EntityDestroyed(const Entity& entity)
	{
		for (auto const& pair : m_componentArrays)
		{
			auto const& comp = pair.second;
			comp->EntitiyDestroyed(entity);
		}
	}

};


// END OF COMPONENT CLASSES
