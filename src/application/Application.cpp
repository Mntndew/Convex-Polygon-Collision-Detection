#include "Application.hpp"

Application::Application(int argc, char** argv)
{
	run();
}

Application::~Application()
{

}

void Application::initialize()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 32;

	m_window.create(sf::VideoMode(1600, 900), "Prototype -- The Revenge of the Carrots", sf::Style::Close, settings);
	m_window.setPosition({0, 0});
	m_view.setSize(1600, 900);
	m_window.setView(m_view);

	m_playerActor.reset(new PlayerActor());
	math::Polygon playerPolygon, playerBottom;
	playerPolygon.addPoint({0, 0});
	playerPolygon.addPoint({50, 0});
	playerPolygon.addPoint({50, 50});
	playerPolygon.addPoint({0, 50});
	playerPolygon.constructEdges();
	playerBottom.addPoint({4, 40});
	playerBottom.addPoint({46, 40});
	playerBottom.addPoint({46, 50});
	playerBottom.addPoint({4, 50});
	playerBottom.constructEdges();
	m_playerActor->setPolygon(playerPolygon);
	m_playerActor->setBottom(playerBottom);
	m_playerActor->updateShape();
	m_playerActor->move({50, 0});
	m_world.addActor(m_playerActor);

	m_camera.trackActor(m_playerActor);

	/*b.resize(1, math::Polygon());
	b[0].addPoint(sf::Vector2f(0, 0));
	b[0].addPoint(sf::Vector2f(500, 0));
	b[0].addPoint(sf::Vector2f(500, 20));
	b[0].addPoint(sf::Vector2f(0, 20));
	b[0].offset(0, 880);
	b[0].constructEdges();

	_b.setPointCount(b[0].getPointCount());
	for (int i = 0; i < b[0].getPointCount(); ++i)
		_b.setPoint(i, b[0].getPoint(i));
	_b.setFillColor({0, 255, 0, 100});*/

	m_world.load("map.obj");
	
	m_running = true;
	m_active = true;
	m_space = false;
	m_mouse = false;
}

void Application::run()
{
	initialize();
	
	sf::Clock dt;
	sf::Time deltaTime;
	sf::Time updateTime = sf::seconds(1.f/60.f);

	while(m_running)
	{
		deltaTime += dt.getElapsedTime();
		dt.restart();

		handleEvents();
		render();
		while (deltaTime >= updateTime && m_active)
		{
			update(deltaTime);
			deltaTime -= updateTime;
		}
	}
}

void Application::handleEvents()
{
	sf::Event event;

	while(m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
		{
			m_window.close();
			m_running = false;
		}
	}
}

void Application::update(sf::Time & deltaTime)
{
	m_playerActor->control(deltaTime.asSeconds());
	m_playerActor->setGrounded(false);
	m_playerActor->setColliding(false);

	std::vector<unsigned char> indices;
	auto polygons = m_world.getPolygons(m_playerActor->getPolygon(), indices);

	for (int i = 0; i < polygons.size(); ++i)
	{
		auto intersect = math::intersect(m_playerActor->getPolygon(), polygons[i], m_playerActor->getVelocity()*deltaTime.asSeconds());
		if (intersect.willIntersect)
		{
			m_playerActor->setColliding(true);
			m_playerActor->setVelocity(m_playerActor->getVelocity() + intersect.minimumTranslationVector/deltaTime.asSeconds());
			_b.setFillColor({255, 0, 0, 100});

			intersect = math::intersect(m_playerActor->getBottom(), polygons[i], m_playerActor->getVelocity()*deltaTime.asSeconds());
			if (intersect.intersect)
				m_playerActor->setGrounded(intersect.willIntersect);
		}
		else
			_b.setFillColor({0, 255, 0, 100});
	}

	m_playerActor->update(deltaTime.asSeconds());

	m_camera.update(deltaTime.asSeconds());
	m_view.setCenter(m_camera.getPosition());

	m_world.update(deltaTime.asSeconds(), m_playerActor->getPosition());
}

void Application::render()
{
	m_window.setView(m_view);
	m_window.clear(sf::Color(46, 46, 46));
	
	m_window.draw(m_world);
	m_window.draw(*m_playerActor);

	m_window.display();
}

