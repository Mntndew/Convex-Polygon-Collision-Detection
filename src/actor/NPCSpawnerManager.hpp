#pragma once

#include <memory>

#include "actor/NPCSpawner.hpp"


class NPCSpawnerManager
{
public:
	NPCSpawnerManager();
	~NPCSpawnerManager();

	void addSpawner(const NPCSpawner& spawner);

	void update(const sf::Vector2f& playerPosition);
	std::vector<std::shared_ptr<NPCSpawner>> getActiveSpawnersAndClear();

private:
	std::vector<std::shared_ptr<NPCSpawner>> m_spawners, m_activeSpawners;
};

