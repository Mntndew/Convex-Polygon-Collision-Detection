#include "actor/NPCSpawner.hpp"


NPCSpawner::NPCSpawner()
{
}

NPCSpawner::~NPCSpawner()
{
}

sf::Vector2f NPCSpawner::getPosition() const
{
	return m_position;
}

void NPCSpawner::setPosition(const sf::Vector2f& position)
{
	m_position = position;
}

ActorType NPCSpawner::getType() const
{
	return m_type;
}

void NPCSpawner::setType(const ActorType& type)
{
	m_type = type;
}

