#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "actor/Actor.hpp"
#include "actor/FollowerNetwork.hpp"
#include "actor/ActorIdTracker.hpp"
#include "actor/LifeActor.hpp"
#include "actor/NPCSpawnerManager.hpp"
#include "actor/NPCActor.hpp"
#include "world/Quadtree.hpp"


class ActorManager : public sf::Drawable
{
public:
	ActorManager();
	~ActorManager();

	void addSpawner(const ActorType& type, const sf::Vector2f& position);

	void addActor(const std::shared_ptr<Actor> actor);
	void createActor(const ActorType& type, const sf::Vector2f& position);

	void update(const float deltaTime, const sf::Vector2f& position, const sf::Vector2f& size);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setQuadtree(const std::weak_ptr<Quadtree> quadtree);

private:
	FollowerNetwork m_followerNetwork;
	ActorIdTracker m_actorIdTracker;
	NPCSpawnerManager m_npcSpawnerManager;
	std::vector<std::shared_ptr<Actor>> m_actors;
	std::weak_ptr<Quadtree> m_quadtree;
	std::weak_ptr<PlayerActor> m_playerActor;
};

