#pragma once

#include <map>
#include <fstream>

#include <SFML/Graphics.hpp>

#include "actor/ActorIdTracker.hpp"
#include "actor/ActorManager.hpp"
#include "actor/NPCActor.hpp"
#include "actor/PlayerActor.hpp"
#include "application/Misc.hpp"
#include "world/Quadtree.hpp"


class World : public sf::Drawable
{
public:
	World();
	~World();

	void addActor(std::shared_ptr<Actor> actor);
	void addPolygon(const math::Polygon& polygon);
	void update(const float deltaTime, const sf::Vector2f& playerPosition);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void load(const std::string& path);

	std::vector<math::Polygon> getPolygons(const math::Polygon& polygon, std::vector<unsigned char>& indices) const;

private:
	unsigned int m_index;
	std::shared_ptr<Quadtree> m_quadtree;
	std::map<unsigned int, sf::ConvexShape> m_shapes;

	ActorManager m_actorManager;
};

