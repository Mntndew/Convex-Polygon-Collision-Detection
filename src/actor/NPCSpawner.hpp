#pragma once

#include "actor/Actor.hpp"


class NPCSpawner
{
public:
	NPCSpawner();
	~NPCSpawner();

	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f& position);

	ActorType getType() const;
	void setType(const ActorType& type);

private:
	sf::Vector2f m_position;
	ActorType m_type;
};

