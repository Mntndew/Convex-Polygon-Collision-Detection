#include "actor/NPCSpawnerManager.hpp"


NPCSpawnerManager::NPCSpawnerManager()
{
}

NPCSpawnerManager::~NPCSpawnerManager()
{
}

void NPCSpawnerManager::addSpawner(const NPCSpawner& spawner)
{
	m_spawners.push_back(std::shared_ptr<NPCSpawner>(new NPCSpawner(spawner)));
}

void NPCSpawnerManager::update(const sf::Vector2f& playerPosition)
{
	if (!m_spawners.empty())
	{
		auto it = m_spawners.begin();

		while (it != m_spawners.end())
		{
			if (math::distance<float>((*it)->getPosition(), playerPosition) <= 2000)
			{
				m_activeSpawners.push_back(*it);
				m_spawners.erase(it);
			}
			else
				++it;
		}
	}
}

std::vector<std::shared_ptr<NPCSpawner>> NPCSpawnerManager::getActiveSpawnersAndClear()
{
	auto spawners = m_activeSpawners;
	m_activeSpawners.clear();
	return spawners;
}

