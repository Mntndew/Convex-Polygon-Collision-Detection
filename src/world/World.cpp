#include "World.hpp"


World::World() :
	m_index(0)
{
	m_quadtree.reset(new Quadtree(sf::Vector2f(0, 0), sf::Vector2f(16384, 16384), false, 0));
	m_actorManager.setQuadtree(m_quadtree);
}

World::~World()
{
}

void World::addActor(std::shared_ptr<Actor> actor)
{
	m_actorManager.addActor(actor);
}

void World::addPolygon(const math::Polygon& polygon)
{
	m_quadtree->insert(std::shared_ptr<math::Polygon>(new math::Polygon(polygon)), m_index);

	sf::ConvexShape shape;
	shape.setPointCount(polygon.getPointCount());

	for (int i = 0; i < shape.getPointCount(); ++i)
		shape.setPoint(i, polygon.getPoint(i));
	
	m_shapes[m_index] = shape;
	m_index++;
}

void World::update(const float deltaTime, const sf::Vector2f& playerPosition)
{
	m_actorManager.update(deltaTime, playerPosition, {0, 0});
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto it = m_shapes.begin(); it != m_shapes.end(); ++it)
		target.draw(it->second, states);

	m_quadtree->draw(target, states);

	target.draw(m_actorManager, states);
}

void World::load(const std::string& path)
{
	std::ifstream file;
	file.open(path);

	if (file.is_open())
	{
		std::string line;
		while (!file.eof())
		{
			std::getline(file, line);

			if (!line.empty() && line[0] == 'o') // new object
			{
				auto objectType = line.substr(2);
				if (objectType.substr(0, 4) == "Cube") // NPC spawner
				{
					std::getline(file, line);
					while (!line.empty() && line[0] != 'u')
					{
						if (!line.empty() && line[0] == 'v' && line.substr(0, 2) != "vn") // is vertex
						{
							auto indices = misc::getAllInstancesOfChar(line, ' ');
							if (indices.size() >= 3)
							{
								auto x = std::atof(line.substr(indices[0] + 1, indices[1] - indices[0] - 1).c_str()), y = std::atof(line.substr(indices[1] + 1, indices[2] - indices[1] - 1).c_str()), z = std::atof(line.substr(indices[2] + 1).c_str());
								m_actorManager.addSpawner(ActorType::CarrotLife, {(float)x*100, (float)y*100});
								break;
							}
						}
						std::getline(file, line);
					}
				}
				else
				{
					math::Polygon polygon;
					std::getline(file, line);
					while (!line.empty() && line[0] != 'u')
					{
						if (!line.empty() && line[0] == 'v' && line.substr(0, 2) != "vn") // is vertex
						{
							auto indices = misc::getAllInstancesOfChar(line, ' ');
							if (indices.size() >= 3)
							{
								auto x = std::atof(line.substr(indices[0] + 1, indices[1] - indices[0] - 1).c_str()), y = std::atof(line.substr(indices[1] + 1, indices[2] - indices[1] - 1).c_str()), z = std::atof(line.substr(indices[2] + 1).c_str());
								polygon.addPoint({(float)x*100, (float)z*100});
							}
						}
						std::getline(file, line);
					}
					
					polygon.constructEdges(true);
					addPolygon(polygon);
				}
			}
		}
	}
}

std::vector<math::Polygon> World::getPolygons(const math::Polygon& polygon, std::vector<unsigned char>& indices) const
{
	return m_quadtree->getPolygons(polygon, indices);
}

