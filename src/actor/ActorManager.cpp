#include "actor/ActorManager.hpp"


ActorManager::ActorManager()
{
}

ActorManager::~ActorManager()
{
}

void ActorManager::addSpawner(const ActorType& type, const sf::Vector2f& position)
{
	NPCSpawner spawner;
	spawner.setType(type);
	spawner.setPosition(position);
	m_npcSpawnerManager.addSpawner(spawner);
}

void ActorManager::addActor(std::shared_ptr<Actor> actor)
{
	if (actor->getId().id == -1)
		actor->setId(m_actorIdTracker.registerNewActor());

	if (!m_playerActor.lock() && actor->isPlayer())
	{
		m_playerActor = std::static_pointer_cast<PlayerActor, Actor>(actor);
		m_followerNetwork.setLeader(m_playerActor.lock());
	}
	else
		m_actors.push_back(actor);
}

void ActorManager::createActor(const ActorType& type, const sf::Vector2f& position)
{
	std::shared_ptr<Actor> actor;
	math::Polygon polygon, bottom;
	switch (type)
	{
		case ActorType::Carrot:
		break;

		case ActorType::CarrotLife:
			actor.reset(new LifeActor());
			polygon.addPoint({0, 0});
			polygon.addPoint({50, 0});
			polygon.addPoint({50, 50});
			polygon.addPoint({0, 50});
			polygon.constructEdges();
			bottom.addPoint({0, 45});
			bottom.addPoint({50, 45});
			bottom.addPoint({50, 50});
			bottom.addPoint({0, 50});
			bottom.constructEdges();
		break;

		case ActorType::Rabbit:
			actor.reset(new NPCActor());
			polygon.addPoint({0, 0});
			polygon.addPoint({50, 0});
			polygon.addPoint({50, 50});
			polygon.addPoint({0, 50});
			polygon.constructEdges();
			bottom.addPoint({0, 45});
			bottom.addPoint({50, 45});
			bottom.addPoint({50, 50});
			bottom.addPoint({0, 50});
			bottom.constructEdges();
		break;

		default:
		break;
	}
	
	if (actor)
	{
		actor->setId(m_actorIdTracker.registerNewActor());
		actor->setPolygon(polygon);
		actor->setBottom(bottom);
		actor->updateShape();
		actor->move(position);
		m_actors.push_back(actor);
	}
}

void ActorManager::update(const float deltaTime, const sf::Vector2f& position, const sf::Vector2f& size)
{
	if (auto quadtree = m_quadtree.lock())
	{
		for (int i = 0; i < m_actors.size(); ++i)
		{
			m_actors[i]->control(deltaTime);
			m_actors[i]->setGrounded(false);
			m_actors[i]->setColliding(false);

			std::vector<unsigned char> indices;
			auto polygons = quadtree->getPolygons(m_actors[i]->getPolygon(), indices);
			for (int j = 0; j < polygons.size(); ++j)
			{
				auto intersect = math::intersect(m_actors[i]->getPolygon(), polygons[j], m_actors[i]->getVelocity()*deltaTime);
				if (intersect.willIntersect)
				{
					m_actors[i]->setColliding(true);
					m_actors[i]->setVelocity(m_actors[i]->getVelocity() + intersect.minimumTranslationVector/deltaTime);

					if (m_actors[i]->isPlayer())
					{
						intersect = math::intersect(m_actors[i]->getBottom(), polygons[j], m_actors[i]->getVelocity()*deltaTime);
						if (intersect.intersect)
							m_actors[i]->setGrounded(intersect.willIntersect);
					}
				}
			}
			if (auto playerActor = m_playerActor.lock())
			{
				if (m_actors[i]->getType() == ActorType::CarrotLife)
				{
					if (math::distance<float>(m_actors[i]->getPosition(), playerActor->getPosition()) <= 100)
						m_followerNetwork.addFollower(m_actors[i]);
				}
			}

			m_actors[i]->update(deltaTime);
		}
	}

	m_followerNetwork.update(deltaTime);
	m_npcSpawnerManager.update(position);
	auto spawners = m_npcSpawnerManager.getActiveSpawnersAndClear();

	for (auto it = spawners.begin(); it != spawners.end(); ++it)
	{
		std::cout << "Creating actor from spawner of type: " << (int)(*it)->getType() << std::endl;
		createActor((*it)->getType(), (*it)->getPosition());
	}
}

void ActorManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < m_actors.size(); ++i)
		target.draw(*m_actors[i], states);
}

void ActorManager::setQuadtree(const std::weak_ptr<Quadtree> quadtree)
{
	m_quadtree = quadtree;
}

